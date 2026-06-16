//#include <reg51.h>
//#include "Delay.h"

//sbit LED = P0^0;        // P0.0控制LED

//bit flash_flag = 0;     // 闪烁标志

//// 计数器0中断：计数10次溢出
//void T0_ISR(void) interrupt 1
//{
//    TH0 = 0xF6;         // 重装初值
//    TL0 = 0xF6;
//    
//    flash_flag = 1;     // 标记需要闪烁
//}

//// LED闪烁2次
//void Flash_LED(void)
//{
//    unsigned char i;
//    for(i = 0; i < 2; i++)
//    {
//        LED = 0;            // 点亮（共阳输出0亮）
//        DelayMS(300);
//        LED = 1;            // 熄灭
//        DelayMS(300);
//    }
//}

//void main(void)
//{
//    LED = 1;            // 初始熄灭
//    
//    // 计数器0，模式2，8位自动重装
//    TMOD = 0x06;        // C/T=1:计数器模式, M1M0=10:模式2
//    
//    TH0 = 0xF6;         // 初值246，计数10次溢出（256-246=10）
//    TL0 = 0xF6;
//    
//    ET0 = 1;            // 使能计数器0中断
//    TR0 = 1;            // 启动计数器0
//    EA = 1;             // 开总中断
//    
//    while(1)
//    {
//        if(flash_flag)          // 需要闪烁
//        {
//            flash_flag = 0;     // 清除标志
//            Flash_LED();        // 闪烁2次
//        }
//    }
//}

////#include <reg51.h>
////#include "Delay.h"

////sbit LED = P0^0;        // P0.0控制LED

////bit flash_flag = 0;     // 闪烁标志

////// 计数器0中断：计数5次溢出
////void T0_ISR(void) interrupt 1
////{
////    TH0 = 0xFB;         // 重装初值
////    TL0 = 0xFB;
////    
////    flash_flag = 1;     // 标记需要闪烁
////}

////// LED闪烁2次
////void Flash_LED(void)
////{
////    unsigned char i;
////    for(i = 0; i < 2; i++)
////    {
////        LED = 0;            // 点亮（共阳输出0亮）
////        DelayMS(300);
////        LED = 1;            // 熄灭
////        DelayMS(300);
////    }
////}

////void main(void)
////{
////    LED = 1;            // 初始熄灭
////    
////    // 计数器0，模式2，8位自动重装
////    TMOD = 0x06;        // C/T=1:计数器模式, M1M0=10:模式2
////    
////    TH0 = 0xFB;         // 初值251，计数5次溢出（256-251=5）//10次
////    TL0 = 0xFB;
////    
////    ET0 = 1;            // 使能计数器0中断
////    TR0 = 1;            // 启动计数器0
////    EA = 1;             // 开总中断
////    
////    while(1)
////    {
////        if(flash_flag)          // 需要闪烁
////        {
////            flash_flag = 0;     // 清除标志
////            Flash_LED();        // 闪烁2次
////        }
////    }
////}
