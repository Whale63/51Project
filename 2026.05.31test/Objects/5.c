//#include <reg51.h>

//sbit KEY = P1^1;   // P1.1接开关

//void DelayMS(unsigned int x) {
//    unsigned char i;
//    while(x--) {
//        for(i = 120; i > 0; i--);
//    }
//}

//void main() 
//{
//    unsigned char led = 0x01;
//    P1 = 0xFF;   // P1口输入
//    
//    while(1) {
//        P0 = led;
//        DelayMS(300);
//        
//        if(KEY == 0) {         // 开关闭合（假设低电平有效）
//            led = led << 1;    // 向左流水（P0.0→P0.7）
//            if(led == 0) led = 0x01;
//        } else {
//            led = led >> 1;    // 向右流水（P0.7→P0.0）
//            if(led == 0) led = 0x80;
//        }
//    }
//}