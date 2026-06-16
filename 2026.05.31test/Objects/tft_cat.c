///*
// * tft_cat.c
// * 2.6寸 TFT (ILI9325D) 驱动 + 小猫跳舞动画
// * 接口：SPI (CS/CLK/DI/DO)
// * 分辨率：240x320
// */

//#include <reg51.h>
//#include "Delay.h"
//#include "tft_cat.h"


////// ==================== TFT 引脚定义 ====================
////sbit TFT_CS   = P1^0;   // 片选
////sbit TFT_CLK  = P1^1;   // 时钟
////sbit TFT_DI   = P1^2;   // 数据输入(MOSI)
////sbit TFT_DO   = P1^3;   // 数据输出(MISO)
////sbit TFT_RST  = P1^4;   // 复位
////sbit TFT_RS   = P1^5;   // 命令/数据选择 (0=命令, 1=数据)

//// 屏幕尺寸
//#define TFT_WIDTH   240
//#define TFT_HEIGHT  320

//// 颜色定义 (RGB565)
//#define BLACK       0x0000
//#define WHITE       0xFFFF
//#define RED         0xF800
//#define GREEN       0x07E0
//#define BLUE        0x001F
//#define YELLOW      0xFFE0
//#define ORANGE      0xFC00
//#define PINK        0xF81F
//#define GRAY        0x8410
//#define DARK_GRAY   0x4208

//// ==================== SPI 底层通信 ====================

//// SPI 发送一个字节
//void SPI_SendByte(unsigned char dat)
//{
//    unsigned char i;
//    for(i = 0; i < 8; i++)
//    {
//        TFT_CLK = 0;
//        if(dat & 0x80) TFT_DI = 1;
//        else           TFT_DI = 0;
//        dat <<= 1;
//        TFT_CLK = 1;
//    }
//}

//// 发送命令
//void TFT_WriteCmd(unsigned char cmd)
//{
//    TFT_RS = 0;         // 命令模式
//    TFT_CS = 0;
//    SPI_SendByte(cmd);
//    TFT_CS = 1;
//}

//// 发送数据
//void TFT_WriteData(unsigned char dat)
//{
//    TFT_RS = 1;         // 数据模式
//    TFT_CS = 0;
//    SPI_SendByte(dat);
//    TFT_CS = 1;
//}

//// 发送16位数据
//void TFT_WriteWord(unsigned int dat)
//{
//    TFT_WriteData(dat >> 8);
//    TFT_WriteData(dat & 0xFF);
//}





//// ==================== 绘图函数 ====================

//// 设置绘图窗口
//void TFT_SetWindow(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
//{
//    TFT_WriteCmd(0x20); TFT_WriteData(x1 >> 8); TFT_WriteData(x1 & 0xFF); // 列地址
//    TFT_WriteCmd(0x21); TFT_WriteData(y1 >> 8); TFT_WriteData(y1 & 0xFF); // 行地址
//    TFT_WriteCmd(0x22); // 写GRAM
//}

//// 清屏
//void TFT_Clear(unsigned int color)
//{
//    unsigned int i, j;
//    TFT_SetWindow(0, 0, TFT_WIDTH-1, TFT_HEIGHT-1);
//    TFT_RS = 1;
//    TFT_CS = 0;
//    for(i = 0; i < TFT_HEIGHT; i++)
//    {
//        for(j = 0; j < TFT_WIDTH; j++)
//        {
//            SPI_SendByte(color >> 8);
//            SPI_SendByte(color & 0xFF);
//        }
//    }
//    TFT_CS = 1;
//}

//// 画点
//void TFT_DrawPixel(unsigned int x, unsigned int y, unsigned int color)
//{
//    if(x >= TFT_WIDTH || y >= TFT_HEIGHT) return;
//    TFT_SetWindow(x, y, x, y);
//    TFT_WriteWord(color);
//}

//// 画填充矩形
//void TFT_FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
//{
//    unsigned int i, j;
//    TFT_SetWindow(x, y, x+w-1, y+h-1);
//    TFT_RS = 1;
//    TFT_CS = 0;
//    for(i = 0; i < h; i++)
//    {
//        for(j = 0; j < w; j++)
//        {
//            SPI_SendByte(color >> 8);
//            SPI_SendByte(color & 0xFF);
//        }
//    }
//    TFT_CS = 1;
//}

