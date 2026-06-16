/**********************************************************************
 * 文件名称: main.c
 * 功能描述: AT89C52 万年历
 *           8位数码管显示（默认共阴极），晶振12MHz
 *           显示模式：日期(YY.MM.DD.) / 时间(HH.MM.SS.) 自动切换
 *           支持按键设置时间
 * 硬件连接:
 *           P0.0-P0.7 -> 数码管段码 a,b,c,d,e,f,g,dp（需上拉电阻）
 *           P2.0-P2.7 -> 数码管位选 1-8（共阴极低电平有效）
 *           P3.0      -> 模式/设置按键（低电平有效）
 *           P3.1      -> 加按键（低电平有效）
 *           P3.2      -> 减按键（低电平有效）
 **********************************************************************/

#include <reg52.h>
#include <intrins.h>

/* ===================== 用户硬件配置 ===================== */
/* 1. 晶振频率（单位 Hz） */
/*    常用值：12000000(12MHz), 11059200(11.0592MHz) */
#define CRYSTAL_FREQ   12000000

/* 2. 数码管极性 */
/*    0 = 共阴极（默认） */
/*    1 = 共阳极 */
#define DIGIT_POLARITY 0
/* ====================================================== */

/* 根据晶振频率计算定时器0初值（定时1ms） */
#if (CRYSTAL_FREQ == 12000000)
    #define TIMER0_H  0xFC
    #define TIMER0_L  0x18
#elif (CRYSTAL_FREQ == 11059200)
    #define TIMER0_H  0xFC
    #define TIMER0_L  0xA7
#elif (CRYSTAL_FREQ == 6000000)
    #define TIMER0_H  0xFE
    #define TIMER0_L  0x0C
#else
    #warning "未定义该晶振频率的定时器初值，请手动计算并修改！"
    #define TIMER0_H  0xFC
    #define TIMER0_L  0x18
#endif

/* 端口定义 */
sbit KEY_MODE = P3^0;
sbit KEY_ADD  = P3^1;
sbit KEY_SUB  = P3^2;

/* 消隐电平定义 */
#if (DIGIT_POLARITY == 0)
    #define DIGIT_OFF     0xFF
    #define SEGMENT_OFF   0x00
#else
    #define DIGIT_OFF     0x00
    #define SEGMENT_OFF   0xFF
#endif

/* 共阴极段码表 */
#if (DIGIT_POLARITY == 0)
unsigned char code seg_table[] = {
    0x3F,  /* 0 */
    0x06,  /* 1 */
    0x5B,  /* 2 */
    0x4F,  /* 3 */
    0x66,  /* 4 */
    0x6D,  /* 5 */
    0x7D,  /* 6 */
    0x07,  /* 7 */
    0x7F,  /* 8 */
    0x6F   /* 9 */
};
unsigned char code seg_table_dp[] = {
    0xBF,  /* 0. */
    0x86,  /* 1. */
    0xDB,  /* 2. */
    0xCF,  /* 3. */
    0xE6,  /* 4. */
    0xED,  /* 5. */
    0xFD,  /* 6. */
    0x87,  /* 7. */
    0xFF,  /* 8. */
    0xEF   /* 9. */
};
#else
/* 共阳极段码表（共阴极取反） */
unsigned char code seg_table[] = {
    0xC0,  /* 0 */
    0xF9,  /* 1 */
    0xA4,  /* 2 */
    0xB0,  /* 3 */
    0x99,  /* 4 */
    0x92,  /* 5 */
    0x82,  /* 6 */
    0xF8,  /* 7 */
    0x80,  /* 8 */
    0x90   /* 9 */
};
unsigned char code seg_table_dp[] = {
    0x40,  /* 0. */
    0x79,  /* 1. */
    0x24,  /* 2. */
    0x30,  /* 3. */
    0x19,  /* 4. */
    0x12,  /* 5. */
    0x02,  /* 6. */
    0x78,  /* 7. */
    0x00,  /* 8. */
    0x10   /* 9. */
};
#endif

/* 位选码 */
#if (DIGIT_POLARITY == 0)
unsigned char code dig_table[] = {
    0xFE, 0xFD, 0xFB, 0xF7,
    0xEF, 0xDF, 0xBF, 0x7F
};
#else
unsigned char code dig_table[] = {
    0x01, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x80
};
#endif

/* 每月天数 */
unsigned char code month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* 时间变量 */
unsigned char year   = 25;   /* 年 (00-99, 表示2000-2099) */
unsigned char month  = 6;    /* 月 (1-12) */
unsigned char day    = 12;   /* 日 (1-31) */
unsigned char hour   = 12;   /* 时 (0-23) */
unsigned char minute = 0;    /* 分 (0-59) */
unsigned char second = 0;    /* 秒 (0-59) */
unsigned char weekday = 4;   /* 星期 (0=周日, 1=周一...6=周六) */

