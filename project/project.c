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
#define SPEED 7
#define TURNSPEED 15
#define BACKSPEED 12

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
	forward(115,SPEED);
	delay_ms(50);
	left(33,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT11;
		}
		forward(1,SPEED);
	}
NEXT11:	
	delay_ms(500);
	back(10,BACKSPEED);
	delay_ms(50);
	while(1)
	{
		if(1==infraM)
		{
			delay(5);
			if(1==infraM)
			goto NEXT12;
		}
		right(1,TURNSPEED);
	}
NEXT12:
	right(11,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==touch)
		{
			delay(5);
			if(0==touch)
			goto NEXT13;
		}
		forward(1,SPEED+5);
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
	back(30,BACKSPEED);
	delay_ms(50);
	left(35,TURNSPEED);
	delay_ms(50);
	forward(68,SPEED);
	delay_ms(50);
	left(34,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT14;
		}
		forward(1,SPEED);
	}
NEXT14:
	forward(17,SPEED);
	delay_ms(50);
	right(35,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==scanner)
		{
			delay(5);
			if(0==scanner)
			goto NEXT15;
		}
		forward(1,TURNSPEED);
	}
NEXT15:	
	left(5,TURNSPEED);
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
	OPEN();
	t1=time;
	Show();
	delay_ms(500);
/*********************second time********************************************************************/
	back(120,BACKSPEED);
	delay_ms(50);
	right(36,TURNSPEED);
	delay_ms(50);
	forward(110,SPEED);
	delay_ms(50);
	left(34,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT21;
		}
		forward(1,SPEED);
	}
NEXT21:
	delay_ms(500);	
	back(12,BACKSPEED);
	delay_ms(50);
	while(1)
	{
		if(1==infraM)
		{
			delay(5);
			if(1==infraM)
			goto NEXT22;
		}
		right(1,TURNSPEED);
	}
NEXT22:
	right(6,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==touch)
		{
			delay(5);
			if(0==touch)
			goto NEXT23;
		}
		forward(1,SPEED+5);
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
	back(30,BACKSPEED);
	delay_ms(50);
	left(34,TURNSPEED);
	delay_ms(50);
	forward(45,SPEED);
	delay_ms(50);
	left(34,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT24;
		}
		forward(1,SPEED);
	}
NEXT24:
	forward(10,SPEED);
	delay_ms(50);
	right(35,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==scanner)
		{
			delay(5);
			if(0==scanner)
			goto NEXT25;
		}
		forward(1,TURNSPEED);
	}
NEXT25:	
	left(7,TURNSPEED);
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
	OPEN();
	t2=time-t1;
	Show();
	delay_ms(500);

/*********************third time***********************************************************************/
	back(50,BACKSPEED);
	delay_ms(50);
	right(34,TURNSPEED);
	delay_ms(50);
	forward(110,SPEED);
	delay_ms(50);
	right(33,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==infraL)
		{
			delay(5);
			if(0==infraL)
			goto NEXT31;
		}
		forward(1,SPEED);
	}
NEXT31:
	delay_ms(500);	
	back(10,BACKSPEED);
	delay_ms(50);
	while(1)
	{
		if(1==infraM)
		{
			delay(5);
			if(1==infraM)
			goto NEXT32;
		}
		left(1,TURNSPEED);
	}
NEXT32:
	left(3,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==touch)
		{
			delay(5);
			if(0==touch)
			goto NEXT33;
		}
		forward(1,SPEED+5);
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
//	back(80,BACKSPEED);
//	delay_ms(50);
	left(33,TURNSPEED);
	delay_ms(50);
	forward(23,SPEED);
	delay_ms(50);
	left(33,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==infraR)
		{
			delay(5);
			if(0==infraR)
			goto NEXT34;
		}
		forward(1,SPEED);
	}
NEXT34:
	forward(5,SPEED);
	delay_ms(50);
	right(38,TURNSPEED);
	delay_ms(50);
	while(1)
	{
		if(0==scanner)
		{
			delay(5);
			if(0==scanner)
			goto NEXT35;
		}
		forward(1,TURNSPEED);
	}
NEXT35:	
	left(10,TURNSPEED);
	delay_ms(50);
	right(1,TURNSPEED);
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
	OPEN();;
	t3=time-t2-t1;
	delay_ms(500);
	back(50,BACKSPEED);
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
	delay_ms(1000);
	buzzer=0;
	delay_ms(1000);
	buzzer=1;
	while(1);
}
