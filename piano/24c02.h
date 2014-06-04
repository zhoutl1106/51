void delay2()
{ ;; }
void start()  //开始信号
{	
	sda=1;
	delay2();
	scl=1;
	delay2();
	sda=0;
	delay2();
}

void stop()   //停止
{
	sda=0;
	delay2();
	scl=1;
	delay2();
	sda=1;
	delay2();
}

void respons()  //应答
{
	uchar i;
	scl=1;
	delay2();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay2();
}

void write_byte(uchar date)
{
	uchar i,temp;
	temp=date;


	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		scl=0;
	    delay2();
		sda=CY;
		delay2();
		scl=1;
		delay2();
	//	scl=0;
     //   delay2();
	}
	scl=0;
	delay2();
	sda=1;
	delay2();
}

uchar read_byte()
{
	uchar i,k;
	scl=0;
	delay2();
	sda=1;
	delay2();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay2();	
		k=(k<<1)|sda;
		scl=0;
		delay2();	
	}
	return k;
}

void delay1(uchar x)
{
	uchar a,b;
	for(a=x;a>0;a--)
	 for(b=100;b>0;b--);
}

void write_add(uchar address,uchar date)
{
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	write_byte(date);
	respons();
	stop();
}

uchar read_add(uchar address)
{
	uchar date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	stop();
	return date;
}

void write()
{
	uchar i;
	for(i=0;i<20;i++)
	{
		write_add(i,sound[i]);
		delay1(100);
	}
	for(i=20;i<40;i++)
	{
		write_add(i,rap[i-20]);
		delay1(100);
	}
}
void read()
{
	uchar i;
	for(i=0;i<20;i++)
	{
		sound[i]=read_add(i);
		delay1(100);
	}
	for(i=20;i<40;i++)
	{
		rap[i-20]=read_add(i);
		delay1(100);
	}
	
}


