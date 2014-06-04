#include <reg51.h>
#include <math.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
//*************************definition of output wave form*****************************
#define SQUARE 0
#define TRIANGLE 1
#define SAWTOOTH 2
#define SINE 3
#define PWM 4
uchar form;
uchar duty;

//*************************definition of keys*****************************************
sbit key_select = P3^2;
sbit key_100 = P3^3;
sbit key_10 = P3^4;

//*************************definition of D/A converter********************************
#define DA P2
uchar val;

//*************************definition of LCD_1602 data & control**********************
sbit LCD_RS=P1^7;
sbit LCD_RW=P1^1;
sbit LCD_EN=P1^2;
#define LCD_data_port P1

//*************************Data array of LCD display**********************************
unsigned char code func_square[]=" Square Wave";
unsigned char code func_triangle[]=" Triangle Wave";
unsigned char code func_sawtooth[]=" Sawtooth Wave";
unsigned char code func_sine[]=" Sine Wave";
unsigned char freq[]="Freq: 000 Hz";

//*************************Table of 256 values of sine function in a period***********
uchar code sinval[256]={
	 0x80,0x83,0x86,0x89,0x8d,0x90,0x93,0x96,0x99,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,0xb1,0xb4,0xb7,0xba,0xbc,0xbf,0xc2,0xc5
	,0xc7,0xca,0xcc,0xcf,0xd1,0xd4,0xd6,0xd8,0xda,0xdd,0xdf,0xe1,0xe3,0xe5,0xe7,0xe9,0xea,0xec,0xee,0xef,0xf1,0xf2,0xf4,0xf5
	,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfd,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfd
	,0xfd,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,0xf6,0xf5,0xf4,0xf2,0xf1,0xef,0xee,0xec,0xea,0xe9,0xe7,0xe5,0xe3,0xe1,0xde,0xdd,0xda
	,0xd8,0xd6,0xd4,0xd1,0xcf,0xcc,0xca,0xc7,0xc5,0xc2,0xbf,0xbc,0xba,0xb7,0xb4,0xb1,0xae,0xab,0xa8,0xa5,0xa2,0x9f,0x9c,0x99
	,0x96,0x93,0x90,0x8d,0x89,0x86,0x83,0x80,0x80,0x7c,0x79,0x76,0x72,0x6f,0x6c,0x69,0x66,0x63,0x60,0x5d,0x5a,0x57,0x55,0x51
	,0x4e,0x4c,0x48,0x45,0x43,0x40,0x3d,0x3a,0x38,0x35,0x33,0x30,0x2e,0x2b,0x29,0x27,0x25,0x22,0x20,0x1e,0x1c,0x1a,0x18,0x16
	,0x15,0x13,0x11,0x10,0x0e,0x0d,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0d,0x0e,0x10,0x11,0x13,0x15
	,0x16,0x18,0x1a,0x1c,0x1e,0x20,0x22,0x25,0x27,0x29,0x2b,0x2e,0x30,0x33,0x35,0x38,0x3a,0x3d,0x40,0x43,0x45,0x48,0x4c,0x4e
	,0x51,0x55,0x57,0x5a,0x5d,0x60,0x63,0x66,0x69,0x6c,0x6f,0x72,0x76,0x79,0x7c,0x80}; 

uint f;	//global frequency variable
uint T; //T is 1/256 of period
uchar subscript;  //subscript of a period, range 0-255
uint count; //count variable used in timer

void delay_ms(unsigned int x)
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void delay_us()
{
	unsigned char n=0;
	for(n=220;n>0;n--)
	{
		_nop_();
	}
}

void delay(uint x)
{
	uint i;
	for(i = x;i>0;i--);
}
void LCD_write_com(unsigned char com)
{
	LCD_RS=0;
	LCD_data_port=com;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
}

void LCD_write_data(unsigned char date)
{
	LCD_RS=1;
	LCD_data_port=date;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
}

void LCD_write_array(unsigned char *shu)
{
	LCD_RS=1;
	LCD_EN=0;
	while((*shu)!='\0')
	{
		LCD_data_port = *shu ;
		delay_us();
		LCD_EN=1;
		delay_us();
		LCD_EN=0;
		delay_us();
		shu++;
	}
}

void LCD_initial()
{
	LCD_RW=0;
	LCD_EN=0;
	LCD_write_com(0x38); // display contral
	LCD_write_com(0x0c);
	LCD_write_com(0x06);
	LCD_write_com(0x01); // clear screen
	delay_ms(10); // wait for clear
}

void disp_waveform(char x)
{
	switch(x)
	{
	case SQUARE:
		LCD_write_com(0x80); // first line of LCD
		LCD_write_array(func_square);
		break;
	case TRIANGLE:
		LCD_write_com(0x80); // first line of LCD
		LCD_write_array(func_triangle);
		break;
	case SAWTOOTH:
		LCD_write_com(0x80); // first line of LCD
		LCD_write_array(func_sawtooth);
		break;
	case SINE:	
		LCD_write_com(0x80); // first line of LCD
		LCD_write_array(func_sine);
		break;
	}
}

void disp_freq()
{
	freq[6] = f/100 + '0';
	freq[7] = f/10%10 + '0';
	freq[8] = f%10 + '0';
	LCD_write_com(0xc0); // second line of LCD
	LCD_write_array(freq);//
}

void keyscan()
{
	if(key_select == 0)
	{
		delay_ms(5);
		if(key_select == 0)
		{
			while(!key_select);
			form++;
			if(form == 5)
			{
				f = 50;
				form = 0;
			}
			disp_waveform(form);
		}
	}
	if(key_100 == 0)
	{
		delay_ms(5);
		if(key_100 == 0)
		{
			while(!key_100);
			if(form == 4)
				duty = (duty + 10)%100;
			else
				f += 100;
			disp_freq();
		}
	}
	if(key_10 == 0)
	{
		delay_ms(5);
		if(key_10 == 0)
		{
			while(!key_10);
			if(form == 4)
				duty = (duty - 10)%100;
			else
					f -= 100;
			disp_freq();
		}
	}
}

void main()
{
	LCD_initial();
	TMOD = 0x00;
	TH0 = 0xff;
	TL0 = 0x17;
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	val = 0;
	subscript = 0;
	form = 0;
	count = 0;
	f = 100;
	duty = 50;
	while(1)
	{
		T = 2000/f;
		keyscan();
		if(form == SQUARE)
		{
			if(subscript < 128)
				val = 255;
			else
				val = 0;
		}
		if(form == TRIANGLE)
		{
			if(subscript < 128)
				val = 2*subscript;
			else
				val = 255- 2*subscript;
		}
		if(form == SAWTOOTH)
		{
				val = subscript;
		}
		if(form == SINE)
		{
				val = sinval[subscript];
		}
		if(form == PWM)
		{
				if(subscript < 255*duty/100)
					val = 255;
				else
					val = 0;
		}
		DA = val;
	}
}

void timer0() interrupt 1
{
	count++;
	if(count >= T)
	{
		count = 0;
		subscript++;
	}
	TH0 = 0xff;
	TL0 = 0x17;
}