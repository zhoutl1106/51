#include <reg52.h>
#define uchar unsigned char

sbit led0=P1^0;
sbit input=P3^0;

uchar control[]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};

void delay(unsigned int x)
{
	char y=110;
	while(x--)
		while(y--);
}

void main()
{
	while(1)
	{
		if(0==input)
			led0=0;
		else
			led0=1;
	}
}
