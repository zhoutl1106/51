#include<STC12C5A.h>
#include<intrins.h>

#define uint unsigned int 
#define uchar unsigned char

/***********************函数声明***********************************/
void delay(unsigned int x);
void delay_ms(unsigned int x); // 延时毫秒级
void delay_us(); // 延时100微秒
/******************************************************************/

sbit LCD_RS=P3^0; // 数据指令选择端定义
sbit LCD_RW=P3^1;
sbit LCD_EN=P3^2; // 使能端定义
sbit infraL=P3^3;
sbit infraM=P3^4;
sbit infraR=P3^5;
sbit buzzer=P1^6;

sbit p14=P1^4;
sbit touch=P1^0;
sbit scanner=P1^1;


unsigned int time=0,t1=0,t2=0,t3=0;

#define LCD_data_port P2  // 定义给液晶送数的端口
#define motor_port P0
#define CATCHCODE 156
#define OPENCODE 145
#define SPEED 9

#include<1602.h>
#include<motor.h>
#include<pwm.h>


/************************延时函数*******************************/
void delay(unsigned int x)
{
	char y=110;
	while(x--)
		while(y--);
}
void delay_ms(unsigned int x) // 延时毫秒级
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void delay_us() // 延时100微秒
{
	unsigned char n=0;
	for(n=220;n>0;n--)
	{
		_nop_();
	}
}
/***************************************************************/
void main()
{
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
/*********************initial*******************/
	PWM_initial();
	touch=1;
	scanner=1;
	infraL=1;
	infraM=1;
	infraR=1;
	OPEN();
	
/*********************first time**************************************************************/
	forward(30,20);
	forward(55,SPEED-1);
	forward(60,SPEED-3);
	delay_ms(50);
	left(33,15);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT11;
		}
		forward(1,SPEED-1);
	}
NEXT11:	
	delay_ms(500);
	back(8,SPEED+10);
	delay_ms(50);
	while(1)
	{
		if(1==infraM)
		{
			delay(5);
			if(1==infraM)
			goto NEXT12;
		}
		right(1,15);
	}
NEXT12:
	right(12,15);
	delay_ms(50);
	while(1)
	{
		if(0==touch)
		{
			delay(5);
			if(0==touch)
			goto NEXT13;
		}
		forward(1,SPEED);
	}
NEXT13:	
	CATCH();
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	back(30,SPEED+10);
	delay_ms(50);
	left(35,15);
	delay_ms(50);
	forward(9,SPEED-1);
	forward(50,SPEED-3);
	forward(9,SPEED-1);
	delay_ms(50);
	left(34,15);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT14;
		}
		forward(1,SPEED-1);
	}
NEXT14:
	forward(17,SPEED-3);
	delay_ms(50);
	right(35,15);
	delay_ms(50);
	while(1)
	{
		if(0==scanner)
		{
			delay(5);
			if(0==scanner)
			goto NEXT15;
		}
		forward(1,15);
	}
NEXT15:	
	left(7,15);
	OPEN();
	back(15,SPEED+10);
	delay_ms(50);
	right(1,15);
	CATCH();
	delay_ms(200);
	forward(15,SPEED+10);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	t1=time;
	Show();
/*********************second time********************************************************************/
	back(120,SPEED+10);
	OPEN();
	delay_ms(50);
	right(36,15);
	delay_ms(50);
	forward(15,SPEED-1);
	forward(70,SPEED-3);
	forward(15,SPEED-1);
	delay_ms(50);
	left(33,15);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT21;
		}
		forward(1,SPEED-1);
	}
NEXT21:
	delay_ms(500);	
	back(10,SPEED+10);
	delay_ms(50);
	while(1)
	{
		if(1==infraM)
		{
			delay(5);
			if(1==infraM)
			goto NEXT22;
		}
		right(1,15);
	}
NEXT22:
	right(7,15);
	delay_ms(50);
	while(1)
	{
		if(0==touch)
		{
			delay(5);
			if(0==touch)
			goto NEXT23;
		}
		forward(1,SPEED-1);
	}
NEXT23:	
	CATCH();
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	back(30,SPEED+10);
	delay_ms(50);
	left(34,15);
	delay_ms(50);
	forward(10,SPEED-1);
	forward(30,SPEED-3);
	forward(10,SPEED-1);
	delay_ms(50);
	left(34,15);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT24;
		}
		forward(1,SPEED-1);
	}
NEXT24:
	forward(10,SPEED-1);
	delay_ms(50);
	right(36,15);
	delay_ms(50);
	while(1)
	{
		if(0==scanner)
		{
			delay(5);
			if(0==scanner)
			goto NEXT25;
		}
		forward(1,15);
	}
NEXT25:	
	left(12,15);
	OPEN();
	back(15,SPEED+10);
	delay_ms(50);
	right(1,15);
	CATCH();
	delay_ms(200);
	forward(15,SPEED+10);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	t2=time-t1;
	Show();
/*********************third time***********************************************************************/
	back(55,SPEED+10);
	OPEN();
	delay_ms(50);
	right(36,15);
	delay_ms(50);
	forward(15,SPEED-1);
	forward(80,SPEED-3);
	forward(15,SPEED-1);
	delay_ms(50);
	right(36,15);
	delay_ms(50);
	while(1)
	{
		if(0==infraL)
		{
			delay(5);
			if(0==infraL)
			goto NEXT31;
		}
		forward(1,SPEED-1);
	}
NEXT31:
	delay_ms(500);	
	back(10,SPEED+10);
	delay_ms(50);
	while(1)
	{
		if(1==infraM)
		{
			delay(5);
			if(1==infraM)
			goto NEXT32;
		}
		left(1,15);
	}
NEXT32:
	left(3,15);
	delay_ms(50);
	while(1)
	{
		if(0==touch)
		{
			delay(5);
			if(0==touch)
			goto NEXT33;
		}
		forward(1,SPEED-1);
	}
NEXT33:	
	CATCH();
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	left(34,15);
	delay_ms(50);
	forward(23,SPEED-1);
	delay_ms(50);
	left(34,15);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT34;
		}
		forward(1,SPEED-1);
	}
NEXT34:
	forward(5,SPEED-2);
	delay_ms(50);
	right(38,15);
	delay_ms(50);
	while(1)
	{
		if(0==scanner)
		{
			delay(5);
			if(0==scanner)
			goto NEXT35;
		}
		forward(1,15);
	}
NEXT35:	
	left(10,15);
	delay_ms(50);
	OPEN();
	back(15,SPEED+10);
	delay_ms(50);
	right(5,15);
	CATCH();
	delay_ms(200);
	forward(15,SPEED+10);
	t3=time-t2-t1;
	Show();
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(100);
	buzzer=0;
	delay_ms(100);
	buzzer=1;
	delay_ms(500);
	buzzer=0;
	delay_ms(500);
	buzzer=1;
	while(1);
}
