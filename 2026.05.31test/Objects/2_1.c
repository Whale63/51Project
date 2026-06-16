//#include "reg51.h"
//#include "Delay.h"

//// 共阴极段码：0~9
//// 段码：dp g f e d c b a（P0.7 ~ P0.0）
//unsigned char code SEG_TABLE[] = 
//{
//    0x3F,  // 0
//    0x06,  // 1
//    0x5B,  // 2
//    0x4F,  // 3
//    0x66,  // 4
//    0x6D,  // 5
//    0x7D,  // 6
//    0x07,  // 7
//    0x7F,  // 8
//    0x6F   // 9
//};

//// P1口位选：P1.0控制十位，P1.1控制个位（低电平选中）
//sbit DIG1 = P1^0;  // 十位
//sbit DIG2 = P1^1;  // 个位
//sbit DIG3 = P1^2;  // 个位

//void main() 
//{
//    while(1) {
//        // 显示十位"1"
//        P0 = SEG_TABLE[1];   // 段码：0x06
//        DIG1 = 0;            // 十位位选有效（低电平）
//        DIG2 = 1;            // 个位位选关闭
//				DIG2 = 1;
//        DelayMS(5);          // 延时5ms
//        
//        // 显示个位"2"
//        P0 = SEG_TABLE[2];   // 段码：0x5B
//        DIG1 = 1;            // 十位位选关闭
//        DIG2 = 1;            // 个位位选有效（低电平）
//				DIG2 = 1;
//        DelayMS(5);          // 延时5ms
//    }
//}
