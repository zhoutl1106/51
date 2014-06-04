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

sbit p14=P1^4;
sbit touch=P1^0;
sbit scanner=P1^1;


unsigned int time=0,t1=0,t2=0,t3=0;

#define LCD_data_port P2  // 定义给液晶送数的端口
#define motor_port P0
#define CATCHCODE 150
#define OPENCODE 130

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
/*********************initial*******************/
	PWM_initial();
	touch=1;
	scanner=1;
	infraL=1;
	infraM=1;
	infraR=1;
	OPEN();
/*********************first time**************************************************************/
	while(1)
	{
		if(0==infraM)
			forward(100);
	}
	while(1);
}
