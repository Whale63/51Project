#include <REGX52.H>
#include <fuction.h>

int main()
{
	int b;
	int s;
	int g;
	
	int i;
	int j;
	
	j=123;//NUMBER
	b=j/100;
	s=(j/10)%10;
	g=j%10;
	
	
	
while(1)
{
	i=1;//LOCATION
INPUT(i,b);//(unsigned char LOCATION,NUMBER)
	i++;
	Delay(1);
	INPUT(i,s);
	i++;
	Delay(1);
	INPUT(i,g);
	Delay(1);
}


}
