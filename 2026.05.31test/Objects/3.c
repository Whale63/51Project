//#include <reg51.h>

//void DelayMS(unsigned int x) 
//	{
//    unsigned char i;
//    while(x--) 
//			{
//        for(i = 120; i > 0; i--);
//    }
//}

//void main() 
//	{
//    unsigned char led = 0x01;  // 初始P0.0亮
//    while(1)
//			{
//        P0 = led;
//        DelayMS(300);          // 延时200ms
//        led = led >> 1;        // 右移一位
//        if(led == 0) 
//					{
//            led = 0x80;        // 移到最右边后回到最左边(P0.7)
//        }
//    }
//}