//#include <reg51.h>
//#include "Delay.h"

//sbit P_INT1 = P3^3;

//unsigned char pwm_duty[8] = {0};
//unsigned char wave_pos = 0;
//bit dir = 0;

// 软件PWM输出一帧（约2ms周期）
//void PWM_Frame(void) {
//    unsigned char step, i;
//    // 256级PWM分8步简化（每步32级）
//    for(step = 0; step < 8; step++) 
//	{
//        unsigned char port_val = 0;
//        unsigned char threshold = step * 32;
//        for(i = 0; i < 8; i++)
//				{
//            if(pwm_duty[i] > threshold) 
//						{
//                port_val |= (1 << i);
//            }
//        }
//        P0 = port_val;
//        DelayMS(0);  // 极短延时，约几十us
//	}
//}

//void EX1_ISR(void) interrupt 2 
//{
//    unsigned char i;
//    for(i = 0; i < 8; i++) 
//		{
//					pwm_duty[i] = 0;

//		}
//    
//    if(dir == 0) 
//		{
//        wave_pos = (wave_pos + 1) & 0x07;
//    } 
//		else
//		{
//        wave_pos = (wave_pos - 1) & 0x07;
//    }
//    
//    pwm_duty[wave_pos] = 255;
//    if(wave_pos >= 1) pwm_duty[wave_pos - 1] = 160;
//    if(wave_pos >= 2) pwm_duty[wave_pos - 2] = 80;
//    if(wave_pos <= 6) pwm_duty[wave_pos + 1] = 160;
//    if(wave_pos <= 5) pwm_duty[wave_pos + 2] = 80;
//}

//void main() 
//{
//    IT1 = 1;
//		EX1 = 1; 
//		EA = 1;
//	
//    while(1) 
//		{
//        PWM_Frame();   // 持续刷新PWM
//    }
//}

