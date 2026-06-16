#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <reg52.h>
#include <intrins.h>

//========================================
// TFT LCD 引脚定义 (ILI9325D 2.6寸)
//========================================
// 数据总线 - 16位并口
#define LCD_DATA_L  P0      // DB0-DB7
#define LCD_DATA_H  P2      // DB8-DB15

// 控制引脚
sbit LCD_RS   = P3^0;       // 数据/命令选择 (0=命令, 1=数据)
sbit LCD_WR   = P3^1;       // 写使能 (低电平有效)
sbit LCD_RD   = P3^2;       // 读使能 (低电平有效)
sbit LCD_CS   = P3^3;       // 片选 (低电平有效)
sbit LCD_RST  = P3^4;       // 复位 (低电平有效)
sbit LCD_EN   = P3^5;       // 使能

// 蜂鸣器引脚
sbit BEEP     = P1^0;

// 背光控制 (可选)
sbit LCD_LED  = P1^1;

//========================================
// 颜色定义 (16位 RGB565)
//========================================
#define COLOR_BLACK     0x0000
#define COLOR_WHITE     0xFFFF
#define COLOR_RED       0xF800
#define COLOR_GREEN     0x07E0
#define COLOR_BLUE      0x001F
#define COLOR_YELLOW    0xFFE0
#define COLOR_CYAN      0x07FF
#define COLOR_MAGENTA   0xF81F
#define COLOR_ORANGE    0xFC00
#define COLOR_PINK      0xF81F
#define COLOR_GRAY      0x8410
#define COLOR_DARKGRAY  0x4208
#define COLOR_BROWN     0x8C00

// 小猫颜色
#define CAT_ORANGE      0xFC00
#define CAT_ORANGE_DARK 0xE880
#define CAT_WHITE       0xFFFF
#define CAT_PINK        0xF81F
#define CAT_BLACK       0x0000
#define BG_COLOR        0x07E0  // 绿色背景

// 屏幕尺寸
#define LCD_WIDTH       240
#define LCD_HEIGHT      320

//========================================
// 常用类型定义
//========================================
#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint16
#define uint16 unsigned int
#endif

#ifndef uint32
#define uint32 unsigned long
#endif

#ifndef int8
#define int8   char
#endif

#ifndef int16
#define int16  int
#endif

#endif // __CONFIG_H__
