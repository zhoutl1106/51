#include<STC12C5A.h>
#include<intrins.h>

#define uint unsigned int 
#define uchar unsigned char

/***********************��������***********************************/
void delay(unsigned int x);
void delay_ms(unsigned int x); // ��ʱ���뼶
void delay_us(); // ��ʱ100΢��
/******************************************************************/

sbit LCD_RS=P3^0; // ����ָ��ѡ��˶���
sbit LCD_RW=P3^1;
sbit LCD_EN=P3^2; // ʹ�ܶ˶���
sbit infraL=P3^3;
sbit infraM=P3^4;
sbit infraR=P3^5;

sbit p14=P1^4;
sbit touch=P1^0;
sbit scanner=P1^1;


unsigned int time=0,t1=0,t2=0,t3=0;

#define LCD_data_port P2  // �����Һ�������Ķ˿�
#define motor_port P0
#define CATCHCODE 150
#define OPENCODE 130

#include<1602.h>
#include<motor.h>
#include<pwm.h>


/************************��ʱ����*******************************/
void delay(unsigned int x)
{
	char y=110;
	while(x--)
		while(y--);
}
void delay_ms(unsigned int x) // ��ʱ���뼶
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void delay_us() // ��ʱ100΢��
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