/* 显示相关 */
unsigned char disp_buf[8];    /* 显示缓冲区 */
unsigned char scan_index = 0; /* 当前扫描位 */
unsigned char display_mode = 0; /* 0=日期, 1=时间, 2=设置 */
unsigned char set_item = 0;   /* 设置项: 0=年,1=月,2=日,3=时,4=分,5=秒 */
unsigned char blink_flag = 0; /* 闪烁标志 */
unsigned char time_update_flag = 0; /* 1秒更新标志 */

/* 计数器 */
unsigned int ms_count = 0;    /* 毫秒计数 */
unsigned int blink_count = 0; /* 闪烁计数 */

/* 函数声明 */
void timer0_init(void);
void time_update(void);
void refresh_display(void);
void key_scan(void);
void delay_ms(unsigned int ms);
unsigned char is_leap_year(unsigned char y);

/* 定时器0中断服务 */
void Timer0_ISR(void) interrupt 1 {
    /* 重装初值 */
    TH0 = TIMER0_H;
    TL0 = TIMER0_L;

    /* 数码管扫描 */
    P2 = DIGIT_OFF;           /* 消隐 */
    P0 = SEGMENT_OFF;
    P0 = disp_buf[scan_index]; /* 输出段码 */
    P2 = dig_table[scan_index]; /* 输出位选 */
    scan_index++;
    if (scan_index > 7) scan_index = 0;

    /* 1ms计数 */
    ms_count++;
    if (ms_count >= 1000) {
        ms_count = 0;
        time_update_flag = 1;
    }

    /* 闪烁计数 (500ms) */
    blink_count++;
    if (blink_count >= 500) {
        blink_count = 0;
        blink_flag ^= 1;
    }
}

/* 主函数 */
void main(void) {
    timer0_init();
    EA = 1;
    refresh_display();

    while (1) {
        if (time_update_flag) {
            time_update_flag = 0;
            time_update();
        }
        refresh_display();
        key_scan();
    }
}

/* 定时器0初始化 */
void timer0_init(void) {
    TMOD &= 0xF0;       /* 清除定时器0模式位 */
    TMOD |= 0x01;       /* 设置定时器0为模式1(16位) */
    TH0 = TIMER0_H;
    TL0 = TIMER0_L;
    ET0 = 1;            /* 使能定时器0中断 */
    TR0 = 1;            /* 启动定时器0 */
}

/* 闰年判断 (2000-2099年范围) */
unsigned char is_leap_year(unsigned char y) {
    return (y % 4 == 0) ? 1 : 0;
}

/* 时间更新 */
void time_update(void) {
    unsigned char max_day;
    unsigned char leap;

    second++;
    if (second >= 60) {
        second = 0;
        minute++;
        if (minute >= 60) {
            minute = 0;
            hour++;
            if (hour >= 24) {
                hour = 0;
                day++;
                weekday++;
                if (weekday > 6) weekday = 0;

                leap = is_leap_year(year);
                max_day = month_days[month - 1];
                if (month == 2 && leap) max_day = 29;

                if (day > max_day) {
                    day = 1;
                    month++;
                    if (month > 12) {
                        month = 1;
                        year++;
                        if (year > 99) year = 0;
                    }
                }
            }
        }
    }
}

