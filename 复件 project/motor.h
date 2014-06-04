uchar controlL[]={0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1,0xf9};
uchar controlR[]={0x8f,0xcf,0x4f,0x6f,0x2f,0x3f,0x1f,0x9f};

void forward(uchar i)
{
	uchar j,k;
	for(k=0;k<i;k++)
	for(j=0;j<8;j++)
	{
		motor_port=controlL[j]&controlR[j];
		delay(5);
	}

}
void back(uchar i)
{
	uchar j,k;
	for(k=0;k<i;k++)
	for(j=0;j<8;j++)
	{
		motor_port=controlL[8-j]&controlR[8-j];
		delay(5);
	}

}
void left(uchar i)
{
	uchar j,k;
	for(k=0;k<i;k++)
	for(j=0;j<8;j++)
	{
		motor_port=controlL[8-j]&controlR[j];
		delay(5);
	}

}
void right(uchar i)
{
	uchar j,k;
	for(k=0;k<i;k++)
	for(j=0;j<8;j++)
	{
		motor_port=controlL[j]&controlR[8-j];
		delay(5);
	}

}
