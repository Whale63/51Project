#include <REGX52.H>

// 数码管段码表：0~9
unsigned char code NixieTable[] =
{
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F   // 9
};

// 时钟变量
unsigned char year = 24;    // 年 0~99
unsigned char month = 5;    // 月 1~12
unsigned char day = 31;     // 日 1~31
unsigned char hour = 12;    // 时 0~23
unsigned char minute = 0;   // 分 0~59
unsigned char second = 0;  // 秒 0~59

// 显示缓冲：年(2位) 月(2位) 日(2位) 时(2位) 分(2位) 秒(2位)
// 位置：1-2:年, 3-4:月, 5-6:日, 7-8:时（时分秒用另外一组或轮换显示）
unsigned char disp_buf[8];

// 延时子函数
void Delay(unsigned int xms)
{
    unsigned char i, j;
    while(xms--)
    {
        i = 2;
        j = 239;
        do
        {
            while(--j);
        } while(--i);
    }
}

// 判断闰年：1是闰年，0不是
unsigned char IsLeapYear(unsigned char y)
{
    unsigned int full_year = 2000 + y;
    if((full_year % 4 == 0 && full_year % 100 != 0) || (full_year % 400 == 0))
    {
        return 1;
    }
    return 0;
}

// 获取当月天数
unsigned char GetDaysInMonth(unsigned char m, unsigned char y)
{
    unsigned char days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(m == 2 && IsLeapYear(y))
    {
        return 29;
    }
    return days[m];
}

// 数码管显示子函数
void Nixie(unsigned char Location, unsigned char Number)
{
    switch(Location)
    {
        case 1: P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
        case 2: P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
        case 3: P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
        case 4: P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
        case 5: P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
        case 6: P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
        case 7: P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
        case 8: P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
    }
    P0 = NixieTable[Number];
    Delay(1);
    P0 = 0x00;
}

// 更新显示缓冲：年月日
void Update_Buffer_YMD(void)
{
    disp_buf[0] = year / 10;
    disp_buf[1] = year % 10;
    disp_buf[2] = month / 10;
    disp_buf[3] = month % 10;
    disp_buf[4] = day / 10;
    disp_buf[5] = day % 10;
    // 最后两位显示分隔或时分
    disp_buf[6] = hour / 10;
    disp_buf[7] = hour % 10;
}

// 更新显示缓冲：时分秒
void Update_Buffer_HMS(void)
{
    disp_buf[0] = hour / 10;
    disp_buf[1] = hour % 10;
    disp_buf[2] = minute / 10;
    disp_buf[3] = minute % 10;
    disp_buf[4] = second / 10;
    disp_buf[5] = second % 10;
    // 最后两位显示分隔或年月
    disp_buf[6] = month / 10;
    disp_buf[7] = month % 10;
}

// 定时器0中断：50ms
unsigned char cnt0 = 0;
bit show_mode = 0;  // 0=显示年月日，1=显示时分秒

void T0_ISR(void) interrupt 1
{
    TH0 = 0x3C;
    TL0 = 0xB0;
    
    cnt0++;
    if(cnt0 >= 20)
    {
        cnt0 = 0;
        second++;
        
        if(second >= 60)
        {
            second = 0;
            minute++;
            
            if(minute >= 60)
            {
                minute = 0;
                hour++;
                
                if(hour >= 24)
                {
                    hour = 0;
                    day++;
                    
                    if(day > GetDaysInMonth(month, year))
                    {
                        day = 1;
                        month++;
                        
                        if(month > 12)
                        {
                            month = 1;
                            year++;
                            
                            if(year > 99)
                            {
                                year = 0;
                            }
                        }
                    }
                }
            }
        }
        
        // 每5秒切换显示模式
        if(second % 5 == 0)
        {
            show_mode = ~show_mode;
        }
    }
}

void main(void)
{
    // 初始化显示缓冲
    Update_Buffer_YMD();
    
    // 定时器0初始化
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0xB0;
    ET0 = 1;
    TR0 = 1;
    EA = 1;
    
    while(1)
    {
        unsigned char i;
        
        // 根据模式更新缓冲
        if(show_mode == 0)
        {
            Update_Buffer_YMD();
        }
        else
        {
            Update_Buffer_HMS();
        }
        
        // 动态扫描8位数码管
        for(i = 0; i < 8; i++)
        {
            Nixie(i + 1, disp_buf[i]);
        }
    }
}
