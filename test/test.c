#include<reg51.h>

void delay()
{
    unsigned int i=0,j=0;
    for(i=0; i<10; i++)
        for(j=0; j<21738; j++);
}
void main()
{
    unsigned int i ;
    unsigned char LED_Data;
    while(1) {
        LED_Data=0x01;
        for(i=0; i<8; i++) {
            P3=~LED_Data;
            delay();
            LED_Data<<=1;
        }
    }
}