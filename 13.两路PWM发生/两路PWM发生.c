//##############################################################
//
//    实  验 名 称: 两路PWM发生器
//
//    实  验 功 能: 本单片机PWM信号主要用于舵机控制
//			        PWM信号周期为20ms,正脉冲在0.5ms到2.5ms之间可调
//
//    实验硬件环境: 所有程序均在"亿唯电子"公司Mini-EV51单片机开发板(二代)上测试成功,
//                  主控芯片: STC公司的 STC12C5A16S2 
//   				晶振频率: 11.0592MHz 
//       
//    更多程序下载>>亿唯电子：www.evmcu.net
//
//##############################################################
#include<STC12C5A.H>
#include<intrins.h>

sbit p13=P1^1;
sbit p14=P1^4;
sbit led0=P1^3;

unsigned char num=0;

unsigned char PWM_wide[2]={0,0}; // 数值从0到180

void delay_ms(unsigned int x) // 延时毫秒级
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void PWM_initial()//PWM输出初始化(默认输出全为高电平)
{
	CMOD=0x05;	   //允许PCA溢出中断
	CCAPM0=0x4c;   //用于设定工作方式
	CCAPM1=0x4c;

	CH=0xf8;        //PCA计时器高八位
	CL=0xf8;     	//PCA计时器低八位

	CCAP0H=0xf9;
	CCAP0L=0x25;

	CCAP1H=0xf9;
	CCAP1L=0x25;

	EA=1;

	CLK_DIV=0x00;   //系统工作时钟分频设定
	AUXR=0x80;      //将定时器T0、T1速度配置(定时器T0速度都为原来的12倍)
	TMOD=0x22;      //将T0定时器作为PCA的时钟源
	TH0=0x85;
	TL0=0x85;
	TR0=1;
	CR=1;           //启动PCA计数器
}

void main()
{
	PWM_initial();

	led0=0;
	while(1)
	{
		PWM_wide[0]=30;// PWM输出引脚为P1.3
		PWM_wide[1]=30;// PWM输出引脚为P1.4
		delay_ms(2000);
		PWM_wide[0]=150;
		PWM_wide[1]=150;
		delay_ms(2000);
	}
}

void PWM_OUT()interrupt 7
{
	if(CF==1)
	{
		p13=1;
		p14=1;

		CL=0xfa;   	//PCA计时器低八位
		CH=0xf8;    //PCA计时器低八位

		CCAP0L=39+PWM_wide[0];
		CCAP0H=0xf9;

		CCAP1L=39+PWM_wide[1];
		CCAP1H=0xf9;

		num++;
		if(50==num)
		{
			num=0;
			led0=~led0;
		}
			
	}
	CF=0;
}
