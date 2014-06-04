//##################################################
//
//    实  验 名 称: 液晶1602显示程序
//
//    试  验 功 能: 通过1602进行显示
//
//    实验硬件环境: 所有程序均在"亿唯电子"公司 MINI51实验板上测试成功,
//                  主控芯片: STC公司的 STC12C5A16S2 单片机
//                  晶振频率: 11.0592MHz 
//       
//    更多程序下载>>亿唯电子：www.evmcu.net
//
//##################################################

#include<reg52.h>
#include<intrins.h>
unsigned char table[]="t1=  s,t2=  s";
unsigned char table1[]="t3=  s,total=   ";

sbit LCD_RS=P3^0; // 数据指令选择端定义
sbit LCD_RW=P3^1;
sbit LCD_EN=P3^2; // 使能端定义

#define LCD_data_port P2  // 定义给液晶送数的端口

unsigned int t1,t2,t3;

void delay_ms(unsigned int x) // 延时毫秒级
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void delay_us() // 延时100微秒
{
	unsigned char n=0;
	for(n=220;n>0;n--)
	{
		_nop_();
	}
}

void LCD_write_com(unsigned char com) // 写指令
{
	LCD_RS=0;
	LCD_data_port=com;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
}

void LCD_write_data(unsigned char date) // 写数据
{
	LCD_RS=1;
	LCD_data_port=date;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
}

void LCD_write_array(unsigned char *shu) // 写字符串
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
	LCD_write_com(0x38); // 显示设置
	LCD_write_com(0x0c);
	LCD_write_com(0x06);
	LCD_write_com(0x01); // 清屏
	delay_ms(10); // 等待一段时间用于清屏
}

void main()
{
	unsigned char n=0;
	LCD_initial(); // 液晶初始化
	t1=31,t2=62,t3=89;
	table[3]=t1/10+'0';
	table[4]=t1%10+'0';
	table[10]=t2/10+'0';
	table[11]=t2%10+'0';
	table1[3]=t3/10+'0';
	table1[4]=t3%10+'0';
	table1[13]=(t1+t2+t3)/100+'0';
	table1[14]=(t1+t2+t3)%100/10+'0';
	table1[15]=(t1+t2+t3)%10+'0';

	LCD_write_com(0x80); // 设定数据指针地址(液晶第一行数据)
	LCD_write_array(table); // 写字符串 table
	LCD_write_com(0xc0); // 设定数据指针地址(液晶第二行数据)
	LCD_write_array(table1);// 写字符串 table1

	
	while(1);
}

