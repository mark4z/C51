#include <reg51.h>			//头文件

//倒计时
unsigned char buf[4];							//片选数码管变量
unsigned int EW_time_default = 15;  	  //东西默认值
unsigned int SN_time_default = 15;			//南北默认值
unsigned int EW_time_now = 7;		//东西方向当前数秒
unsigned int SN_time_now = 10;		//南北方向当前数秒
unsigned int SN_Yellow_time_default = 3;		//南北方向黄灯
unsigned int EW_Yellow_time_default = 3;		//东西方向黄灯
unsigned int SN_Yellow_time_now = 3;		//南北方向黄灯
unsigned int EW_Yellow_time_now = 3;		//东西方向黄灯

//通行
unsigned int traffic_light_signal = 0; //交通灯信号标志位
unsigned int SN_or_EW = 1; //0：南北通行 1：东西通行
unsigned int Open = 1;
unsigned int SN_flash = 0; //南北黄灯闪烁标志
unsigned int EW_flash = 0; //东西黄灯闪烁标志

//智能延时
unsigned int sensor1_num = 0;
unsigned int sensor2_num = 0;

//字型码
unsigned char code LED[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

//计数
unsigned int time0_count; //1s定时
unsigned int flash_count; //0.5s定时
unsigned int flash_signl; //闪烁计数信号

//后台通信
unsigned int flag = 0;

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
void flash();			//黄灯闪烁
void Yellow_adjustment();			//根据行人数量调整时间
void sendChar(unsigned int Value);			//发送消息

void main() {
	init();
	while (1) {
		display();
		//调整信号灯
		traffic_light();
	}
}

void init() {
	//开总中断
	EA = 1;
	//外部中断
	IT0 = 1; //跳变沿
	EX0 = 1; //中断允许
	IT1 = 1; //跳变沿
	EX1 = 1; //中断允许

	ET0 = 1; //开定时器0
	//定时器0初始化
	Timer0Init();
}

void time0()
interrupt 1
{
	//重置定时器
	TH0 = 0x4c;
	TL0 = 0x00;
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
{
	switch (traffic_light_signal) {
	case 0: //东西方向通行  绿灯亮
		Green_EW = Open;
		Red_EW = !Open;
		EW_flash = !Open;

		Green_SN = !Open;
		Red_SN = Open;
		SN_flash = !Open;

		break;
	case 1: //东西方向通行  黄灯闪
		Green_EW = !Open;
		Red_EW = !Open;
		EW_flash = Open;

		Green_SN = !Open;
		Yellow_SN = !Open;
		Red_SN = Open;
		SN_flash = !Open;

		break;
	case 2: //南北方向通行  绿灯亮
		Green_EW = !Open;
		Red_EW = Open;
		EW_flash = !Open;

		Green_SN = Open;
		Red_SN = !Open;
		SN_flash = !Open;

		break;
	case 3: //南北方向通行  黄灯闪
		Green_EW = !Open;
		Red_EW = Open;
		EW_flash = !Open;

		Green_SN = !Open;
		Red_SN = !Open;
		SN_flash = Open;

		break;
	}
}

void flash() {
	flash_count++;
	if (flash_count >= 10) { //0.5s闪烁一次
		flash_count = 0;
		flash_signl++;
		if (flash_signl > 10)
			flash_signl = 0; //闪烁信号清零

		//黄灯闪烁
		if (SN_flash) {
			Yellow_SN = flash_signl % 2;
		} else {
			Yellow_SN = !Open;
		}
		if (EW_flash) {
			Yellow_EW = flash_signl % 2;
		} else {
			Yellow_EW = !Open;
		}
	}
}

void LED_light() //倒计时
{
	time0_count++;
	if (time0_count >= 19) {
		//每秒检测一次，归零后重置，并切换通行方向
		time0_count = 0;
		//东西通行
		if (SN_or_EW) {
			if (EW_time_now > 0 && EW_flash == 0) //正常绿灯
					{
				traffic_light_signal = 0;
				EW_flash = 0;
			}
			if (EW_time_now <= 0 && EW_flash == 0) //绿灯倒计时结束，切换黄灯
					{
				Yellow_adjustment();
				EW_time_now = EW_Yellow_time_now;
				EW_flash = 1;
				traffic_light_signal = 1;
			}
			if (EW_time_now <= 0 && EW_flash == 1) //黄灯倒计时结束，切换通行方向
					{
				EW_time_now = EW_time_default;
				SN_time_now = SN_time_default;
				//重置可调节黄灯时间
				EW_Yellow_time_now = EW_Yellow_time_default;
				SN_Yellow_time_now = SN_Yellow_time_default;

				EW_flash = 0;
				SN_or_EW = !SN_or_EW;
			}
			if (SN_time_now <= 0)   //东西方向额外等待时间
					{
				SN_time_now = EW_time_now;
			}
		}
		//南北通行
		else {
			if (SN_time_now > 0 && SN_flash == 0)   //正常绿灯
					{
				traffic_light_signal = 2;
				SN_flash = 0;
			}
			if (SN_time_now <= 0 && SN_flash == 0)   //绿灯倒计时结束，切换黄灯
					{
				Yellow_adjustment();
				SN_time_now = SN_Yellow_time_now;
				SN_flash = 1;
				traffic_light_signal = 3;
			}
			if (SN_time_now <= 0 && SN_flash == 1)   //黄灯倒计时结束，切换通行方向
					{
				EW_time_now = EW_time_default;
				SN_time_now = SN_time_default;
				//重置可调节黄灯时间
				EW_Yellow_time_now = EW_Yellow_time_default;
				SN_Yellow_time_now = SN_Yellow_time_default;
				SN_flash = 0;
				SN_or_EW = !SN_or_EW;
			}
			if (EW_time_now <= 0)   //南北方向额外等待时间
					{
				EW_time_now = SN_time_now;
			}
		}
		SN_time_now--;
		EW_time_now--;
	}
}
void Yellow_adjustment() //根据人数调整黄灯时间
{
	if (SN_or_EW) {
		EW_Yellow_time_now += sensor1_num + sensor2_num / 3;
		EW_Yellow_time_now =
				(EW_Yellow_time_now > 10) ? 10 : EW_Yellow_time_now;
	} else {
		SN_Yellow_time_now += sensor1_num + sensor2_num / 3;
		SN_Yellow_time_now =
				(SN_Yellow_time_now > 10) ? 10 : SN_Yellow_time_now;
	}
	//发送当前数据到后台
	sendChar(sensor1_num+sensor1_num);
	
	//行人计数重置
	sensor1_num = 0;
	sensor2_num = 0;
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

	TMOD = 0x21;	//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	TF0 = 0;		  //清除TF0标志
	TR0 = 1;		  //定时器0开始计时

	//Time1初始化 波特率9600
	//TMOD = 0x20;	//设置定时器模式
	SCON = 0x50;
	PCON = 0x00;
	TL1 = 0xFD;
	TH1 = 0xFD;
	TR1 = 1;
	ES = 1;
}
void sendChar(unsigned int Value) {
	SBUF = Value;
	flag = 1;
}

void sensor1()
interrupt 0
{
	if(!SN_flash || !EW_flash) {
		sensor1_num++;
	}
}

void sensor2()
interrupt 2
{
	if(!SN_flash || !EW_flash) {
		sensor2_num++;
	}
}
void serial() interrupt 4 {
	if(RI)
	{
		RI = 0;
		P0=SBUF;
	}

	if(TI)
	{
		TI = 0;
	}
}

