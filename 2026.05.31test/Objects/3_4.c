//#include <reg51.h>
//#include "Delay.h"

//// 38译码器位选：P2.2=A, P2.3=B, P2.4=C
//sbit A_138 = P2^2;
//sbit B_138 = P2^3;
//sbit C_138 = P2^4;

//// 共阴极段码：0~9，10='-'
//unsigned char code SEG_TABLE[] =
//{
//    0x3F,  // 0
//    0x06,  // 1
//    0x5B,  // 2
//    0x4F,  // 3
//    0x66,  // 4
//    0x6D,  // 5
//    0x7D,  // 6
//    0x07,  // 7
//    0x7F,  // 8
//    0x6F,  // 9
//    0x40   // 10 = '-' 横杠
//};

//// 时钟变量
//unsigned char second = 0;
//unsigned char minute = 0;
//unsigned char hour = 0;

//// 显示缓冲：8位数码管（全部启用）
//unsigned char disp_buf[8];

//// 位选函数（3-8译码器，支持8位：000~111）
//void Select_Digit(unsigned char pos)
//{
//    A_138 = pos & 0x01;         // A = bit0
//    B_138 = (pos >> 1) & 0x01;  // B = bit1
//    C_138 = (pos >> 2) & 0x01;  // C = bit2
//}

//// 动态扫描显示（扫描8位）
//void Display_Scan(void)
//{
//    unsigned char i;
//    for(i = 0; i < 8; i++)      // 改成扫描8位
//    {
//        P0 = 0x00;                          // 消隐
//        Select_Digit(i);                    // 位选
//        P0 = SEG_TABLE[disp_buf[i]];        // 段码
//        DelayMS(1);                         // 延时1ms
//    }
//    P0 = 0x00;                              // 最后消隐
//}

//// 更新显示缓冲：格式为 MM----SS
//void Update_Buffer(void)
//{
//    disp_buf[0] = minute / 10;      // 分钟十位（最高位）
//    disp_buf[1] = minute % 10;      // 分钟个位
//    disp_buf[2] = 10;               // 横杠 '-'
//    disp_buf[3] = 10;               // 横杠 '-'
//    disp_buf[4] = 10;               // 横杠 '-'
//    disp_buf[5] = 10;               // 横杠 '-'
//    disp_buf[6] = second / 10;      // 秒十位
//    disp_buf[7] = second % 10;      // 秒个位（最低位）
//}

//// 定时器0中断：50ms
//unsigned char cnt0 = 0;

//void T0_ISR(void) interrupt 1
//{
//    TH0 = 0x3C;
//    TL0 = 0xB0;
//    
//    cnt0++;
//    if(cnt0 >= 20)          // 1秒到
//    {
//        cnt0 = 0;
//        second++;
//        
//        if(second >= 60)
//        {
//            second = 0;
//            minute++;
//            if(minute >= 60)
//            {
//                minute = 0;
//                hour++;
//                if(hour >= 24)
//                    hour = 0;
//            }
//        }
//        Update_Buffer();
//    }
//}

//void main(void)
//{
//    Update_Buffer();
//    
//    TMOD = 0x01;
//    TH0 = 0x3C;
//    TL0 = 0xB0;
//    
//    ET0 = 1;
//    TR0 = 1;
//    EA = 1;
//    
//    while(1)
//    {
//        Display_Scan();
//    }
//}

////#include <reg51.h>
////#include "Delay.h"

////// 38译码器位选：P2.2=A, P2.3=B, P2.4=C
////sbit A_138 = P2^2;
////sbit B_138 = P2^3;
////sbit C_138 = P2^4;

////// 共阴极段码：0~9
////unsigned char code SEG_TABLE[] =
////{
////    0x3F,  // 0
////    0x06,  // 1
////    0x5B,  // 2
////    0x4F,  // 3
////    0x66,  // 4
////    0x6D,  // 5
////    0x7D,  // 6
////    0x07,  // 7
////    0x7F,  // 8
////    0x6F,  // 9
////		0x40   // -
////	
////};

////// 时钟变量
////unsigned char second = 0;
////unsigned char minute = 0;
////unsigned char hour = 0;

////// 显示缓冲：6位数码管
////unsigned char disp_buf[6];

////// 位选函数
////void Select_Digit(unsigned char pos)
////{
////    A_138 = pos & 0x01;
////    B_138 = (pos >> 1) & 0x01;
////    C_138 = (pos >> 2) & 0x01;
////}

////// 动态扫描显示
////void Display_Scan(void)
////{
////    unsigned char i;
////    for(i = 0; i < 6; i++)
////    {
////        P0 = 0x00;                          // 消隐
////        Select_Digit(i);                    // 位选
////        P0 = SEG_TABLE[disp_buf[i]];        // 段码（共阴极直接输出）
////        DelayMS(1);                         // 延时1ms
////    }
////    P0 = 0x00;                              // 最后消隐
////}

////// 更新显示缓冲
////void Update_Buffer(void)
////{
////    disp_buf[0] = hour / 10;        // 时十位
////    disp_buf[1] = hour % 10;        // 时个位
////    disp_buf[2] = minute / 10;      // 分十位
////    disp_buf[3] = minute % 10;      // 分个位
////    disp_buf[4] = second / 10;      // 秒十位
////    disp_buf[5] = second % 10;      // 秒个位
////}

////// 定时器0中断：50ms
////unsigned char cnt0 = 0;

////void T0_ISR(void) interrupt 1
////{
////    TH0 = 0x3C;
////    TL0 = 0xB0;
////    
////    cnt0++;
////    if(cnt0 >= 20)          // 1秒到
////    {
////        cnt0 = 0;
////        second++;
////        
////        if(second >= 60)
////        {
////            second = 0;
////            minute++;
////            if(minute >= 60)
////            {
////                minute = 0;
////                hour++;
////                if(hour >= 24)
////                    hour = 0;
////            }
////        }
////        Update_Buffer();
////    }
////}

////void main(void)
////{
////    Update_Buffer();
////    
////    TMOD = 0x01;
////    TH0 = 0x3C;
////    TL0 = 0xB0;
////    
////    ET0 = 1;
////    TR0 = 1;
////    EA = 1;
////    
////    while(1)
////    {
////        Display_Scan();
////    }
////}