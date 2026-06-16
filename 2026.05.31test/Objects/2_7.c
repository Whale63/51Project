#include <reg51.h>
#include "Delay.h"

// 共阴极段码：0~F
unsigned char code SEG_TABLE[] =
{
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F,  // 9
    0x77,  // A
    0x7C,  // b
    0x39,  // C
    0x5E,  // d
    0x79,  // E
    0x71   // F
};

unsigned char num = 0;      // 当前显示数字 0~15

// 外部中断0：数字加1
void EX0_ISR(void) interrupt 0 
{
    num++;
    if(num > 15) num = 0;   // 超过F回到0
    P0 = ~SEG_TABLE[num];
}

// 外部中断1：数字减1
void EX1_ISR(void) interrupt 2 
{
    if(num == 0) num = 15;  // 0减1到F
    else num--;
    P0 = ~SEG_TABLE[num];
}

void main() 
{
    IT0 = 1;            // INT0 下降沿触发
    IT1 = 1;            // INT1 下降沿触发
    EX0 = 1;            // 使能外部中断0
    EX1 = 1;            // 使能外部中断1
    EA = 1;             // 开总中断
    
    P0 = ~SEG_TABLE[0];  // 初始显示"0"
    
    while(1) 
		{
        // 主循环空转
    }
}

