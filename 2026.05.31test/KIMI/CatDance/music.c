#include "music.h"
#include "delay.h"

//========================================
// 音符频率表 (C大调, 4/5/6八度)
//========================================
// 低音
#define L1  262   // Do
#define L1S 277   // Do#
#define L2  294   // Re
#define L2S 311   // Re#
#define L3  330   // Mi
#define L4  349   // Fa
#define L4S 370   // Fa#
#define L5  392   // Sol
#define L5S 415   // Sol#
#define L6  440   // La
#define L6S 466   // La#
#define L7  494   // Si

// 中音
#define M1  523   // Do
#define M1S 554   // Do#
#define M2  587   // Re
#define M2S 622   // Re#
#define M3  659   // Mi
#define M4  698   // Fa
#define M4S 740   // Fa#
#define M5  784   // Sol
#define M5S 831   // Sol#
#define M6  880   // La
#define M6S 932   // La#
#define M7  988   // Si

// 高音
#define H1  1047  // Do
#define H1S 1109  // Do#
#define H2  1175  // Re
#define H2S 1245  // Re#
#define H3  1319  // Mi
#define H4  1397  // Fa
#define H4S 1480  // Fa#
#define H5  1568  // Sol
#define H5S 1661  // Sol#
#define H6  1760  // La
#define H6S 1865  // La#
#define H7  1976  // Si

// 休止符
#define REST 0

// 速度定义 (拍子时长 ms)
#define SPEED 400

//========================================
// 《兰花草》经典部分简谱数据
// 旋律: 5 6 5 3 | 5 6 5 2 | 3 5 3 2 | 1 6 1 2 |
//       3 3 2 1 | 6 1 2 3 | 5 - - - | ...
//========================================
code uint16 LanHuaCao_Notes[] = {
    // 第一段: 我从山中来 带着兰花草
    M5, M6, M5, M3,
    M5, M6, M5, M2,
    M3, M5, M3, M2,
    M1, L6, M1, M2,
    
    // 第二段: 种在小园中 希望花开早
    M3, M3, M2, M1,
    L6, M1, M2, M3,
    M5, M5, M3, M2,
    M3, M2, M1, L7,
    
    // 第三段: 一日看三回 看得花时过
    M1, M2, M3, M5,
    M3, M2, M1, M2,
    M3, M3, M2, M1,
    L6, L6, M1, M2,
    
    // 第四段: 兰花却依然 苞也无一个
    M3, M2, M1, L6,
    L5, L6, M1, M2,
    M3, M5, M3, M2,
    M1, M1, M2, M3,
    
    // 结尾重复经典段
    M5, M6, M5, M3,
    M5, M6, M5, M2,
    M3, M5, M3, M2,
    M1, L6, M1, M2,
    
    M3, M3, M2, M1,
    L6, M1, M2, M3,
    M5, REST, REST, REST,
};

// 音符时长 (1=四分音符, 2=二分音符, 4=全音符等, 用倍数表示)
code uint8 LanHuaCao_Durations[] = {
    // 第一段
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    
    // 第二段
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    
    // 第三段
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    
    // 第四段
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    
    // 结尾
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    
    1, 1, 1, 1,
    1, 1, 1, 1,
    2, 2, 2, 2,
};

#define SONG_LENGTH_CONST (sizeof(LanHuaCao_Notes) / sizeof(LanHuaCao_Notes[0]))

// 导出歌曲长度 (供外部引用)
code uint16 SONG_LENGTH = SONG_LENGTH_CONST;

// 定时器计数变量
static volatile uint16 timer_count = 0;
static volatile uint16 timer_target = 0;
static volatile uint8 beep_state = 0;

//========================================
// 音乐初始化 (定时器0)
//========================================
void Music_Init(void)
{
    // 定时器0初始化 (模式1, 16位定时器)
    TMOD &= 0xF0;       // 清除定时器0模式位
    TMOD |= 0x01;       // 设置定时器0为模式1 (16位)
    TH0 = 0;
    TL0 = 0;
    ET0 = 1;            // 使能定时器0中断
    EA = 1;             // 使能总中断
    
    BEEP = 0;           // 蜂鸣器初始关闭
}

//========================================
// 定时器0中断服务程序
//========================================
void Timer0_ISR(void) interrupt 1
{
    // 重装定时器值
    TH0 = (65536 - timer_target) >> 8;
    TL0 = (65536 - timer_target) & 0xFF;
    
    // 翻转蜂鸣器状态
    beep_state = !beep_state;
    BEEP = beep_state;
}

//========================================
// 播放单个音符 (使用定时器中断精确产生方波)
// freq: 频率(Hz), 0=休止符
// duration_ms: 时长(ms)
//========================================
void Music_PlayNote(uint16 freq, uint16 duration_ms)
{
    if(freq == 0)  // 休止符
    {
        TR0 = 0;            // 关闭定时器
        BEEP = 0;
        delay_ms(duration_ms);
        return;
    }
    
    // 计算半周期延时 (us)
    // 12MHz晶振, 机器周期 = 1us
    delay_us_val = 500000 / freq;  // 半周期 us
    
    // 计算需要翻转的次数
    // duration_ms * 1000 / (delay_us_val * 2) = 总周期数
    for(i = 0; i < duration_ms * 1000 / (delay_us_val * 2); i++)
    {
        BEEP = 1;
        delay_us(delay_us_val);
        BEEP = 0;
        delay_us(delay_us_val);
    }
}


