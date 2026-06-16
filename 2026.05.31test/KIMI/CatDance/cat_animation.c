#include "cat_animation.h"
#include "tft_lcd.h"
#include "delay.h"

//========================================
// 绘制椭圆 (用于身体、头部等)
//========================================
static void DrawEllipse(uint16 cx, uint16 cy, uint16 rx, uint16 ry, uint16 color)
{
    int16 x, y;
    int16 rx2 = rx * rx;
    int16 ry2 = ry * ry;
    
    for(y = -ry; y <= ry; y++)
    {
        for(x = -rx; x <= rx; x++)
        {
            if((x * x * ry2 + y * y * rx2) <= (rx2 * ry2))
            {
                LCD_DrawPoint(cx + x, cy + y, color);
            }
        }
    }
}

//========================================
// 绘制小猫头部
//========================================
static void Cat_DrawHead(uint16 x, uint16 y, uint16 scale, uint16 color)
{
    uint16 r = 18 * scale / 10;
    // 头部主体
    LCD_FillCircle(x, y, r, color);
    
    // 耳朵 (左)
    LCD_FillTriangle(x - r + 2, y - r/2, x - r/2, y - r - 8, x - 2, y - r + 2, color);
    // 耳朵 (右)
    LCD_FillTriangle(x + r - 2, y - r/2, x + r/2, y - r - 8, x + 2, y - r + 2, color);
    
    // 耳朵内部粉色
    LCD_FillTriangle(x - r + 4, y - r/2, x - r/2, y - r - 4, x - 4, y - r + 2, CAT_PINK);
    LCD_FillTriangle(x + r - 4, y - r/2, x + r/2, y - r - 4, x + 4, y - r + 2, CAT_PINK);
}

//========================================
// 绘制小猫脸部
//========================================
static void Cat_DrawFace(uint16 x, uint16 y, uint16 scale, uint8 frame)
{
    uint16 r = 18 * scale / 10;
    int8 eye_offset = 0;
    
    // 根据帧调整眼睛位置 (眨眼效果)
    if(frame == 1 || frame == 3) eye_offset = 1;
    
    // 左眼
    LCD_FillCircle(x - r/2, y - 2 + eye_offset, 3, CAT_BLACK);
    LCD_FillCircle(x - r/2 + 1, y - 3 + eye_offset, 1, CAT_WHITE);
    
    // 右眼
    LCD_FillCircle(x + r/2, y - 2 + eye_offset, 3, CAT_BLACK);
    LCD_FillCircle(x + r/2 + 1, y - 3 + eye_offset, 1, CAT_WHITE);
    
    // 鼻子
    LCD_FillCircle(x, y + 2, 2, CAT_PINK);
    
    // 嘴巴
    LCD_DrawLine(x - 3, y + 5, x, y + 7, CAT_BLACK);
    LCD_DrawLine(x, y + 7, x + 3, y + 5, CAT_BLACK);
    
    // 胡须
    LCD_DrawLine(x - r - 2, y + 2, x - r/2 - 2, y + 3, CAT_BLACK);
    LCD_DrawLine(x - r - 2, y + 5, x - r/2 - 2, y + 5, CAT_BLACK);
    LCD_DrawLine(x + r/2 + 2, y + 3, x + r + 2, y + 2, CAT_BLACK);
    LCD_DrawLine(x + r/2 + 2, y + 5, x + r + 2, y + 5, CAT_BLACK);
}

//========================================
// 绘制小猫身体
//========================================
static void Cat_DrawBody(uint16 x, uint16 y, uint16 scale, uint16 color)
{
    uint16 w = 22 * scale / 10;
    uint16 h = 28 * scale / 10;
    
    // 身体椭圆
    DrawEllipse(x, y, w, h, color);
    
    // 肚子 (浅色)
    DrawEllipse(x, y + h/4, w - 4, h - 6, CAT_WHITE);
}

//========================================
// 绘制小猫尾巴
//========================================
static void Cat_DrawTail(uint16 x, uint16 y, uint16 scale, uint8 frame, uint16 color)
{
    uint16 tx, ty;
    int8 offset = 0;
    
    // 根据帧调整尾巴位置
    switch(frame)
    {
        case 0: offset = -8; break;
        case 1: offset = -12; break;
        case 2: offset = -6; break;
        case 3: offset = -10; break;
        case 4: offset = -4; break;
        case 5: offset = -14; break;
        case 6: offset = -8; break;
        case 7: offset = -12; break;
    }
    
    tx = x + 18 * scale / 10;
    ty = y - 15 * scale / 10 + offset;
    
    // 尾巴用几个圆连接
    LCD_FillCircle(tx, ty, 4 * scale / 10, color);
    LCD_FillCircle(tx + 3, ty - 4, 4 * scale / 10, color);
    LCD_FillCircle(tx + 6, ty - 8, 4 * scale / 10, color);
    LCD_FillCircle(tx + 8, ty - 12, 3 * scale / 10, color);
}

