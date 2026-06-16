//#include"reg51.h"
//#define uint unsigned int
//#define uchar unsigned char

//uchar code table[]={
//0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
//0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
//};

//uchar flag,num;

//void main()
//{
//        SM0=0;
//        SM1=1;
//        REN=1;
//        
//        TR1=1;
//        TMOD=0x20;
//        TH1=0xf3;//波特率设置为4800
//        TL1=0xf3;
//        
//        EA=1;
//        ES=1;
//        
//        while(1)
//        {
//                if(flag==1)
//                {
//                        ES=0;
//                        flag=0;
//                        SBUF=num;
//                        while(TI==0);
//                        TI=0;
//                        ES=1;
//                }
//        }
//}

//void ser() interrupt 4
//{
//        RI=0;
//        num=SBUF;
//        P0=~table[SBUF];
//        flag=1;
//        
//}
