#include "tft_lcd.h"
#include "delay.h"

//========================================
// 写命令 (16位模式)
//========================================
void LCD_WriteCmd(uint16 cmd)
{
    LCD_RS = 0;             // 命令模式
    LCD_CS = 0;             // 片选有效
    LCD_RD = 1;             // 读无效
    
    LCD_DATA_L = (uint8)(cmd & 0xFF);
    LCD_DATA_H = (uint8)(cmd >> 8);
    
    LCD_WR = 0;             // 写使能
    _nop_(); _nop_();
    LCD_WR = 1;             // 写结束
    LCD_CS = 1;             // 片选无效
}

//========================================
// 写数据 (16位模式)
//========================================
void LCD_WriteData(uint16 dat)
{
    LCD_RS = 1;             // 数据模式
    LCD_CS = 0;             // 片选有效
    LCD_RD = 1;             // 读无效
    
    LCD_DATA_L = (uint8)(dat & 0xFF);
    LCD_DATA_H = (uint8)(dat >> 8);
    
    LCD_WR = 0;             // 写使能
    _nop_(); _nop_();
    LCD_WR = 1;             // 写结束
    LCD_CS = 1;             // 片选无效
}

//========================================
// 写寄存器
//========================================
void LCD_WriteReg(uint16 reg, uint16 dat)
{
    LCD_WriteCmd(reg);
    LCD_WriteData(dat);
}

//========================================
// ILI9325D 初始化
//========================================
void LCD_Init(void)
{
    // 初始化引脚
    LCD_CS = 1;
    LCD_WR = 1;
    LCD_RD = 1;
    LCD_RS = 1;
    LCD_EN = 1;
    
    // 复位
    LCD_RST = 1;
    delay_ms(10);
    LCD_RST = 0;
    delay_ms(50);
    LCD_RST = 1;
    delay_ms(50);
    
    // ILI9325D 初始化序列
    LCD_WriteReg(0x0001, 0x0100);  // SS=1, 输出方向从S720到S1
    LCD_WriteReg(0x0002, 0x0700);  // 行反转, 列反转
    LCD_WriteReg(0x0003, 0x1030);  // BGR=1, AM=1 (横向), ID=10
    LCD_WriteReg(0x0004, 0x0000);  // 缩放控制
    LCD_WriteReg(0x0008, 0x0207);  // 显示控制2
    LCD_WriteReg(0x0009, 0x0000);  // 显示控制3
    LCD_WriteReg(0x000A, 0x0000);  // 帧信号输出
    LCD_WriteReg(0x000C, 0x0000);  // RGB接口控制
    LCD_WriteReg(0x000D, 0x0000);  // 帧标记位置
    LCD_WriteReg(0x000F, 0x0000);  // 交替控制
    
    delay_ms(10);
    
    // 电源控制
    LCD_WriteReg(0x0010, 0x0000);  // 电源控制1
    LCD_WriteReg(0x0011, 0x0007);  // 电源控制2
    LCD_WriteReg(0x0012, 0x0000);  // 电源控制3
    LCD_WriteReg(0x0013, 0x0000);  // 电源控制4
    
    delay_ms(200);
    
    LCD_WriteReg(0x0010, 0x1690);  // 电源控制1
    LCD_WriteReg(0x0011, 0x0227);  // 电源控制2
    
    delay_ms(50);
    
    LCD_WriteReg(0x0012, 0x008C);  // 电源控制3
    
    delay_ms(50);
    
    LCD_WriteReg(0x0013, 0x1500);  // 电源控制4
    LCD_WriteReg(0x0029, 0x0008);  // 电源控制7
    
    delay_ms(50);
    
    // 伽马校正
    LCD_WriteReg(0x0030, 0x0000);
    LCD_WriteReg(0x0031, 0x0707);
    LCD_WriteReg(0x0032, 0x0307);
    LCD_WriteReg(0x0035, 0x0200);
    LCD_WriteReg(0x0036, 0x0008);
    LCD_WriteReg(0x0037, 0x0004);
    LCD_WriteReg(0x0038, 0x0000);
    LCD_WriteReg(0x0039, 0x0707);
    LCD_WriteReg(0x003C, 0x0002);
    LCD_WriteReg(0x003D, 0x1D04);
    
    // 显示窗口设置
    LCD_WriteReg(0x0050, 0x0000);  // 水平起始
    LCD_WriteReg(0x0051, 0x00EF);  // 水平结束 (239)
    LCD_WriteReg(0x0052, 0x0000);  // 垂直起始
    LCD_WriteReg(0x0053, 0x013F);  // 垂直结束 (319)
    
    // 显示控制
    LCD_WriteReg(0x0060, 0xA700);  // 驱动输出控制
    LCD_WriteReg(0x0061, 0x0001);  // 基像显示控制
    LCD_WriteReg(0x006A, 0x0000);  // 垂直滚动控制
    
    // 部分图像控制
    LCD_WriteReg(0x0080, 0x0000);
    LCD_WriteReg(0x0081, 0x0000);
    LCD_WriteReg(0x0082, 0x0000);
    LCD_WriteReg(0x0083, 0x0000);
    LCD_WriteReg(0x0084, 0x0000);
    LCD_WriteReg(0x0085, 0x0000);
    
    // 面板控制
    LCD_WriteReg(0x0090, 0x0010);
    LCD_WriteReg(0x0092, 0x0600);
    LCD_WriteReg(0x0093, 0x0003);
    LCD_WriteReg(0x0095, 0x0110);
    LCD_WriteReg(0x0097, 0x0000);
    LCD_WriteReg(0x0098, 0x0000);
    
    // 开启显示
    LCD_WriteReg(0x0007, 0x0133);  // 显示控制 (D1=1, D0=1)
    
    delay_ms(50);
    
    // 打开背光
    LCD_LED = 1;
    
    // 清屏为绿色背景
    LCD_Clear(BG_COLOR);
}