//// 画圆（填充）
//void TFT_FillCircle(unsigned int x, unsigned int y, unsigned int r, unsigned int color)
//{
//    int dx, dy;
//    for(dy = -r; dy <= r; dy++)
//    {
//        for(dx = -r; dx <= r; dx++)
//        {
//            if(dx*dx + dy*dy <= r*r)
//            {
//                TFT_DrawPixel(x+dx, y+dy, color);
//            }
//        }
//    }
//}

//// ==================== 小猫动画 ====================

//// 小猫颜色
//#define CAT_BODY    ORANGE
//#define CAT_HEAD    YELLOW
//#define CAT_EAR     PINK
//#define CAT_EYE     WHITE
//#define CAT_PUPIL   BLACK
//#define CAT_NOSE    PINK
//#define CAT_LEG     ORANGE
//#define CAT_TAIL    ORANGE

//// 帧计数
//unsigned char cat_frame = 0;

//// 画小猫（简化版，用几何图形组合）
//// x,y: 中心位置, frame: 动画帧 0~3
//void Draw_Cat(unsigned int x, unsigned int y, unsigned char frame)
//{
//    unsigned int offset = 0;
//    
//    // 根据帧计算偏移（跳舞动作）
//    switch(frame)
//    {
//        case 0: offset = 0; break;
//        case 1: offset = 5; break;
//        case 2: offset = 0; break;
//        case 3: offset = -5; break;
//    }

//    // 身体（椭圆）
//    TFT_FillRect(x-25, y+offset, 50, 40, CAT_BODY);
//    
//    // 头（圆）
//    TFT_FillCircle(x, y-25+offset, 25, CAT_HEAD);
//    
//    // 耳朵（三角形简化：小矩形）
//    TFT_FillRect(x-20, y-45+offset, 12, 15, CAT_EAR);
//    TFT_FillRect(x+8, y-45+offset, 12, 15, CAT_EAR);
//    
//    // 眼睛
//    TFT_FillCircle(x-10, y-30+offset, 5, CAT_EYE);
//    TFT_FillCircle(x+10, y-30+offset, 5, CAT_EYE);
//    TFT_FillCircle(x-10, y-30+offset, 2, CAT_PUPIL);
//    TFT_FillCircle(x+10, y-30+offset, 2, CAT_PUPIL);
//    
//    // 鼻子
//    TFT_FillRect(x-3, y-22+offset, 6, 4, CAT_NOSE);
//    
//    // 腿（根据帧摆动）
//    if(frame == 0 || frame == 2)
//    {
//        TFT_FillRect(x-20, y+35, 10, 15, CAT_LEG);
//        TFT_FillRect(x+10, y+35, 10, 15, CAT_LEG);
//    }
//    else if(frame == 1)
//    {
//        TFT_FillRect(x-25, y+30, 10, 15, CAT_LEG);  // 左腿抬起
//        TFT_FillRect(x+10, y+35, 10, 15, CAT_LEG);
//    }
//    else
//    {
//        TFT_FillRect(x-20, y+35, 10, 15, CAT_LEG);
//        TFT_FillRect(x+15, y+30, 10, 15, CAT_LEG);  // 右腿抬起
//    }
//    
//    // 尾巴（摆动）
//    if(frame == 0 || frame == 2)
//    {
//        TFT_FillRect(x+25, y+10, 20, 6, CAT_TAIL);
//    }
//    else
//    {
//        TFT_FillRect(x+25, y+5, 20, 6, CAT_TAIL);
//    }
//}

//// 清小猫区域
//void Clear_CatArea(unsigned int x, unsigned int y)
//{
//    TFT_FillRect(x-40, y-50, 90, 110, BLACK);
//}

//// 小猫跳舞动画（主循环调用）
//void Cat_Dance_Animate(void)
//{
//    static unsigned int cat_x = 120;
//    static unsigned int cat_y = 160;
//    
//    Clear_CatArea(cat_x, cat_y);
//    Draw_Cat(cat_x, cat_y, cat_frame);
//    
//    cat_frame++;
//    if(cat_frame >= 4) cat_frame = 0;
//    
//    DelayMS(200);   // 每帧200ms
//}





//// ==================== TFT 初始化 (ILI9325D) ====================
//	void TFT_Init(void)
//{
//    // 硬件复位
//    TFT_RST = 1;
//    DelayMS(10);
//    TFT_RST = 0;
//    DelayMS(50);
//    TFT_RST = 1;
//    DelayMS(50);

