//#######################################################
//
//  ��  �� �� ��: ͼ��Һ�� 128*64 ��ʾ����
//
//  ��  �� �� ��: ͨ��128*64����ͼ�ε���ʾ
//
//  ʵ��Ӳ������: ���г������"��Ψ����"��˾ MINI51ʵ����ϲ��Գɹ�,
//                ����оƬ: STC��˾�� STC12C5A16S2 ��Ƭ��
//                ����Ƶ��: 11.0592MHz 
//
//  �����������>>��Ψ����: www.evmcu.net 
//
//#######################################################

#include<reg52.h>
#include<BMP.h> // ���ļ�Ϊ�Զ����ļ�,������Ҫ��ʾ��ͼ�ε�����
#include<intrins.h>

sbit 	LCD_EN   = P3^7 ;
sbit    LCD_PSB  = P3^6 ;
sbit    LCD_RW   = P3^5 ;
sbit    LCD_RS   = P3^4 ;

#define LCD_data_port P1 // ���ݶ˿ڶ���

void delay_ms(unsigned int x) // ��ʱ���뼶
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void delay_us() // �̶���ʱ100΢��
{
	unsigned char n=0;
	for(n=220;n>0;n--)
	{
		_nop_();
	}
}

void delay_8us()// �̶���ʱ��΢��  
{
	unsigned char n=0;
	for(n=14;n>0;n--) _nop_();
}

////////////////////////////////*Һ����ʾ����*/////////////////////////////

void LCD_write_com(unsigned char shu)//дָ��
{
	LCD_PSB=1;
	LCD_RS=0;
	LCD_RW=0;
	LCD_EN=0;

	LCD_data_port = shu ;
	delay_8us();
	LCD_EN=1;
	delay_8us();
	LCD_EN=0;
	delay_us(); // ����128*64һ���Ĵ���ʱ��, оƬ�����Ƽ���75 ΢��
}

void LCD_write_data(unsigned char shu)//д����
{
	LCD_PSB=1;
	LCD_RS=1;
	LCD_RW=0;
	LCD_EN=0;

	LCD_data_port = shu ;
	delay_8us();
	LCD_EN=1;
	delay_8us();
	LCD_EN=0;
	delay_us(); // ����128*64һ���Ĵ���ʱ��, оƬ�����Ƽ���75 ΢��
}

void LCD_write_array(unsigned char *shu) // д�ַ���
{
	LCD_PSB=1;
	LCD_RS=1;
	LCD_RW=0;
	LCD_EN=0;

	while((*shu)!='\0')
	{
		LCD_data_port = *shu ;
		delay_8us();
		LCD_EN=1;
		delay_8us();
		LCD_EN=0;
		delay_us();
		shu++;
	}
}

void LCD_dis_figure(unsigned char *img) // ��ʾһ��64*128 ��ͼ��
{
	volatile unsigned int i=0,point=0,x=0,y=0;
	for(i=0;i<2;i++)
	{
		for(y=0;y<32;y++)
		{
			for(x=0;x<8;x++)
			{
				LCD_write_com(0x34);	   // �ر�ͼ����ʾ,�趨Ϊ����ָ�����
				LCD_write_com(0x80+y);     // �е�ַ
				LCD_write_com(0x80+x+i*8); // �е�ַ
				LCD_write_data(img[point++]); // ����д�����ֽڵ�����
				LCD_write_data(img[point++]);
			}
		}
	}
	LCD_write_com(0x36); // ����ͼ����ʾ
}


//////////////  * ���ͼ����ʾ RAM */////////////////

void LCD_clr_figure() 
{
	volatile unsigned int x=0,y=0;
	for(y=0;y<32;y++)
	{
		for(x=0;x<16;x++)
		{
			LCD_write_com(0x34);	// �ر�ͼ����ʾ,�趨Ϊ����ָ�����
			LCD_write_com(0x80+y);  // �е�ַ
			LCD_write_com(0x80+x);  // �е�ַ
			LCD_write_data(0x00);	// ����д�����ֽڵ�����
			LCD_write_data(0x00);	// ����д�����ֽڵ�����
		}
	}
	LCD_write_com(0x36); // ����ͼ����ʾ
}

/////////////////////////////////*Һ����ʼ��*///////////////////////////////

void LCD_initial()//Һ����ʼ��
{
	LCD_EN=0;
	LCD_write_com(0x30);
	LCD_write_com(0x0c);
	LCD_write_com(0x01);
	LCD_write_com(0x06);
	delay_ms(10); // �ȴ�һ��ʱ����������
}

void main(void)
{
	delay_ms(100);
	LCD_initial();
	while(1)
	{ 	
		LCD_dis_figure(BMP_0); // ��ʾ��һ��ͼ��
		delay_ms(4000);
		LCD_clr_figure();
		LCD_dis_figure(BMP); // ��ʾ�ڶ���ͼ��
		while(1);
	}
}