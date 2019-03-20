#include <reg51.h>			//Í·ÎÄ¼þ


//µ¹¼ÆÊ±
unsigned char buf[4];							//Æ¬Ñ¡ÊýÂë¹Ü±äÁ¿
unsigned int EW_time_default = 15;  	  //¶«Î÷Ä¬ÈÏÖµ
unsigned int SN_time_default = 10;			//ÄÏ±±Ä¬ÈÏÖµ
unsigned int EW_time_now = 15;		//¶«Î÷·½Ïòµ±Ç°ÊýÃë
unsigned int SN_time_now = 10;		//ÄÏ±±·½Ïòµ±Ç°ÊýÃë

//Í¨ÐÐ
unsigned int SN_or_EW=0; //0£ºÄÏ±±Í¨ÐÐ 1£º¶«Î÷Í¨ÐÐ
unsigned int Open=1;
unsigned int SN_flash=0; //ÄÏ±±»ÆµÆÉÁË¸±êÖ¾
unsigned int EW_flash=0; //¶«Î÷»ÆµÆÉÁË¸±êÖ¾

//×ÖÐÍÂë
unsigned char code LED[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};


//¼ÆÊý
unsigned int time0_count; //1s¶¨Ê±
unsigned int flash_count; //0.5s¶¨Ê±
unsigned int flash_signl; //ÉÁË¸¼ÆÊýÐÅºÅ

//ºìÂÌµÆ
sbit Green_EW = P2 ^ 1;		//¶«Î÷
sbit Yellow_EW = P2 ^ 2;
sbit Red_EW = P2 ^ 3;

sbit Red_SN = P2 ^ 6;		//ÄÏ±±
sbit Yellow_SN = P2 ^ 5;
sbit Green_SN = P2 ^ 4;

//º¯ÊýÉùÃ÷
void delay(int ms);			//ÑÓÊ±
void display();				//ÏÔÊ¾µ¹¼ÆÊ±
void init();   				//¿ª»ú³õÊ¼»¯
void Timer0Init();       //¶¨Ê±Æ÷0
void traffic_light(); //¿ØÖÆÐÅºÅµÆ
void LED_light();      //¿ØÖÆµ¹¼ÆÊ±
void flash();					//»ÆµÆÉÁË¸

void main()
{
    init();
    while (1) {
      display();
    }
}

void init()
{
    //¿ª×ÜÖÐ¶Ï
    EA = 1;
	  ET0 = 1;      //¿ª¶¨Ê±Æ÷0
    //¶¨Ê±Æ÷0
    Timer0Init();
}

void time0() interrupt 1
{
    //ÖØÖÃ¶¨Ê±Æ÷
    TH0 = 0x4c;
    TL0 = 0x00;
		//µ÷ÕûÐÅºÅµÆ
		traffic_light();
	  //µ÷Õûµ¹¼ÆÊ±
		LED_light();
	  //µ÷Õû»ÆµÆ
		flash();
}

void display() //ÏÔÊ¾×Ó³ÌÐò
{

	    
	
    //ÄÏ±±·½Ïò¸öÎ»Ê®Î»
    buf[0] = SN_time_now / 10;
    buf[1] = SN_time_now % 10;
    //¶«Î÷·½Ïò¸öÎ»Ê®Î»
    buf[2] = EW_time_now / 10;
    buf[3] = EW_time_now % 10;

    //µãÁÁÄÏ±±·½Ïòµ¹¼ÆÊ±
    P1 = 0x01;           		//Æ¬Ñ¡LED1
    P0 = LED[buf[0]];			//ËÍÄÏ±±Ê±¼äÊ®Î»µÄÊýÂë¹Ü±àÂë
    delay(1);				//ÑÓÊ±			
	
    P1 = 0x02;             	//Æ¬Ñ¡LED2
    P0 = LED[buf[1]];
    delay(1);
		
    P1 = 0X04;		  		//Æ¬Ñ¡LED3
    P0 = LED[buf[2]];		    //ËÍ¶«Î÷Ê±¼äÊ®Î»µÄÊýÂë¹Ü±àÂë
    delay(1);				//ÑÓÊ±
		
    P1 = 0X08;				//Æ¬Ñ¡LED4
    P0 = LED[buf[3]];
    delay(1);	
}

