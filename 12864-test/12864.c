//#######################################################
//
//    试  验 名 称: 图形液晶 128*64 显示程序
//
//    试  验 功 能: 通过128*64进行汉字,字符的显示
//
//    实验硬件环境: 所有程序均在"亿唯电子"公司 MINI51实验板上测试成功,
//                  主控芯片: STC公司的 STC12C5A16S2 单片机
//   				晶振频率: 11.0592MHz 
//       
//    更多程序下载>>亿唯电子: www.evmcu.net
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

#define LCD_data_port P1 // 数据端口定义

void delay_ms(unsigned int x) // 延时毫秒级
{
	unsigned int a=0,b=0,c=0;
	for(a=x;a>0;a--)
	for(b=5;b>0;b--)
	for(c=128;c>0;c--);
}

void delay_us() // 固定延时100微秒
{
	unsigned char n=0;
	for(n=220;n>0;n--)
	{
		_nop_();
	}
}

////////////////////////////////*液晶显示程序*/////////////////////////////

void LCD_write_com(unsigned char shu)//写指令
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

void LCD_write_data(unsigned char shu)//写数据
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

void LCD_write_array(unsigned char *shu) // 写字符串
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

/////////////////////////////////*液晶初始化*///////////////////////////////
void LCD_initial()//液晶初始化
{
	LCD_EN=0;
	LCD_write_com(0x30);
	LCD_write_com(0x0c);
	LCD_write_com(0x01);
	LCD_write_com(0x06);
	delay_ms(10); // 等待一段时间用于清屏
}

void main(void)
{
	LCD_initial();
	while(1)
	{
		LCD_write_com(0x81);
		LCD_write_array("Designed By");
		LCD_write_com(0x92);
		LCD_write_array("亿唯电子");
		LCD_write_com(0x89);
		LCD_write_array("WWW.EVMCU.NET");
		LCD_write_com(0x99);
		LCD_write_array("QQ:1164601485");
		delay_ms(100);

		while(1);
	}
}