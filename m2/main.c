#include <REGX52.H>
#include <intrins.h>
void Delay1ms(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
	do
	{
		while (--j);
	} while (--i);
	  xms--;
	}
  
}
unsigned char NixieTable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 

void Nixie(unsigned char Location,Number)
{
  switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}		
	
  P0=NixieTable[Number];
	
}

void main()
{
  
//	while()
	//{
	int i=65535;
	while(i--)
		{
	  Nixie(7,2);
//		P0 = 0x00;		
		Nixie(8,7);
//		P0 = 0x00;		
		}	
		Delay1ms(500);
		
		Nixie(7,3);
		Delay1ms(1);
		Nixie(8,4);
		Delay1ms(500);
		Nixie(7,5);
		Delay1ms(1);
		Nixie(8,1);
		Delay1ms(500);
		Nixie(7,6);
		Delay1ms(1);
		Nixie(8,8);
		Delay1ms(500);
		Nixie(7,8);
		Delay1ms(1);
		Nixie(8,5);
		Delay1ms(500);
		Nixie(6,1);
		Delay1ms(1);
		Nixie(7,0);
		Delay1ms(1);
		Nixie(8,2);
		Delay1ms(500);
		Nixie(6,1);
		Delay1ms(1);
		Nixie(7,1);
		Delay1ms(1);
		Nixie(8,9);
		Delay1ms(500);
	  Nixie(6,1);
		Delay1ms(1);
		Nixie(7,3);
		Delay1ms(1);
		Nixie(8,6);
		Delay1ms(500);
	  Nixie(6,1);
		Delay1ms(1);
		Nixie(7,5);
		Delay1ms(1);
		Nixie(8,3);
		Delay1ms(500);
	  Nixie(6,1);
		Delay1ms(1);
		Nixie(7,7);
		Delay1ms(1);
		Nixie(8,0);
		Delay1ms(500);
	
	}



