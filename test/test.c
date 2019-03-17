#include<reg51.h>
sbit A1=P1^1;
sbit B1=P1^0;
void delay()
{
    unsigned int i=0,j=0;
    for(i=0; i<1; i++)
        for(j=0; j<21738; j++);
}
void delay2()
{
    unsigned int i=0,j=0;
    for(i=0; i<1; i++)
        for(j=0; j<217; j++);
}
void main()
{
	  char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
    unsigned int i ;
    int shi,ge;
    while(1) {
			for (i=60;i>0;i--){
				shi=i/10;
				ge=i%10;
				A1=1;B1=0;
        P3=table[ge];
				delay2();
				A1=0;B1=1;
        P3=table[shi];
				delay2();
				delay();
}
    }
}