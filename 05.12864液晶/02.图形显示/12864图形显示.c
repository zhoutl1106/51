//#######################################################
//
//  试  验 名 称: 图形液晶 128*64 显示程序
//
//  试  验 功 能: 通过128*64进行图形的显示
//
//  实验硬件环境: 所有程序均在"亿唯电子"公司 MINI51实验板上测试成功,
//                主控芯片: STC公司的 STC12C5A16S2 单片机
//                晶振频率: 11.0592MHz 
//
//  更多程序下载>>亿唯电子: www.evmcu.net 
//
//#######################################################

#include<reg52.h>
#include<BMP.h> // 本文件为自定义文件,包含所要显示的图形的数据
#include<intrins.h>

sbit 	LCD_EN   = P3^7 ;
sbit    LCD_PSB  = P3^6 ;
sbit    LCD_RW   = P3^5 ;
sbit    LCD_RS   = P3^4 ;

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

void delay_8us()// 固定延时八微秒  
{
	unsigned char n=0;
	for(n=14;n>0;n--) _nop_();
}

////////////////////////////////*液晶显示程序*/////////////////////////////

void LCD_write_com(unsigned char shu)//写指令
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
	delay_us(); // 留给128*64一定的处理时间, 芯片资料推荐是75 微秒
}

void LCD_write_data(unsigned char shu)//写数据
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
	delay_us(); // 留给128*64一定的处理时间, 芯片资料推荐是75 微秒
}

void LCD_write_array(unsigned char *shu) // 写字符串
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

void LCD_dis_figure(unsigned char *img) // 显示一幅64*128 的图形
{
	volatile unsigned int i=0,point=0,x=0,y=0;
	for(i=0;i<2;i++)
	{
		for(y=0;y<32;y++)
		{
			for(x=0;x<8;x++)
			{
				LCD_write_com(0x34);	   // 关闭图形显示,设定为扩充指令集工作
				LCD_write_com(0x80+y);     // 行地址
				LCD_write_com(0x80+x+i*8); // 列地址
				LCD_write_data(img[point++]); // 连续写入两字节的数据
				LCD_write_data(img[point++]);
			}
		}
	}
	LCD_write_com(0x36); // 开启图形显示
}


//////////////  * 清除图形显示 RAM */////////////////

void LCD_clr_figure() 
{
	volatile unsigned int x=0,y=0;
	for(y=0;y<32;y++)
	{
		for(x=0;x<16;x++)
		{
			LCD_write_com(0x34);	// 关闭图形显示,设定为扩充指令集工作
			LCD_write_com(0x80+y);  // 行地址
			LCD_write_com(0x80+x);  // 列地址
			LCD_write_data(0x00);	// 连续写入两字节的数据
			LCD_write_data(0x00);	// 连续写入两字节的数据
		}
	}
	LCD_write_com(0x36); // 开启图形显示
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
	delay_ms(100);
	LCD_initial();
	while(1)
	{ 	
		LCD_dis_figure(BMP_0); // 显示第一幅图像
		delay_ms(4000);
		LCD_clr_figure();
		LCD_dis_figure(BMP); // 显示第二幅图像
		while(1);
	}
}