//    // ILI9325D 初始化序列
//    TFT_WriteCmd(0x01);     // 软件复位
//    DelayMS(10);

//    TFT_WriteCmd(0xE5); TFT_WriteData(0x78); TFT_WriteData(0x78); // SRAM内部设定
//    TFT_WriteCmd(0xE1); TFT_WriteData(0x00); TFT_WriteData(0x00); // 停止自动调节
//    TFT_WriteCmd(0x00); TFT_WriteData(0x00); TFT_WriteData(0x00); // 开始振荡
//    DelayMS(10);

//    // 电源设定
//    TFT_WriteCmd(0x10); TFT_WriteData(0x00); TFT_WriteData(0x00); // 退出睡眠
//    TFT_WriteCmd(0x11); TFT_WriteData(0x00); TFT_WriteData(0x00); // 退出待机
//    TFT_WriteCmd(0x12); TFT_WriteData(0x00); TFT_WriteData(0x00); // 内部工作
//    TFT_WriteCmd(0x13); TFT_WriteData(0x00); TFT_WriteData(0x00); // 放大器设定

//    // 显示设定
//    TFT_WriteCmd(0x01); TFT_WriteData(0x01); TFT_WriteData(0x1C); // 驱动输出控制
//    TFT_WriteCmd(0x02); TFT_WriteData(0x01); TFT_WriteData(0x00); // 波形控制
//    TFT_WriteCmd(0x03); TFT_WriteData(0x10); TFT_WriteData(0x30); // 入口模式：BGR, 横向
//    TFT_WriteCmd(0x08); TFT_WriteData(0x08); TFT_WriteData(0x08); // 显示控制2
//    TFT_WriteCmd(0x09); TFT_WriteData(0x00); TFT_WriteData(0x00); // 显示控制3
//    TFT_WriteCmd(0x0A); TFT_WriteData(0x00); TFT_WriteData(0x00); // 显示控制4

//    // 帧率控制
//    TFT_WriteCmd(0x0C); TFT_WriteData(0x00); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x0D); TFT_WriteData(0x00); TFT_WriteData(0x00);

//    // 窗口设定
//    TFT_WriteCmd(0x50); TFT_WriteData(0x00); TFT_WriteData(0x00); // 水平起始
//    TFT_WriteCmd(0x51); TFT_WriteData(0x00); TFT_WriteData(0xEF); // 水平结束 (239)
//    TFT_WriteCmd(0x52); TFT_WriteData(0x00); TFT_WriteData(0x00); // 垂直起始
//    TFT_WriteCmd(0x53); TFT_WriteData(0x01); TFT_WriteData(0x3F); // 垂直结束 (319)

//    // 面板控制
//    TFT_WriteCmd(0x60); TFT_WriteData(0x27); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x61); TFT_WriteData(0x00); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x6A); TFT_WriteData(0x00); TFT_WriteData(0x00);

//    // 电源设定
//    TFT_WriteCmd(0x90); TFT_WriteData(0x00); TFT_WriteData(0x10);
//    TFT_WriteCmd(0x92); TFT_WriteData(0x00); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x93); TFT_WriteData(0x00); TFT_WriteData(0x00);

//    // 伽马校正
//    TFT_WriteCmd(0x30); TFT_WriteData(0x00); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x31); TFT_WriteData(0x07); TFT_WriteData(0x07);
//    TFT_WriteCmd(0x32); TFT_WriteData(0x03); TFT_WriteData(0x07);
//    TFT_WriteCmd(0x35); TFT_WriteData(0x02); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x36); TFT_WriteData(0x02); TFT_WriteData(0x07);
//    TFT_WriteCmd(0x37); TFT_WriteData(0x00); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x38); TFT_WriteData(0x00); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x39); TFT_WriteData(0x00); TFT_WriteData(0x07);
//    TFT_WriteCmd(0x3C); TFT_WriteData(0x00); TFT_WriteData(0x00);
//    TFT_WriteCmd(0x3D); TFT_WriteData(0x00); TFT_WriteData(0x00);

//    // 开启显示
//    TFT_WriteCmd(0x07); TFT_WriteData(0x01); TFT_WriteData(0x33); // 显示控制
//    DelayMS(50);

//    TFT_Clear(BLACK);
//}
//// ==================== 初始化入口 ====================
//void TFT_Cat_Init(void)
//{

//    TFT_Init();
//    TFT_Clear(BLACK);
//    
//    // 显示标题
//    // 这里可以添加文字显示函数
//}

