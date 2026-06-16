//#include <reg51.h>
//#include "Delay.h"

//// 共阴极段码：0~9
//// 段码：dp g f e d c b a（P0.7 ~ P0.0）
//unsigned char code SEG_TABLE[] = 
//{
//    0x3F,  // 0  0011 1111
//    0x06,  // 1  0000 0110
//    0x5B,  // 2  0101 1011
//    0x4F,  // 3  0100 1111
//    0x66,  // 4  0110 0110
//    0x6D,  // 5  0110 1101
//    0x7D,  // 6  0111 1101
//    0x07,  // 7  0000 0111
//    0x7F,  // 8  0111 1111
//    0x6F   // 9  0110 1111
//};

//// 位选引脚（低电平选中）
//sbit LED_C1 = P1^0;  // 十位
//sbit LED_C2 = P1^1;  // 个位
//sbit LED_C3 = P1^2;

//// 动态扫描显示函数
//// 参数：ten-十位数字, one-个位数字
//void Display(unsigned char ten, unsigned char one)
//{
//    // 显示十位
//    P0 = 0x00;           // 消隐，防止残影          // 关闭个位
//		LED_C1 = 0;  // 十位
//		LED_C2 = 1;  // 个位
//		LED_C3 = 1;
//    P0 = SEG_TABLE[ten]; // 送十位段码
//    LED_C1 = 0;          // 十位位选有效
//    DelayMS(5);          // 延时5ms
//    
//    // 显示个位
//    P0 = 0x00;           // 消隐
//		LED_C1 = 1;  // 十位
//		LED_C2 = 1;  // 个位
//		LED_C3 = 1;
//    P0 = SEG_TABLE[one]; // 送个位段码
//    LED_C2 = 0;          // 个位位选有效
//    DelayMS(5);          // 延时5ms
//}

//void main()
//{
//    unsigned char num = 0;      // 当前显示的数字 0~99
//    unsigned char ten, one;     // 十位和个位
//    unsigned char i;
//	
//    LED_C1 = 1;
//    LED_C2 = 1;                 // 初始关闭两位
//    
//    while(1) 
//		{
//        // 分离十位和个位
//        ten = num / 10;
//        one = num % 10;
//			
//        // 动态扫描显示50次（约500ms），数字才变化一次;这样人眼能看到稳定的数字，而不是快速跳变
//			
//        
//        for(i = 0; i < 50; i++)
//				{
//            Display(one, ten);
//        }
//        
//        // 数字加1，到99后回到00
//        num++;
//        if(num > 99) 
//				{
//            num = 0;
//        }
//    }
//}
