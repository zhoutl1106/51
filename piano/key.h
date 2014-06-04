
char keyscan()   //键盘扫描程序,取回一个键盘号
{	uchar temp;
   duank=0xfe;
   temp=duank;
   temp=temp&0xf0;
   while(temp!=0xf0)
    {
     delay(50);
     temp=duank;
     temp=temp&0xf0;
     while(temp!=0xf0)
     {
      temp=duank;
     switch(temp)
      {
       case 0xee:num=-4;
        break;
       case 0xde:num=-5;
        break;
       case 0xbe:num=-6;
        break;
       case 0x7e:num=-7;
        break;
      }
     while(temp!=0xf0)
      {
       temp=duank;
       temp=temp&0xf0;
      }
     }
    }

   duank=0xfd;
   temp=duank;
   temp=temp&0xf0;
   while(temp!=0xf0)
    {
     delay(50);
     temp=duank;
     temp=temp&0xf0;
     while(temp!=0xf0)
     {
      temp=duank;
     switch(temp)
      {
       case 0xed:num=1;
        break;
       case 0xdd:num=2;
        break;
       case 0xbd:num=3;
        break;
       case 0x7d:num=4;
        break;
      }
     while(temp!=0xf0)
      {
       temp=duank;
       temp=temp&0xf0;
      }
     }
    }


   duank=0xfb;
   temp=duank;
   temp=temp&0xf0;
   while(temp!=0xf0)
    {
     delay(50);
     temp=duank;
     temp=temp&0xf0;
     while(temp!=0xf0)
     {
      temp=duank;
     switch(temp)
      {
       case 0xeb:num=5;
        break;
       case 0xdb:num=6;
        break;
       case 0xbb:num=7;
        break;
       case 0x7b:num=8;
        break;
      }
     while(temp!=0xf0)
      {
       temp=duank;
       temp=temp&0xf0;
      }
     }
    }


   duank=0xf7;
   temp=duank;
   temp=temp&0xf0;
   while(temp!=0xf0)
    {
     delay(50);
     temp=duank;
     temp=temp&0xf0;
     while(temp!=0xf0)
     {
      temp=duank;
     switch(temp)
      {
       case 0xe7:num=9;
        break;
       case 0xd7:num=10;
        break;
       case 0xb7:num=11;
        break;
       case 0x77:num=12;
        break;
      }
     while(temp!=0xf0)
      {
       temp=duank;
       temp=temp&0xf0;
      }
     }
    }
	if(key1==0)
	{
		delay(50);
		if(key1==0)
			num=21;
		while(key1==0);
	}
	if(key2==0)
	{
		delay(50);
		if(key2==0)
			num=22;
		while(key2==0);
	}
	if(key3==0)
	{
		delay(50);
		if(key3==0)
			num=23;
		while(key3==0);
	}
	if(key4==0)
	{
		delay(50);
		if(key4==0)
			num=24;
		while(key4==0);
	}
	if(key5==0)
	{
		delay(50);
		if(key5==0)
			num=-1;
		while(key5==0);
	}
	if(key6==0)
	{
		delay(50);
		if(key6==0)
			num=-2;
		while(key6==0);
	}
	if(key7==0)
	{
		delay(50);
		if(key7==0)
			num=-3;
		while(key7==0);
	}
return num;

}
