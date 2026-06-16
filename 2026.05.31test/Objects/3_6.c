//#include <reg51.h>
//#include "Delay.h"

//// 共阴极段码：0~F
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
//    0x6F,  // 9
//    0x77,  // A
//    0x7C,  // b
//    0x39,  // C
//    0x5E,  // d
//    0x79,  // E
//    0x71   // F
//};

//// 接收到的数据
//unsigned char recv_data = 0;

//// 串行口中断服务程序
//void UART_ISR(void) interrupt 4
//{
//    if(RI == 1)         // 接收中断
//    {
//        RI = 0;         // 清接收标志
//        recv_data = SBUF;   // 读取数据
//        
//        // 限制0~F有效
//        if(recv_data > 0x0F)
//        {
//            recv_data = 0x0F;
//        }
//    }
//    
//    if(TI == 1)         // 发送中断（本例不用）
//    {
//        TI = 0;
//    }
//}

//void main(void)
//{
//    // 串口初始化：方式1，9600bps，12MHz晶振
//    SCON = 0x50;        // 方式1，允许接收
//    TMOD = 0x20;        // T1模式2，自动重装
//    TH1 = 0xFD;         // 9600bps初值
//    TL1 = 0xFD;
//    TR1 = 1;            // 启动T1
//    ES = 1;             // 使能串口中断
//    EA = 1;             // 开总中断
//    
//    P0 = ~SEG_TABLE[0];  // 初始显示0
//    
//    while(1)
//    {
//        // 持续显示接收到的数据
//        P0 = ~SEG_TABLE[recv_data];
//    }
//}
