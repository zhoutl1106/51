//#######################################################
//
//    ��  �� �� ��: ͼ��Һ�� 128*64 ��ʾ����
//
//    ��  �� �� ��: ͨ��128*64���к���,�ַ�����ʾ
//
//    ʵ��Ӳ������: ���г������"��Ψ����"��˾ MINI51ʵ����ϲ��Գɹ�,
//                  ����оƬ: STC��˾�� STC12C5A16S2 ��Ƭ��
//   				����Ƶ��: 11.0592MHz 
//       
//    �����������>>��Ψ����: www.evmcu.net
//
//#######################################################
#include<reg52.h>
#include<intrins.h>

sbit 	LCD_DI   = P3^0 ;
sbit    LCD_RW   = P3^1 ;
sbit    LCD_EN    = P3^2 ;
sbit    LCD_CS1  = P3^3 ;
sbit    LCD_CS2  = P3^4 ;
sbit    LCD_RST  = P3^5 ;

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

////////////////////////////////*Һ����ʾ����*/////////////////////////////

void LCD_write_com(unsigned char shu)//дָ��
{
	LCD_DI=0;
	LCD_RW=0;
	LCD_EN=0;

	delay_us();
	LCD_data_port = shu ;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
	delay_us();
}

void LCD_write_data(unsigned char shu)//д����
{
	LCD_DI=1;
	LCD_RW=0;
	LCD_EN=0;

	delay_us();
	LCD_data_port = shu ;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
	delay_us();
}

void LCD_write_array(unsigned char *shu) // д�ַ���
{
	LCD_DI=1;
	LCD_RW=0;
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
	LCD_initial();
	while(1)
	{
		LCD_write_com(0x81);
		LCD_write_array("Designed By");
		LCD_write_com(0x92);
		LCD_write_array("��Ψ����");
		LCD_write_com(0x89);
		LCD_write_array("WWW.EVMCU.NET");
		LCD_write_com(0x99);
		LCD_write_array("QQ:1164601485");
		delay_ms(100);

		while(1);
	}
}