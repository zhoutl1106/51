//##############################################################
//
//    ʵ  �� �� ��: ��·PWM������
//
//    ʵ  �� �� ��: ����Ƭ��PWM�ź���Ҫ���ڶ������
//			        PWM�ź�����Ϊ20ms,��������0.5ms��2.5ms֮��ɵ�
//
//    ʵ��Ӳ������: ���г������"��Ψ����"��˾Mini-EV51��Ƭ��������(����)�ϲ��Գɹ�,
//                  ����оƬ: STC��˾�� STC12C5A16S2 
//   				����Ƶ��: 11.0592MHz 
//       
//    �����������>>��Ψ���ӣ�www.evmcu.net
//
//##############################################################
#include<STC12C5A.H>
#include<intrins.h>

sbit p13=P1^1;
sbit p14=P1^4;
sbit led0=P1^3;

unsigned char num=0;

unsigned char PWM_wide[2]={0,0}; // ��ֵ��0��180

void delay_ms(unsigned int x) // ��ʱ���뼶
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void PWM_initial()//PWM�����ʼ��(Ĭ�����ȫΪ�ߵ�ƽ)
{
	CMOD=0x05;	   //����PCA����ж�
	CCAPM0=0x4c;   //�����趨������ʽ
	CCAPM1=0x4c;

	CH=0xf8;        //PCA��ʱ���߰�λ
	CL=0xf8;     	//PCA��ʱ���Ͱ�λ

	CCAP0H=0xf9;
	CCAP0L=0x25;

	CCAP1H=0xf9;
	CCAP1L=0x25;

	EA=1;

	CLK_DIV=0x00;   //ϵͳ����ʱ�ӷ�Ƶ�趨
	AUXR=0x80;      //����ʱ��T0��T1�ٶ�����(��ʱ��T0�ٶȶ�Ϊԭ����12��)
	TMOD=0x22;      //��T0��ʱ����ΪPCA��ʱ��Դ
	TH0=0x85;
	TL0=0x85;
	TR0=1;
	CR=1;           //����PCA������
}

void main()
{
	PWM_initial();

	led0=0;
	while(1)
	{
		PWM_wide[0]=30;// PWM�������ΪP1.3
		PWM_wide[1]=30;// PWM�������ΪP1.4
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

		CL=0xfa;   	//PCA��ʱ���Ͱ�λ
		CH=0xf8;    //PCA��ʱ���Ͱ�λ

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