//========================================
// 设置显示窗口
//========================================
void LCD_SetWindow(uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
    // 水平地址设置
    LCD_WriteReg(0x0050, x1);      // 水平起始地址
    LCD_WriteReg(0x0051, x2);      // 水平结束地址
    
    // 垂直地址设置
    LCD_WriteReg(0x0052, y1);      // 垂直起始地址
    LCD_WriteReg(0x0053, y2);      // 垂直结束地址
    
    // 设置光标位置
    LCD_WriteReg(0x0020, x1);      // 水平GRAM地址
    LCD_WriteReg(0x0021, y1);      // 垂直GRAM地址
}

//========================================
// 清屏
//========================================
void LCD_Clear(uint16 color)
{
    uint32 i;
    uint32 total = (uint32)LCD_WIDTH * LCD_HEIGHT;
    
    LCD_SetWindow(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
    LCD_WriteCmd(0x0022);          // 写GRAM命令
    
    for(i = 0; i < total; i++)
    {
        LCD_WriteData(color);
    }
}

//========================================
// 画点
//========================================
void LCD_DrawPoint(uint16 x, uint16 y, uint16 color)
{
    if(x >= LCD_WIDTH || y >= LCD_HEIGHT) return;
    
    LCD_SetWindow(x, y, x, y);
    LCD_WriteReg(0x0022, color);
}

//========================================
// 画线 (Bresenham算法)
//========================================
void LCD_DrawLine(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color)
{
    int16 dx, dy, sx, sy, err, e2;
    
    dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;
    
    while(1)
    {
        LCD_DrawPoint(x1, y1, color);
        if(x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if(e2 > -dy) { err -= dy; x1 += sx; }
        if(e2 < dx)  { err += dx; y1 += sy; }
    }
}

//========================================
// 填充矩形
//========================================
void LCD_FillRect(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 color)
{
    uint16 x, y;
    
    if(x1 > x2) { x = x1; x1 = x2; x2 = x; }
    if(y1 > y2) { y = y1; y1 = y2; y2 = y; }
    
    LCD_SetWindow(x1, y1, x2, y2);
    LCD_WriteCmd(0x0022);
    
    for(y = y1; y <= y2; y++)
    {
        for(x = x1; x <= x2; x++)
        {
            LCD_WriteData(color);
        }
    }
}

//========================================
// 填充圆
//========================================
void LCD_FillCircle(uint16 x, uint16 y, uint16 r, uint16 color)
{
    int16 x0, y0;
    
    for(y0 = -r; y0 <= r; y0++)
    {
        for(x0 = -r; x0 <= r; x0++)
        {
            if(x0 * x0 + y0 * y0 <= r * r)
            {
                LCD_DrawPoint(x + x0, y + y0, color);
            }
        }
    }
}

//========================================
// 填充三角形
//========================================
void LCD_FillTriangle(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 x3, uint16 y3, uint16 color)
{
    uint16 y, x_start, x_end;
    int16 dx1, dx2, dx3;
    int16 x1_temp, x2_temp;
    uint16 y_min, y_max;
    
    // 找到y范围
    y_min = y1; y_max = y1;
    if(y2 < y_min) y_min = y2;
    if(y2 > y_max) y_max = y2;
    if(y3 < y_min) y_min = y3;
    if(y3 > y_max) y_max = y3;
    
    for(y = y_min; y <= y_max; y++)
    {
        x_start = 255; x_end = 0;
        
        // 边1-2
        if((y1 <= y && y < y2) || (y2 <= y && y < y1) || y == y1 || y == y2)
        {
            if(y1 != y2)
            {
                x1_temp = x1 + (int16)(y - y1) * (x2 - x1) / (y2 - y1);
                if(x1_temp < x_start) x_start = x1_temp;
                if(x1_temp > x_end) x_end = x1_temp;
            }
        }
        
        // 边2-3
        if((y2 <= y && y < y3) || (y3 <= y && y < y2) || y == y2 || y == y3)
        {
            if(y2 != y3)
            {
                x2_temp = x2 + (int16)(y - y2) * (x3 - x2) / (y3 - y2);
                if(x2_temp < x_start) x_start = x2_temp;
                if(x2_temp > x_end) x_end = x2_temp;
            }
        }
        
        // 边3-1
        if((y3 <= y && y < y1) || (y1 <= y && y < y3) || y == y3 || y == y1)
        {
            if(y3 != y1)
            {
                x1_temp = x3 + (int16)(y - y3) * (x1 - x3) / (y1 - y3);
                if(x1_temp < x_start) x_start = x1_temp;
                if(x1_temp > x_end) x_end = x1_temp;
            }
        }
        
        if(x_start <= x_end)
        {
            LCD_DrawLine(x_start, y, x_end, y, color);
        }
    }
}


