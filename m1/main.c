#include <REGX52.H>
#include <intrins.h>

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	while(1)
	{
	P2=0xfe;//1111 1110
		Delay100ms();
	P2=0xfc;//1111 1100
		Delay100ms();
	P2=0xf8;//1111 1000
		Delay100ms();
	P2=0xf0;//1111 0000
		Delay100ms();
	P2=0xe0;//1110 0000
		Delay100ms();
	P2=0xc0;//1100 0000
		Delay100ms();
	P2=0x80;//1000 0000
		Delay100ms();
	P2=0x00;//0000 0000
		Delay100ms();
	P2=0xff;//1111 1111
		Delay100ms();
	}
	
}