void traffic_light() //ÐÅºÅµÆ
{         //
	if((SN_or_EW))
	{
		//¶«Î÷·½ÏòÍ¨ÐÐ  ÂÌµÆÁÁ
    if(EW_time_now>5){Green_EW=Open;EW_flash=!Open;} //Ð¡ÓÚ5sÊ±£¬»ÆµÆÉÁË¸
		else{Green_EW=!Open;EW_flash=Open;}
		Red_EW=!Open;
		//ÄÏ±±·½Ïò½ø½ûÐÐ ºìµÆÁÁ
		SN_flash=!Open;  //¹Ø±Õ»ÆµÆ
		Green_SN=!Open;
		Red_SN=Open;
  }
	else{
		//¶«Î÷·½Ïò½ûÐÐ  ºìµÆÁÁ
		EW_flash=!Open; //¹Ø±Õ»ÆµÆ
    Green_EW=!Open;
		Red_EW=Open;
		//ÄÏ±±·½ÏòÍ¨ÐÐûÐÂÌµÆÁÁ
		if(SN_time_now>5){Green_SN=Open;SN_flash=!Open;} //Ð¡ÓÚ5sÊ±£¬»ÆµÆÉÁË¸
		else{Green_SN=!Open; SN_flash=Open;}
		Red_SN=!Open;
}
}

void flash()
{
	flash_count++;
	if(flash_count>=10)  //0.5sÉÁË¸Ò»´Î
		{
			flash_count=0;
			flash_signl++;
			if(flash_signl>10)
				flash_signl=0; //ÉÁË¸ÐÅºÅÇåÁã
			
			//»ÆµÆÉÁË¸
			if(SN_flash) {Yellow_SN=flash_signl%2;}
			else {Yellow_SN=!Open;}
			if(EW_flash) {Yellow_EW=flash_signl%2;}
			else {Yellow_EW=!Open;}
		}
}

void LED_light() //µ¹¼ÆÊ±
{
		time0_count++;
    if(time0_count >= 20) 
		{
			//Ã¿Ãë¼ì²âÒ»´Î£¬¹éÁãºóÖØÖÃ£¬²¢ÇÐ»»Í¨ÐÐ·½Ïò
        time0_count = 0;
			//¶«Î÷Í¨ÐÐÊ
        if(EW_time_now > 0) {
            SN_time_now--;
					  EW_time_now--;
					 if(SN_time_now<=0)
						 {
							 if(SN_or_EW){
									SN_time_now=EW_time_now;}
						   }else{EW_time_now=SN_time_now;}
        } else {
            SN_time_now = SN_time_default;
					  EW_time_now = EW_time_default;
						SN_or_EW=!SN_or_EW;
        }
			}
}

void delay(int ms)			//ÑÓÊ±×Ó³ÌÐò
{
    unsigned int j, k;
    for (j = 0; j < ms; j++)
        for (k = 0; k < 124; k++)
            ;
}

void Timer0Init()		//50ºÁÃë@11.0592MHz
{
    TMOD = 0x01;	//ÉèÖÃ¶¨Ê±Æ÷Ä£Ê½
    TL0 = 0x00;		//ÉèÖÃ¶¨Ê±³õÖµ
    TH0 = 0x4C;		//ÉèÖÃ¶¨Ê±³õÖµ
    TF0 = 0;		  //Çå³ýTF0±êÖ¾
    TR0 = 1;		  //¶¨Ê±Æ÷0¿ªÊ¼¼ÆÊ±
}

