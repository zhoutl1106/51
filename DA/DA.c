sbit dawr = 
sbit dacs = 

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

void main()
{
	uchar val,flag;
	dacs = 0;
	dawr = 0;
	P0 = 0;
	while(1)
	{
		if(flag == 0)
		{
			val += 5;
			P0 = val;
			if(val == 255)
			{
				flag = 1;
			}
			delayms(50);
		}
		else
		{
			val -= 5;
			P0 = val;
			if(val == 0)
			{
				flag = 0;
			}
			delayms(50);
		}
	}
}