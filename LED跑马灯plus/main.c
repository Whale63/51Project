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


void main()
{
	while(1)
	{
	P2=0xfe;//1111 1110
	Delay1ms(10);
	P2=0xfd;//1111 1101
	Delay1ms(10);
	P2=0xfb;//1111 1011
	Delay1ms(10);
	P2=0xf7;//1111 0111
	Delay1ms(10);
	P2=0xef;//1110 1111
	Delay1ms(10);
	P2=0xdf;//1101 1111
	Delay1ms(10);
	P2=0xbf;//1011 1111
	Delay1ms(10);
	P2=0x7f;//0111 1111
	Delay1ms(10);
	}
	
}