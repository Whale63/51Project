//#include <reg51.h>
//#include "Delay.h"

//unsigned char code LED_TABLE[8] = {   // 共阳单灯点亮码表
//    ~0x01,  // P0.0亮  0xFE
//    ~0x02,  // P0.1亮  0xFD
//    ~0x04,  // P0.2亮  0xFB
//    ~0x08,  // P0.3亮  0xF7
//    ~0x10,  // P0.4亮  0xEF
//    ~0x20,  // P0.5亮  0xDF
//    ~0x40,  // P0.6亮  0xBF
//    ~0x80   // P0.7亮  0x7F
//};

//unsigned char pos = 0;      // 当前点亮的灯位置 0~7

// 外部中断0：向左移动1步（P0.0→P0.7方向）
//void EX0_ISR(void) interrupt 0
//{
//    if(pos < 7) {
//        pos++;
//    } else {
//        pos = 0;            // 到头回到起点
//    }
//    P0 = LED_TABLE[pos];
//}

// 外部中断1：向右移动1步（P0.7→P0.0方向）
//void EX1_ISR(void) interrupt 2 
//{
//    if(pos > 0) {
//        pos--;
//    } else {
//        pos = 7;            // 到头回到起点
//    }
//    P0 = LED_TABLE[pos];
//}

//void main()
//{
//    // 中断初始化
//    IT0 = 1;        // INT0 下降沿触发
//    IT1 = 1;        // INT1 下降沿触发
//    EX0 = 1;        // 使能外部中断0
//    EX1 = 1;        // 使能外部中断1
//    EA = 1;         // 开总中断
//    
//    P0 = LED_TABLE[0];   // 初始显示 P0.0 亮
//    
//    while(1);       // 主循环空转
//}

