#include <reg51.h>
#include "Delay.h"

unsigned char code SEG_TABLE[] =
{
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
};

void UART_SendChar(unsigned char ch)
{
    SBUF = ch;
    while(!TI);
    TI = 0;
}

void main(void)
{
    unsigned char recv_data = 0;
    
    SCON = 0x50;
    TMOD = 0x20;
    TH1 = 0xFA;
    TL1 = 0xFA;
    TR1 = 1;
    ES = 0;
    EA = 0;
    
    P0 = ~SEG_TABLE[0];
    
    while(1)
    {
        if(RI == 1)
        {
            RI = 0;
            
            // 关键修改：高四位清零，只保留低四位
            recv_data = SBUF & 0x0F;
            
            // 回传处理后的数据（可选：回传原始值还是处理后的值？）
            // 如果老师要求回传处理后的（不带8的）：
            UART_SendChar(recv_data);
            
            // 或者如果你想回传原始值给电脑看：
            // UART_SendChar(SBUF);
        }
        
        P0 = ~SEG_TABLE[recv_data];
    }
}
