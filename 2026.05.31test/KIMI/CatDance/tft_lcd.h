#ifndef __TFT_LCD_H__
#define __TFT_LCD_H__

#include "config.h"

// TFT LCD 函数声明
void LCD_Init(void);
void LCD_WriteCmd(uint16 cmd);
void LCD_WriteData(uint16 dat);
void LCD_WriteReg(uint16 reg, uint16 dat);
uint16 LCD_ReadData(void);

void LCD_SetWindow(uint16 x1, uint16 y1, uint16 x2, uint16 y2);
void LCD_Clear(uint16 color);
void LCD_DrawPoint(uint16 x, uint16 y, uint16 color);
void LCD_DrawLine(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color);
void LCD_FillRect(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color);
void LCD_FillCircle(uint16 x, uint16 y, uint16 r, uint16 color);
void LCD_FillTriangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 x3, uint16 y3, uint16 color);

#endif // __TFT_LCD_H__
