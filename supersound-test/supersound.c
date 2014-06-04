#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit led0=P1^0;
sbit input=P1^7;
sbit en_a=P1^6;
sbit en_b=P3^1;
sbit sw1=P3^2;

//uchar control[]={0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1,0xf9};

void delay(unsigned int x)
{
	unsigned int y=;
	while(x--)
		while(y--);
}

void main()
{
	while(1)
	{	
		led0=1;
		delay(1000);
		led0=0;
		delay(1000);
	}
}

void INT0_server() interrupt 0
{
	led0=0;
	delay(1000);
	led0=1;
}
