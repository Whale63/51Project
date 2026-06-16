//#include <reg51.h>

////--定义使用的 IO--//
//#define GPIO_DIG P0

//sbit LSA = P2^2;
//sbit LSB = P2^3;
//sbit LSC = P2^4;

////--定义全局变量--//
//// 共阴极数码管段码表：0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F
//unsigned char code DIG_CODE[17] = {
//    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
//    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
//};

//// 用来存放要显示的 8 位数值
//unsigned char DisplayData[8];

////--声明全局函数--//
//void DigDisplay();  // 动态显示函数

//void main(void)
//{
//    unsigned char i;
//    
//    // 初始化显示数据：第 0~7 位分别显示 0,1,2,3,4,5,6,7
//    for(i = 0; i < 8; i++)
//    {
//        DisplayData[i] = DIG_CODE[i];
//    }
//    
//    while(1)
//    {
//        DigDisplay();  // 循环调用动态显示
//    }
//}

//void DigDisplay()
//{
//    unsigned char i;
//    unsigned int j;
//    
//    for(i = 0; i < 8; i++)
//    {
//        // 位选：通过 74HC138 选择点亮的数码管
//        switch(i)
//        {
//            case(0):
//                LSA = 0; LSB = 0; LSC = 0; break;  // 显示第 0 位
//            case(1):
//                LSA = 1; LSB = 0; LSC = 0; break;  // 显示第 1 位
//            case(2):
//                LSA = 0; LSB = 1; LSC = 0; break;  // 显示第 2 位
//            case(3):
//                LSA = 1; LSB = 1; LSC = 0; break;  // 显示第 3 位
//            case(4):
//                LSA = 0; LSB = 0; LSC = 1; break;  // 显示第 4 位
//            case(5):
//                LSA = 1; LSB = 0; LSC = 1; break;  // 显示第 5 位
//            case(6):
//                LSA = 0; LSB = 1; LSC = 1; break;  // 显示第 6 位
//            case(7):
//                LSA = 1; LSB = 1; LSC = 1; break;  // 显示第 7 位
//        }
//        
//        GPIO_DIG = DisplayData[i];  // 发送段码数据
//        
//        j = 10;                     // 扫描间隔时间设定
//        while(j--);
//        
//        GPIO_DIG = 0x00;            // 消隐（关闭显示，防止拖影）
//    }
//}