//========================================
// 绘制小猫前腿
//========================================
static void Cat_DrawFrontLegs(uint16 x, uint16 y, uint16 scale, uint8 frame, uint16 color)
{
    int8 left_offset = 0, right_offset = 0;
    uint16 leg_w = 5 * scale / 10;
    uint16 leg_h = 15 * scale / 10;
    
    // 根据帧调整腿部位置 (跳舞动作)
    switch(frame)
    {
        case 0: left_offset = 0; right_offset = 0; break;
        case 1: left_offset = -4; right_offset = 2; break;
        case 2: left_offset = -6; right_offset = 4; break;
        case 3: left_offset = -2; right_offset = 6; break;
        case 4: left_offset = 0; right_offset = 0; break;
        case 5: left_offset = 2; right_offset = -4; break;
        case 6: left_offset = 4; right_offset = -6; break;
        case 7: left_offset = 6; right_offset = -2; break;
    }
    
    // 左腿
    LCD_FillRect(x - 10 * scale / 10 + left_offset, y + 5, 
                 x - 5 * scale / 10 + left_offset, y + 5 + leg_h, color);
    LCD_FillCircle(x - 7 * scale / 10 + left_offset, y + 5 + leg_h, 3, color);
    
    // 右腿
    LCD_FillRect(x + 5 * scale / 10 + right_offset, y + 5, 
                 x + 10 * scale / 10 + right_offset, y + 5 + leg_h, color);
    LCD_FillCircle(x + 7 * scale / 10 + right_offset, y + 5 + leg_h, 3, color);
}

//========================================
// 绘制小猫后腿
//========================================
static void Cat_DrawBackLegs(uint16 x, uint16 y, uint16 scale, uint8 frame, uint16 color)
{
    int8 left_offset = 0, right_offset = 0;
    
    switch(frame)
    {
        case 0: left_offset = 0; right_offset = 0; break;
        case 1: left_offset = 2; right_offset = -4; break;
        case 2: left_offset = 4; right_offset = -6; break;
        case 3: left_offset = 6; right_offset = -2; break;
        case 4: left_offset = 0; right_offset = 0; break;
        case 5: left_offset = -4; right_offset = 2; break;
        case 6: left_offset = -6; right_offset = 4; break;
        case 7: left_offset = -2; right_offset = 6; break;
    }
    
    // 左后腿
    LCD_FillCircle(x - 14 * scale / 10 + left_offset, y + 18 * scale / 10, 5, color);
    // 右后腿
    LCD_FillCircle(x + 14 * scale / 10 + right_offset, y + 18 * scale / 10, 5, color);
}

//========================================
// 绘制单帧小猫
//========================================
void Cat_DrawFrame(uint8 frame, uint16 center_x, uint16 center_y, uint16 scale)
{
    uint16 head_y = center_y - 25 * scale / 10;
    uint16 body_y = center_y;
    
    // 绘制尾巴 (在身体后面)
    Cat_DrawTail(center_x, body_y, scale, frame, CAT_ORANGE);
    
    // 绘制后腿
    Cat_DrawBackLegs(center_x, body_y, scale, frame, CAT_ORANGE);
    
    // 绘制身体
    Cat_DrawBody(center_x, body_y, scale, CAT_ORANGE);
    
    // 绘制前腿
    Cat_DrawFrontLegs(center_x, body_y, scale, frame, CAT_ORANGE);
    
    // 绘制头部
    Cat_DrawHead(center_x, head_y, scale, CAT_ORANGE);
    
    // 绘制脸部
    Cat_DrawFace(center_x, head_y, scale, frame);
}

//========================================
// 清除小猫区域
//========================================
void Cat_ClearArea(uint16 center_x, uint16 center_y, uint16 scale)
{
    uint16 x1 = center_x - 35 * scale / 10;
    uint16 y1 = center_y - 50 * scale / 10;
    uint16 x2 = center_x + 35 * scale / 10;
    uint16 y2 = center_y + 35 * scale / 10;
    
    if(x1 > LCD_WIDTH) x1 = 0;
    if(y1 > LCD_HEIGHT) y1 = 0;
    if(x2 >= LCD_WIDTH) x2 = LCD_WIDTH - 1;
    if(y2 >= LCD_HEIGHT) y2 = LCD_HEIGHT - 1;
    
    LCD_FillRect(x1, y1, x2, y2, BG_COLOR);
}


