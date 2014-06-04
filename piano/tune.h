void tune(uchar y,char x) //play a tune,0 for mute
{
	unsigned int t,h;
	switch(x)
	{
		case 0:buzzer=1;delay(y*TIME*2);goto end;
		case 1:h=19;break;
		case 2:h=17;break;
		case 3:h=15;break;
		case 4:h=14;break;
		case 5:h=12;break;
		case 6:h=10;break;
		case 7:h=9;break;
		case 8:h=8;break;
		case 9:h=7;break;
		case 10:h=15;break;
		case 11:h=14;break;
		case 12:h=12;break;
		case -7:h=20;break;
		case -71:h=21;break;
		case -6:h=23;break;
		case -5:h=26;break;
		case -4:h=29;break;
		case -3:h=31;break;
		case -2:h=35;break;
		case -1:h=39;break;
	}
	t=y*TIME/h;
	while(t--)
	{
		buzzer=0;
		delay(h);
		buzzer=1;
		delay(h);
	}
	end:;
}