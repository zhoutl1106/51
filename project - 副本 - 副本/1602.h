unsigned char table[]="t1=  s,t2=  s";
unsigned char table1[]="t3=  s,total=   ";

void LCD_write_com(unsigned char com) // дָ��
{
	LCD_RS=0;
	LCD_data_port=com;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
}

void LCD_write_data(unsigned char date) // д����
{
	LCD_RS=1;
	LCD_data_port=date;
	delay_us();
	LCD_EN=1;
	delay_us();
	LCD_EN=0;
}

void LCD_write_array(unsigned char *shu) // д�ַ���
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
	LCD_write_com(0x38); // ��ʾ����
	LCD_write_com(0x0c);
	LCD_write_com(0x06);
	LCD_write_com(0x01); // ����
	delay_ms(10); // �ȴ�һ��ʱ����������
}

void Show()
{
	LCD_initial(); // Һ����ʼ��
	
	table[3]=t1/10+'0';
	table[4]=t1%10+'0';
	table[10]=t2/10+'0';
	table[11]=t2%10+'0';
	table1[3]=t3/10+'0';
	table1[4]=t3%10+'0';
	table1[13]=(t1+t2+t3)/100+'0';
	table1[14]=(t1+t2+t3)%100/10+'0';
	table1[15]=(t1+t2+t3)%10+'0';

	LCD_write_com(0x80); // �趨����ָ���ַ(Һ����һ������)
	LCD_write_array(table); // д�ַ��� table
	LCD_write_com(0xc0); // �趨����ָ���ַ(Һ���ڶ�������)
	LCD_write_array(table1);// д�ַ��� table1
}
