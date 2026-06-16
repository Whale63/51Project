#include <REGX52.H>
#include <stdio.h>
#include <LCD1602.h>
#include <LCD1602.c>

void Delay(unsigned char xms)	//@11.0592MHz
{
	unsigned char data i, j;

	while(xms--)
	{
	//_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	}
}


int main()
{
	int c;//column
	int x;
	x='x';
	c=1;
	
	LCD_Init();

		if(P3_1==1)//pressing the button
     {
			 Delay(20);
			 LCD_ShowChar(1,c,x);//void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
     }
		if(P3_1==0)
		{
			 Delay(20);
			 LCD_ShowNum(1,c,1,1);//LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
			 c++;
		}
		if(P3_2==1)//pressing the button
		{
		Delay(20);
			 LCD_ShowChar(1,c,x);
		}
		if(P3_2==0)
		{
			 Delay(20);
			 LCD_ShowNum(1,c,2,1);//LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
			c++;
		}
		if(P3_3==1)//pressing the button
		{
		Delay(20);
			 LCD_ShowChar(1,c,x);
		}
		if(P3_3==0)
		{
			 Delay(20);
			 LCD_ShowNum(1,c,3,1);//LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
			c++;
		}
		
  while(1);
	



}