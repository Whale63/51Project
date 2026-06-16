///*
// * buzzer_music.c
// * 蜂鸣器驱动 + 《兰花草》经典部分循环播放
// * 接口：J7 (P2^0) 控制 PNP 三极管，低电平触发
// * 音符：简谱 1=C，经典部分
// */

#include <reg51.h>
#include "Delay.h"

// 蜂鸣器引脚（低电平触发）
sbit BUZZER = P2^0;

// ==================== 音符频率表 ====================
// 基于12MHz晶振，定时器初值计算

// 音阶频率 (Hz)
#define NOTE_REST   0
#define NOTE_L1     262   // 低音1 Do
#define NOTE_L2     294   // 低音2 Re
#define NOTE_L3     330   // 低音3 Mi
#define NOTE_L4     349   // 低音4 Fa
#define NOTE_L5     392   // 低音5 Sol
#define NOTE_L6     440   // 低音6 La
#define NOTE_L7     494   // 低音7 Si
#define NOTE_1      523   // 中音1 Do
#define NOTE_2      587   // 中音2 Re
#define NOTE_3      659   // 中音3 Mi
#define NOTE_4      698   // 中音4 Fa
#define NOTE_5      784   // 中音5 Sol
#define NOTE_6      880   // 中音6 La
#define NOTE_7      988   // 中音7 Si
#define NOTE_H1     1047  // 高音1 Do

// 速度：四分音符 = 300ms（加快节奏，更清晰）
#define TEMPO_MS    300

// ==================== 音符结构 ====================

typedef struct {
    unsigned int freq;      // 频率
    unsigned char beat;     // 节拍倍数 (1=四分音符)
} Note;

// ==================== 《兰花草》经典部分 ====================
// 简谱：
// 6 6 6 5 3 5 6 - | 6 6 6 5 3 5 2 -
// 3 3 2 1 6 1 2 - | 3 2 1 6 5 - - -

code Note music_lancao[] = {
    // 第一乐句：6 6 6 5 3 5 6 -
    {NOTE_6, 1}, {NOTE_6, 1}, {NOTE_6, 1}, {NOTE_5, 1},
    {NOTE_3, 1}, {NOTE_5, 1}, {NOTE_6, 2},
    
    // 第二乐句：6 6 6 5 3 5 2 -
    {NOTE_6, 1}, {NOTE_6, 1}, {NOTE_6, 1}, {NOTE_5, 1},
    {NOTE_3, 1}, {NOTE_5, 1}, {NOTE_2, 2},
    
    // 第三乐句：3 3 2 1 6 1 2 -
    {NOTE_3, 1}, {NOTE_3, 1}, {NOTE_2, 1}, {NOTE_1, 1},
    {NOTE_L6, 1}, {NOTE_1, 1}, {NOTE_2, 2},
    
    // 第四乐句：3 2 1 6 5 - - -
    {NOTE_3, 1}, {NOTE_2, 1}, {NOTE_1, 1}, {NOTE_L6, 1},
    {NOTE_L5, 4}, {NOTE_REST, 4},
};

#define MUSIC_LEN   (sizeof(music_lancao) / sizeof(Note))

// ==================== 定时器产生方波 ====================

// 定时器0中断：产生音符频率
unsigned int timer_reload = 0;      // 定时器重载值
unsigned char sound_enable = 0;       // 发声标志

void T0_ISR(void) interrupt 1
{
    if(sound_enable)
    {
        TH0 = timer_reload >> 8;
        TL0 = timer_reload & 0xFF;
        BUZZER = ~BUZZER;           // 翻转蜂鸣器
    }
}

// 计算定时器初值（12MHz晶振，12分频）
// 周期 = 1/freq，半周期 = 500000/freq (us)
// 机器周期 = 1us，计数次数 = 500000/freq
// 初值 = 65536 - 500000/freq
void Set_Note(unsigned int freq)
{
    unsigned int count;
    
    if(freq == 0)
    {
        sound_enable = 0;
        BUZZER = 1;     // 停止时拉高（三极管截止）
        return;
    }
    
    // 计算半周期计数值
    count = 500000 / freq;
    timer_reload = 65536 - count;
    
    TH0 = timer_reload >> 8;
    TL0 = timer_reload & 0xFF;
    sound_enable = 1;
}

// 延时指定节拍
void Delay_Beat(unsigned char beat)
{
    unsigned int ms = beat * TEMPO_MS;
    while(ms--)
    {
        DelayMS(1);
    }
}

// ==================== 播放控制 ====================

// 播放一次完整乐谱
void Play_Music(void)
{
    unsigned char i;
    for(i = 0; i < MUSIC_LEN; i++)
    {
        Set_Note(music_lancao[i].freq);
        Delay_Beat(music_lancao[i].beat);
        // 音符间短暂休止，避免粘连
        Set_Note(NOTE_REST);
        DelayMS(30);
    }
}

// 循环播放（主循环调用）
void Buzzer_Loop(void)
{
    Play_Music();
    DelayMS(800);       // 曲间停顿
}

// ==================== 初始化 ====================

void Buzzer_Init(void)
{
    BUZZER = 1;         // 初始高电平，蜂鸣器不响
    
    TMOD = 0x01;        // T0模式1，16位定时
    TH0 = 0xFC;         // 初始值，避免首次中断异常
    TL0 = 0x18;
    ET0 = 1;            // 使能T0中断
    TR0 = 1;            // 启动T0
    EA = 1;             // 开总中断
}