/* 刷新显示缓冲区 */
void refresh_display(void) {
    unsigned char i;
    unsigned char temp_buf[8];

    if (display_mode == 0) {
        /* 日期模式: YY.MM.DD. */
        temp_buf[0] = seg_table[year / 10];
        temp_buf[1] = seg_table_dp[year % 10];
        temp_buf[2] = seg_table[month / 10];
        temp_buf[3] = seg_table_dp[month % 10];
        temp_buf[4] = seg_table[day / 10];
        temp_buf[5] = seg_table_dp[day % 10];
        temp_buf[6] = SEGMENT_OFF;  /* 空 */
        temp_buf[7] = SEGMENT_OFF;  /* 空 */
    } else if (display_mode == 1) {
        /* 时间模式: HH.MM.SS. */
        temp_buf[0] = seg_table[hour / 10];
        temp_buf[1] = seg_table_dp[hour % 10];
        temp_buf[2] = seg_table[minute / 10];
        temp_buf[3] = seg_table_dp[minute % 10];
        temp_buf[4] = seg_table[second / 10];
        temp_buf[5] = seg_table_dp[second % 10];
        temp_buf[6] = SEGMENT_OFF;
        temp_buf[7] = SEGMENT_OFF;
    } else {
        /* 设置模式 */
        if (set_item < 3) {
            /* 设置日期项 */
            temp_buf[0] = seg_table[year / 10];
            temp_buf[1] = seg_table_dp[year % 10];
            temp_buf[2] = seg_table[month / 10];
            temp_buf[3] = seg_table_dp[month % 10];
            temp_buf[4] = seg_table[day / 10];
            temp_buf[5] = seg_table_dp[day % 10];
        } else {
            /* 设置时间项 */
            temp_buf[0] = seg_table[hour / 10];
            temp_buf[1] = seg_table_dp[hour % 10];
            temp_buf[2] = seg_table[minute / 10];
            temp_buf[3] = seg_table_dp[minute % 10];
            temp_buf[4] = seg_table[second / 10];
            temp_buf[5] = seg_table_dp[second % 10];
        }
        temp_buf[6] = SEGMENT_OFF;
        temp_buf[7] = SEGMENT_OFF;

        /* 闪烁处理 */
        if (!blink_flag) {
            if (set_item == 0) { temp_buf[0] = SEGMENT_OFF; temp_buf[1] = SEGMENT_OFF; }
            else if (set_item == 1) { temp_buf[2] = SEGMENT_OFF; temp_buf[3] = SEGMENT_OFF; }
            else if (set_item == 2) { temp_buf[4] = SEGMENT_OFF; temp_buf[5] = SEGMENT_OFF; }
            else if (set_item == 3) { temp_buf[0] = SEGMENT_OFF; temp_buf[1] = SEGMENT_OFF; }
            else if (set_item == 4) { temp_buf[2] = SEGMENT_OFF; temp_buf[3] = SEGMENT_OFF; }
            else if (set_item == 5) { temp_buf[4] = SEGMENT_OFF; temp_buf[5] = SEGMENT_OFF; }
        }
    }

    /* 复制到显示缓冲区 */
    for (i = 0; i < 8; i++) {
        disp_buf[i] = temp_buf[i];
    }
}

/* 按键扫描 */
void key_scan(void) {
    static unsigned char key_press = 0;

    if (KEY_MODE == 0 || KEY_ADD == 0 || KEY_SUB == 0) {
        delay_ms(20);  /* 消抖 */
        if (KEY_MODE == 0) {
            if (key_press == 0) {
                key_press = 1;
                /* 模式切换 */
                if (display_mode == 0) {
                    display_mode = 1; /* 切换到时间 */
                } else if (display_mode == 1) {
                    display_mode = 2; /* 进入设置 */
                    set_item = 0;
                } else {
                    set_item++;
                    if (set_item > 5) {
                        set_item = 0;
                        display_mode = 0; /* 退出设置 */
                    }
                }
                while (!KEY_MODE); /* 等待释放 */
                delay_ms(20);
            }
        } else if (KEY_ADD == 0) {
            if (key_press == 0 && display_mode == 2) {
                key_press = 1;
                switch (set_item) {
                    case 0: /* 年 */
                        year++;
                        if (year > 99) year = 0;
                        break;
                    case 1: /* 月 */
                        month++;
                        if (month > 12) month = 1;
                        break;
                    case 2: /* 日 */
                        day++;
                        {
                            unsigned char leap = is_leap_year(year);
                            unsigned char max_d = month_days[month - 1];
                            if (month == 2 && leap) max_d = 29;
                            if (day > max_d) day = 1;
                        }
                        break;
                    case 3: /* 时 */
                        hour++;
                        if (hour > 23) hour = 0;
                        break;
                    case 4: /* 分 */
                        minute++;
                        if (minute > 59) minute = 0;
                        break;
                    case 5: /* 秒 */
                        second++;
                        if (second > 59) second = 0;
                        break;
                }
                while (!KEY_ADD);
                delay_ms(20);
            }
        } else if (KEY_SUB == 0) {
            if (key_press == 0 && display_mode == 2) {
                key_press = 1;
                switch (set_item) {
                    case 0:
                        if (year == 0) year = 99; else year--;
                        break;
                    case 1:
                        if (month == 1) month = 12; else month--;
                        break;
                    case 2:
                        if (day == 1) {
                            unsigned char leap = is_leap_year(year);
                            unsigned char max_d = month_days[month - 1];
                            if (month == 2 && leap) max_d = 29;
                            day = max_d;
                        } else {
                            day--;
                        }
                        break;
                    case 3:
                        if (hour == 0) hour = 23; else hour--;
                        break;
                    case 4:
                        if (minute == 0) minute = 59; else minute--;
                        break;
                    case 5:
                        if (second == 0) second = 59; else second--;
                        break;
                }
                while (!KEY_SUB);
                delay_ms(20);
            }
        }
    } else {
        key_press = 0;
    }
}

/* 延时函数 (约 ms 毫秒 @ 12MHz) */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}
