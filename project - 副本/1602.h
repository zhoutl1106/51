unsigned char table[]="t1=  s,t2=  s";
unsigned char table1[]="t3=  s,total=   ";

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

void Show()
{
	LCD_initial(); // 液晶初始化
	
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
}
