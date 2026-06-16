//#include <reg51.h>
//#include "Delay.h"

//sbit LED = P0^0;

//// 定时器0中断服务程序：每50ms中断一次
//unsigned char cnt = 0;      // 中断计数

//void T0_ISR(void) interrupt 1 
//{
//    TH0 = 0x3C;             // 定时50ms初值（12MHz）
//    TL0 = 0xB0;
//    
//    cnt++;
//    if(cnt >= 10)
//		{         // 50ms × 10 = 500ms = 0.5秒
//        cnt = 0;
//        LED = ~LED;         // LED状态翻转
//    }
//}

//void main() 
//{
//    LED = 0;                // 初始点亮（低电平有效）
//    
//    TMOD = 0x01;            // 定时器0，模式1（16位定时器）
//    TH0 = 0x3C;             // 50ms定时初值
//    TL0 = 0xB0;
//    ET0 = 1;                // 使能定时器0中断
//    TR0 = 1;                // 启动定时器0
//    EA = 1;                 // 开总中断
//    
//    while(1) 
//		{
//        // 主循环空转
//    }
//}
