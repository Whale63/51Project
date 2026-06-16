//#include <reg51.h>
//#include "Delay.h"

//unsigned char led = 0x01;   // 当前亮灯位置（位变量：0x01, 0x02, 0x04...）
//bit dir = 0;                // 0=左移(低位→高位)，1=右移(高位→低位)
//unsigned char cnt0 = 0;     // T0计数
//unsigned char cnt1 = 0;     // T1计数

//// 定时器0中断：50ms × 10 = 0.5秒，流水灯移动
//void T0_ISR(void) interrupt 1
//{
//    TH0 = 0x3C;     // 重装初值 50ms
//    TL0 = 0xB0;
//    
//    cnt0++;
//    if(cnt0 >= 10)  // 0.5秒到
//    {
//        cnt0 = 0;
//        
//        if(dir == 0)    // 左移：P0.0 → P0.7
//        {
//            led = led << 1;         // 左移1位
//            if(led == 0)            // 移出边界（变成0）
//                led = 0x01;         // 回到最低位
//        }
//        else            // 右移：P0.7 → P0.0
//        {
//            led = led >> 1;         // 右移1位
//            if(led == 0)            // 移出边界（变成0）
//                led = 0x80;         // 回到最高位
//        }
//        
//        P0 = ~led;      // 共阳：取反后输出（0点亮）
//    }
//}

//// 定时器1中断：50ms × 100 = 5秒，变换方向
//void T1_ISR(void) interrupt 3
//{
//    TH1 = 0x3C;     // 重装初值 50ms
//    TL1 = 0xB0;
//    
//    cnt1++;
//    if(cnt1 >= 100) // 5秒到
//    {
//        cnt1 = 0;
//        dir = !dir;     // 切换方向（bit类型用 ! 不能用 ~）
//    }
//}

//void main(void)
//{
//    P0 = ~0x01;     // 初始显示：P0.0 亮（共阳）
//    
//    TMOD = 0x11;    // T0和T1都设为模式1（16位定时器）
//    
//    // T0初值 50ms @12MHz
//    TH0 = 0x3C;
//    TL0 = 0xB0;
//    
//    
//    ET0 = 1;        // 使能T0中断
//    ET1 = 1;        // 使能T1中断
//    TR0 = 1;        // 启动T0
//    TR1 = 1;        // 启动T1
//    EA = 1;         // 开总中断
//    
//    while(1);
//}