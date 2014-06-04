#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit led0=P1^0;
sbit input=P1^7;
sbit en_a=P1^6;
sbit en_b=P3^1;
sbit sw1=P3^2;

uchar controlL[]={0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1,0xf9};
uchar controlR[]={0x8f,0xcf,0x4f,0x6f,0x2f,0x3f,0x1f,0x9f};

void delay(unsigned int x)
{
	char y=110;
	while(x--)
		while(y--);
}

void forward(uchar i)
{
	uchar j;
	for(j=0;j<8;j++)
	{
		P0=controlL[j]&controlR[j];
		delay(i);
	}

}
void main()
{
	while(1)
	{	
		forward(5);
	}
}
