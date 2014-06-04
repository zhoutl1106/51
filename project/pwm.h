unsigned char num=0;

unsigned char PWM_wide[2]={0,0}; // ��ֵ��0��180

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

void PWM_OUT()interrupt 7
{
	if(CF==1)
	{
		//p13=1;
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
			time++;
		}
			
	}
	CF=0;
}

void CATCH()
{
	PWM_wide[1]=CATCHCODE;
}

void OPEN()
{
	PWM_wide[1]=OPENCODE;
}
