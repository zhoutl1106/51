#include<reg52.h>
sbit led0=P1^0;
sbit key=P1^7;
unsigned char num=0;
void delay_ms(unsigned int x) // ÑÓÊ±ºÁÃë¼¶
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=64;c>0;c--);
}
void main()
{
	unsigned char a=20,m;
	TMOD=0x12;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	TR1=1;
	ET1=1;
	
	while(1)
	{
		
	}
}

void timer_0() interrupt 3
{
	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	num++;
	if(20==num)
	{
		num=0;
		led0=~led0;
	}

}
