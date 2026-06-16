#include "config.h"
#include "tft_lcd.h"
#include "cat_animation.h"
#include "music.h"
#include "delay.h"

//========================================
// 全局变量 (使用 xdata 避免内部 RAM 溢出)
//========================================
xdata uint8 g_cat_frame;          // 当前动画帧
xdata uint16 g_music_index;       // 当前音乐索引
xdata uint8 g_frame_counter;      // 帧计数器

// 外部引用音乐数据
extern code uint16 LanHuaCao_Notes[];
extern code uint8 LanHuaCao_Durations[];
extern code uint16 SONG_LENGTH;

//========================================
// 绘制舞台背景
//========================================
void Draw_Stage(void)
{
    uint16 i;
    
    // 清屏为绿色草地
    LCD_Clear(BG_COLOR);
    
    // 绘制天空 (上半部分蓝色渐变)
    for(i = 0; i < 80; i++)
    {
        LCD_FillRect(0, i, LCD_WIDTH - 1, i, 0x0010 + (i << 5));
    }
    
    // 绘制太阳
    LCD_FillCircle(200, 40, 20, COLOR_YELLOW);
    LCD_FillCircle(200, 40, 15, COLOR_ORANGE);
    
    // 绘制云朵
    LCD_FillCircle(60, 35, 15, COLOR_WHITE);
    LCD_FillCircle(80, 30, 18, COLOR_WHITE);
    LCD_FillCircle(100, 35, 15, COLOR_WHITE);
    
    LCD_FillCircle(160, 55, 12, COLOR_WHITE);
    LCD_FillCircle(175, 50, 15, COLOR_WHITE);
    LCD_FillCircle(190, 55, 12, COLOR_WHITE);
    
    // 绘制草地装饰 (花朵)
    for(i = 0; i < 8; i++)
    {
        uint16 fx = 30 + i * 30;
        uint16 fy = 280 + (i % 3) * 10;
        
        // 花茎
        LCD_FillRect(fx, fy - 8, fx + 2, fy, COLOR_GREEN);
        // 花瓣
        LCD_FillCircle(fx + 1, fy - 10, 4, COLOR_RED);
        LCD_FillCircle(fx + 1, fy - 10, 2, COLOR_YELLOW);
    }
    
    // 绘制标题
    // 由于字体限制，用简单图形表示标题区域
    LCD_FillRect(60, 90, 180, 110, COLOR_BLACK);
    LCD_FillRect(62, 92, 178, 108, BG_COLOR);
}

//========================================
// 播放一个音符 (非阻塞式，使用延时)
//========================================
void Play_Note_NonBlocking(uint16 index)
{
    uint16 freq;
    uint16 duration;
    
    if(index >= SONG_LENGTH)
    {
        g_music_index = 0;
        return;
    }
    
    freq = LanHuaCao_Notes[index];
    duration = LanHuaCao_Durations[index] * 100;  // 缩短为100ms每拍，配合动画
    
    Music_PlayNote(freq, duration);
}

//========================================
// 主函数
//========================================
void main(void)
{
    uint16 cat_x;
    uint16 cat_y;
    uint16 scale;
    
    // 初始化全局变量 (xdata 不能在声明时初始化)
    g_cat_frame = 0;
    g_music_index = 0;
    g_frame_counter = 0;
    
    cat_x = LCD_WIDTH / 2;
    cat_y = LCD_HEIGHT / 2 + 30;
    scale = 10;
    
    // 初始化
    LCD_Init();
    Music_Init();
    
    // 绘制舞台背景
    Draw_Stage();
    
    // 主循环: 动画 + 音乐
    while(1)
    {
        // ===== 1. 清除上一帧小猫区域 =====
        Cat_ClearArea(cat_x, cat_y, scale);
        
        // ===== 2. 绘制新帧小猫 =====
        Cat_DrawFrame(g_cat_frame, cat_x, cat_y, scale);
        
        // ===== 3. 更新帧计数 =====
        g_cat_frame++;
        if(g_cat_frame >= 8) g_cat_frame = 0;
        
        // ===== 4. 播放音乐 (每帧播放2个音符) =====
        Play_Note_NonBlocking(g_music_index);
        g_music_index++;
        if(g_music_index >= SONG_LENGTH)
        {
            g_music_index = 0;
            delay_ms(300);  // 歌曲间停顿
        }
        
        // ===== 5. 帧延时 =====
        // 动画帧率约 150ms/帧，配合音乐节奏
        delay_ms(120);
    }
}
