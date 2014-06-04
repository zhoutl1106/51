#include <STC12C5A.h>
sfr  CCAPMn0  = 0xDA;//PCA Module 0 Mode Register 
void main(void)
{
   CMOD = 0x02;  //Setup PCA timer
   CL	= 0x00;
   CH   = 0x00;
   CCAP0L  = 0xf9;  
   CCAP0H  = 0x25;
   CCAPMn0 = 0x42;
   CR     = 1;//start pca timer
   while(1)
   {};

}
