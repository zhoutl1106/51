unsigned char num=0;

unsigned char PWM_wide[2]={0,0}; // 数值从0到180

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

void PWM_OUT()interrupt 7
{
	if(CF==1)
	{
		//p13=1;
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
