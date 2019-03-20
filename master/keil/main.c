#include <reg51.h>			//头文件


//倒计时
unsigned char buf[4];							//片选数码管变量
unsigned int EW_time_default = 15;  	  //东西默认值
unsigned int SN_time_default = 10;			//南北默认值
unsigned int EW_time_now = 15;		//东西方向当前数秒
unsigned int SN_time_now = 10;		//南北方向当前数秒

//通行
unsigned int SN_or_EW=0; //0：南北通行 1：东西通行
unsigned int Open=1;
unsigned int SN_flash=0; //南北黄灯闪烁标志
unsigned int EW_flash=0; //东西黄灯闪烁标志

//字型码
unsigned char code LED[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};


//计数
unsigned int time0_count; //1s定时
unsigned int flash_count; //0.5s定时
unsigned int flash_signl; //闪烁计数信号

//红绿灯
sbit Green_EW = P2 ^ 1;		//东西
sbit Yellow_EW = P2 ^ 2;
sbit Red_EW = P2 ^ 3;

sbit Red_SN = P2 ^ 6;		//南北
sbit Yellow_SN = P2 ^ 5;
sbit Green_SN = P2 ^ 4;

//函数声明
void delay(int ms);			//延时
void display();				//显示倒计时
void init();   				//开机初始化
void Timer0Init();       //定时器0
void traffic_light(); //控制信号灯
void LED_light();      //控制倒计时
void flash();					//黄灯闪烁

void main()
{
    init();
    while (1) {
      display();
    }
}

void init()
{
    //开总中断
    EA = 1;
	  ET0 = 1;      //开定时器0
    //定时器0
    Timer0Init();
}

void time0() interrupt 1
{
    //重置定时器
    TH0 = 0x4c;
    TL0 = 0x00;
		//调整信号灯
		traffic_light();
	  //调整倒计时
		LED_light();
	  //调整黄灯
		flash();
}

void display() //显示子程序
{

	    
	
    //南北方向个位十位
    buf[0] = SN_time_now / 10;
    buf[1] = SN_time_now % 10;
    //东西方向个位十位
    buf[2] = EW_time_now / 10;
    buf[3] = EW_time_now % 10;

    //点亮南北方向倒计时
    P1 = 0x01;           		//片选LED1
    P0 = LED[buf[0]];			//送南北时间十位的数码管编码
    delay(1);				//延时			
	
    P1 = 0x02;             	//片选LED2
    P0 = LED[buf[1]];
    delay(1);
		
    P1 = 0X04;		  		//片选LED3
    P0 = LED[buf[2]];		    //送东西时间十位的数码管编码
    delay(1);				//延时
		
    P1 = 0X08;				//片选LED4
    P0 = LED[buf[3]];
    delay(1);	
}

void traffic_light() //信号灯
{         //
	if((SN_or_EW))
	{
		//东西方向通行  绿灯亮
    if(EW_time_now>5){Green_EW=Open;EW_flash=!Open;} //小于5s时，黄灯闪烁
		else{Green_EW=!Open;EW_flash=Open;}
		Red_EW=!Open;
		//南北方向进禁行 红灯亮
		SN_flash=!Open;  //关闭黄灯
		Green_SN=!Open;
		Red_SN=Open;
  }
	else{
		//东西方向禁行  红灯亮
		EW_flash=!Open; //关闭黄灯
    Green_EW=!Open;
		Red_EW=Open;
		//南北方向通行绿灯亮
		if(SN_time_now>5){Green_SN=Open;SN_flash=!Open;} //小于5s时，黄灯闪烁
		else{Green_SN=!Open; SN_flash=Open;}
		Red_SN=!Open;
}
}

void flash()
{
	flash_count++;
	if(flash_count>=10)  //0.5s闪烁一次
		{
			flash_count=0;
			flash_signl++;
			if(flash_signl>10)
				flash_signl=0; //闪烁信号清零
			
			//黄灯闪烁
			if(SN_flash)
			{Yellow_SN=flash_signl%2;}
			else {Yellow_SN=!Open;}
			if(EW_flash)
			{Yellow_EW=flash_signl%2;}
			else {Yellow_EW=!Open;}
		}
}

void LED_light() //倒计时
{
		time0_count++;
    if(time0_count >= 20) 
		{
			//每秒检测一次，归零后重置，并切换通信方向
        time0_count = 0;
        if(EW_time_now > 0) {
            SN_time_now--;
					  EW_time_now--;
					 if(SN_time_now<=0)
						 {
							 SN_time_now=EW_time_now;
						}
        } else {
            SN_time_now = SN_time_default;
					  EW_time_now = EW_time_default;
						SN_or_EW=!SN_or_EW;
        }
			}
}

void delay(int ms)			//延时子程序
{
    unsigned int j, k;
    for (j = 0; j < ms; j++)
        for (k = 0; k < 124; k++)
            ;
}

void Timer0Init()		//50毫秒@11.0592MHz
{
    TMOD = 0x01;	//设置定时器模式
    TL0 = 0x00;		//设置定时初值
    TH0 = 0x4C;		//设置定时初值
    TF0 = 0;		  //清除TF0标志
    TR0 = 1;		  //定时器0开始计时
}

