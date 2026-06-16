#ifndef __TFT_CAT_H__
#define __TFT_CAT_H__

#include "Delay.h"

#define TFT_WIDTH   240
#define TFT_HEIGHT  320

#define BLACK       0x0000
#define WHITE       0xFFFF
#define RED         0xF800
#define GREEN       0x07E0
#define BLUE        0x001F
#define YELLOW      0xFFE0
#define ORANGE      0xFC00
#define PINK        0xF81F

void SPI_SendByte(unsigned char dat);
void TFT_WriteCmd(unsigned char cmd);
void TFT_WriteData(unsigned char dat);
void TFT_WriteWord(unsigned int dat);
void TFT_Init(void);
void TFT_SetWindow(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void TFT_Clear(unsigned int color);
void TFT_DrawPixel(unsigned int x, unsigned int y, unsigned int color);
void TFT_FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);
void TFT_FillCircle(unsigned int x, unsigned int y, unsigned int r, unsigned int color);
void Draw_Cat(unsigned int x, unsigned int y, unsigned char frame);
void Clear_CatArea(unsigned int x, unsigned int y);
void Cat_Dance_Animate(void);
void TFT_Cat_Init(void);

#endif
