//#include <reg51.h>
//#include "Delay.h"

//sbit LED = P0^0;

//unsigned char cnt = 0;

//void T1_ISR(void) interrupt 3
//{
//    TH1 = 0x3C;
//    TL1 = 0xB0;
//    
//    cnt++;
//    if(cnt >= 20)
//    {
//        cnt = 0;
//        LED = ~LED;
//    }
//}

//void main(void)
//{
//    LED = 0;
//    
//    TMOD = 0x10;
//    TH1 = 0x3C;
//    TL1 = 0xB0;
//    ET1 = 1;
//    TR1 = 1;
//    EA = 1;
//    
//    while(1)
//    {
//			
//    }
//}
