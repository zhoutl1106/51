#include <reg51.h>
#define uchar unsigned char
#define duank P1
#define TIME 5000

sbit buzzer=P2^0;
sbit key1=P3^0;
sbit key2=P3^1;
sbit key3=P3^3;
sbit key4=P3^4;
sbit key5=P3^5;
sbit key6=P3^6;
sbit key7=P3^7;
sbit rec=P3^2;

sbit sda=P2^7;
sbit scl=P2^6;

char num;
   
void delay(unsigned int x)
{
while(x--);
}

#include <key.h>
#include <tune.h>

char sound[20]={99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99};
char   rap[20]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

#include <songs.h>
#include <24c02.h>

void init()
{
	EA=1;//开总终中断
	EX0=1;//开外部中断0
	sda=1;
	delay2();
	scl=1;
	delay2();
}

void main()
{
	
	char i;
	init();
	read();
	tune(1,3);tune(1,0);tune(1,3);
	num=-9;
	while(1)
	{
		i=keyscan();
		if(i==21)
		{
			playsong1();
		num=0;i=0;
		}else
		if(i==22)
		{
			playsong2();
		num=0;i=0;
		}else
		if(i==23)
		{
			playsong3();
		num=0;i=0;
		}else
		if(i==24)
		{
			playself();
		num=0;i=0;
		}else
			tune(1,i);
		num=0;
		
	} 
}

void int0() interrupt 0
{
	char i,j;
	tune(1,3);tune(1,0);tune(1,3);
	for(j=0;j<20;j++)
		sound[j]=99;
	j=0;
	while(rec!=0)
	{
		i=keyscan();
		while(i<-7||i>12)
			{
				i=keyscan();
				if(rec==0)goto end1;
			}
		tune(1,i);
		if(i==12)i=0;
		sound[j]=i;
		i=keyscan();
		while(i<21||i>24)
			{
				i=keyscan();
				if(rec==0)goto end1;
			}
		switch(i)
		{
			case 21:rap[j]=8;break;
			case 22:rap[j]=4;break;
			case 23:rap[j]=2;break;
			case 24:rap[j]=1;break;
		}
		tune(rap[j],sound[j]);
		j++;
		if(j==15)
		{
			tune(1,3);tune(1,0);tune(1,3);
		}
	}
	sound[j]=99;
end1:
	j=0;
	sound[19]=99;
	tune(8,0);tune(8,0);tune(8,0);
	while(sound[j]!=99)
	{
		tune(rap[j],sound[j]);
		j++;
	}
	write();
	tune(8,0);tune(8,0);tune(8,0);tune(1,3);tune(1,0);tune(1,3);tune(1,0);tune(1,3);
}
