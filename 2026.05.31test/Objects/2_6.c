//#include <reg51.h>
//#include "Delay.h"

//// 中断嵌套：INT0（高优先级）可打断INT1，INT1（低优先级）不能打断INT0

//void EX0_ISR(void) interrupt 0 
//{
//    // 外部中断0：8只LED点亮1秒
//    P0 =~0xFF;          // 全亮
//    DelayMS(1000);      // 延时1秒
//    P0 = ~0x00;          // 全灭
//}

//void EX1_ISR(void) interrupt 2 
//{
//    // 外部中断1：8只LED点亮3秒
//    P0 = ~0xFF;          // 全亮
//    DelayMS(3000);      // 延时3秒
//    P0 = ~0x00;          // 全灭
//}

//void main() 
//{
//    // 中断优先级设置
//    PX0 = 1;            // INT0 高优先级
//    PX1 = 0;            // INT1 低优先级
//    
//    IT0 = 1;            // INT0 下降沿触发
//    IT1 = 1;            // INT1 下降沿触发
//    EX0 = 1;            // 使能外部中断0
//    EX1 = 1;            // 使能外部中断1
//    EA = 1;             // 开总中断
//    
//    P0 = ~0x00;          // 初始全灭
//    
//    while(1) 
//		{
//        // 主循环空转
//    }
//}
