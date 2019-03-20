#include <reg51.h>				//头文件
#define uchar unsigned char
#define uint  unsigned int		//宏定义

uchar  buf[4];					//秒显示的变量
uchar  sec_EW=20;  			//东西数默认
uchar  sec_SN=30;			//南北默认值
float  set_EW_time=20;		//设置东西方向的时间
float  set_SN_time=30;		//设置南北方向的时间
int n;
uchar data countt0,countt1,flag,flag1,flag2,count2,flag3,flag5;//定时器0中断次数
//定义6组开关
sbit  k3=P3^4;		//确认
sbit  k5=P3^1;		//禁止
sbit  k6=P1^5;		//夜间模式
sbit  k7=P3^7;		  //车辆检测，模式键
sbit  k8=P3^5;		  //东西车辆检测
sbit  k9=P3^6;		//南北车辆检测

sbit BUZZ=P3^0;

sbit Red_SN=P2^6;		//南北红灯标志
sbit Yellow_SN=P2^5;	//南北黄灯标志
sbit Green_SN=P2^4;     //南北绿灯标志

sbit Red_EW=P2^3;		//东西红灯标志
sbit Yellow_EW=P2^2;	//东西黄灯标志
sbit Green_EW=P2^1;		//东西绿灯标志
		
bit set=0;				//调时方向切换键标志 =1时，南北，=0时，东西
bit EW_SN=0;			//东西南北控制位
bit Lighting=0;			//闪烁标志位
bit Night=0;			//夜间黄灯闪烁标志位

uchar code table[11]={	//共阴极字型码
	0x3f,  //--0
	0x06,  //--1
	0x5b,  //--2
	0x4f,  //--3
	0x66,  //--4
	0x6d,  //--5
	0x7d,  //--6
	0x07,  //--7
	0x7f,  //--8
	0x6f,  //--9
	0x00   //--NULL
};

//函数的声明部分
void delay(int ms);			//延时子程序
void key();					//按键扫描子程序
void key_to1();				//键处理子程序
void key_to2();
void key_to3();
void display();				//显示子程序
void logo();   				//开机LOGO
void Buzzer();
//主程序
void main()
{
	TMOD=0X11;	   				//定时器设置
	TH1=0X3C;		
	TL1=0XB0;
	TH0=0X3C;					//定时器0置初值 0.05S
	TL0=0XB0;
	EA=1;						//开总中断
	ET0=1;						//定时器0中断开启
	ET1=1;					   //定时器1中断开启
	TR0=1;						//启动定时0
	TR1=0;						 	//关闭定时1
	EX0=1;						//开外部中断0
	EX1=1;						//开外部中断1
    logo();						//开机初始化
	P2=0Xc3;				// 开始默认状态，东西绿灯，南北黄灯   
    sec_SN=sec_EW+5; 			//默认南北通行时间比东西多5秒
	while(1)					  //主循环
	{	 
		key(); 					//调用按键扫描程序
		display(); 				//调用显示程序
	}	
}
//函数的定义部分
	if(k3!=1)							//当K3（确认）键按下时
	{	
		display();       				//调用显示，用于延时消抖
		if(k3!=1)						//如果确定按下
		{	flag=0;
			TR0=1;  						//启动定时器0
			flag3=0;
			TR1=1;
			sec_SN=set_SN_time;				//从中断回复，仍显示设置过的数值
			sec_EW=set_EW_time;				//显示设置过的时间
										//关定时器1	
			if(set==0)						//时间倒时到0时
			{ 
				P2=0X00;					 //灭显示
				Green_EW=1;						//东西绿灯亮
				Red_SN=1;					//南北红灯亮
				sec_SN=sec_EW+5; 			//回到初值
			}
			else 
			{ 
				P2=0x00;					//南北绿灯，东西红灯
				Green_SN=1;
				Red_EW=1;
				sec_EW=sec_SN+5; 
			}
		}
	}
	if(k5!=1)							//当K5（禁止）键按下时
	{
	   	display();       				//调用显示，用于延时消抖
	   	if(k5!=1)						//如果确定按下
	   	{ 	  flag3=0;
		flag5=1-flag5;
		  if(flag5==1)
	    {	TR0=0;						//关定时器
			P2=0x00;					//灭显示
			Red_EW=1;
			Red_SN=1;			}		//全部置红灯  
			if(flag5==0)
{		    TR0=1;
				P2=0X00;					 //灭显示
				Green_EW=1;						//东西绿灯亮
				Red_SN=1;					//南北红灯亮
				sec_EW=set_EW_time;
				sec_SN=sec_EW+5; }		//回到初值
			do
			{
				display(); 				//调用显示，用于延时
			}	
			while(k5!=1);			//等待按键释放	
	   	}
	}
	if(k6!=1)							//当K6（夜间模式）按下 
	{
	   	display();       				//调用显示，用于延时消抖 
	   	if(k6!=1)						//如果确定按下
	   	{ 	
	    	TR0=0;						//关定时器
			P2=0x00;
			flag3=1;
			sec_EW=00;					//四个方向的时间都为00
			sec_SN=00;
			do
			{
				display(); 			  //调用显示，用于延时
			}	
			while(k6!=1);			//等待按键释放	
	   	}
	}
	if(k7!=1)							//当K6（夜间模式）按下 
	{
	   	display();       				//调用显示，用于延时消抖 
	   	if(k7!=1)						//如果确定按下
	   	{
			flag++;		
			if(flag>=99)					 
			flag=0;		   //模式超出范围重置
			if(flag==1)
			{
				TR0=0;TR1=1;
				sec_EW=set_EW_time;
				sec_SN=set_SN_time;	  //显示设置的初始通行时间
				do	
			    { 
					display();       		//调用显示，用于延时
				}
				
				while(k7!=1); 
			}
			if(flag==2)
			{
				TR0=0;TR1=1;
				sec_EW=flag2;
				sec_SN=flag1;				  //显示车辆计数
				do	
			    { 
					display();       		//调用显示，用于延时
				}
				while(k7!=1); 
			}
	   	}
	}
	if(k8!=1)							// 
	{
	   	display();       				//调用显示，用于延时消抖 
	   	if(k8!=1)						//如果确定按下
	   	{
			if(Green_EW==1)
			{
				flag2++;  			//东西车流量加
				if(flag2>=99)
				flag2=0;	
			}
			else if(Red_EW==1)
			{
				BUZZ=0;
				countt1=0;
			}	      
			
			if(flag==0)
			{
				do	
				{ 
					display();       		//调用显示，用于延时
				}
	
				while(k8!=1);
			}
			if(flag==1)
			{
				sec_EW=set_EW_time;
				sec_SN=set_SN_time;				 //显示设置的通行时间
				do	
				{ 
					display();       		//调用显示，用于延时
				}
	
				while(k8!=1);
			}
			if(flag==2)
			{
				sec_SN=flag1;		//显示车辆计数
				sec_EW=flag2;	 
				do	
				{ 
					display();       		//调用显示，用于延时
				}
				while(k8!=1);	
			}
		}
	}
	if(k9!=1)							//
	{
	   	display();       				//调用显示，用于延时消抖 
	   	if(k9!=1)						//如果确定按下
	   	{
			if(Green_SN==1)
			{
				flag1++;				   //南北车流量加
				if(flag1>=99)
				flag1=0;	
			}
			else if(Red_SN==1)
			{
				BUZZ=0;
				countt1=0;
			}				
								   //车辆最大计数99
			if(flag==0)
			{
				do	
				{ 
					display();       		//调用显示，用于延时
				}
			
				while(k9!=1);
			}
			if(flag==1)
			{
				sec_SN=set_SN_time;		//设置的数值赋给东西南北
				sec_EW=set_EW_time;	 
				do	
				{ 
					display();       		//调用显示，用于延时
				}
				while(k9!=1);	
			}
			if(flag==2)
			{
				sec_SN=flag1;		//计数的车辆赋给东西南北
				sec_EW=flag2;	 
				do	
				{ 
					display();       		//调用显示，用于延时
				}
				while(k9!=1);	
			}
	   	}
	}
}
void display(void) //显示子程序
{		
	buf[1]=sec_SN/10; 		//第1位 东西秒十位
	buf[2]=sec_SN%10; 		//第2位 东西秒个位
	buf[3]=sec_EW/10; 		//第3位 南北秒十位
	buf[0]=sec_EW%10; 		//第4位 南北秒个位		
	P1=0xff;          		// 初始灯为灭的
	P0=0x00;				 ////灭显示
	P1=0xfe;           		//片选LED1
	P0=table[buf[1]];		//送东西时间十位的数码管编码			
	delay(1);				//延时
	P1=0xff;				//关显示
	P0=0x00;				//灭显示
						   
	P1=0xfd;             	//片选LED2
	P0=table[buf[2]];		 //送东西时间个位的数码管编码
	delay(1);				 //延时
	P1=0xff;				//关显示
	P0=0x00;				//关显示
	P1=0Xfb;		  		//片选LED3
	P0=table[buf[3]];		//送南北时间十位的数码管编码
	delay(1);				//延时
	P1=0xff;				 //关显示
	P0=0x00;				 //关显示
	P1=0Xf7;				 //片选LED4	
	P0=table[buf[0]];		//送南北时间个位的数码管编码
	delay(1);				//延时
}

void time0(void) interrupt 1 using 1  	//定时中断子程序
{
	TH0=0X3C;							//重赋初值
	TL0=0XB0;							//12m晶振50ms//重赋初值
	TR0=1;								//重新启动定时器
	countt0++;							//软件计数加1
	if(countt0==10)						//加到10也就是半秒
	{
		if((sec_SN<=5)&&(EW_SN==0)&&(Lighting==1))  		//东西黄灯闪		
        {
			Green_EW=0;
			Yellow_EW=0;
		}		   				
	    if((sec_EW<=5)&&(EW_SN==1)&&(Lighting==1))  		//南北黄灯闪		
        {  
			Green_SN=0;
			Yellow_SN=0;
		}	
	}
		
	if(countt0==20)	                  	// 定时器中断次数=20时（即1秒时）
	{	countt0=0;						//清零计数器
		sec_EW--;						//东西时间减1
		sec_SN--;						//南北时间减1
		
//		BUZZ=1;
		if((sec_SN<=5)&&(EW_SN==0)&&(Lighting==1))  		//东西黄灯闪		
        {
			Green_EW=0;
			Yellow_EW=1;
		}		   				
	    if((sec_EW<=5)&&(EW_SN==1)&&(Lighting==1))  		//南北黄灯闪		
        {  
			Green_SN=0;
			Yellow_SN=1;
		}		 						
		if(sec_EW==0&&sec_SN==5) 		//当东西倒计时到0时，重置5秒，用于黄灯闪烁时间   
		{
			sec_EW=5;
			Lighting=1;
		}
		if(sec_SN==0&&sec_EW==5)		//当南北倒计时到0时，重置5秒，用于黄灯闪烁时间   
		{
			sec_SN=5;
			Lighting=1;
		}
		if(EW_SN==0&&sec_SN==0)			//当黄灯闪烁时间倒计时到0时，
		{
			P2=0x00;					//重置东西南背方向的红绿灯
			Green_SN=1;
			Red_EW=1;
			EW_SN=!EW_SN;
			Lighting=0;
																					             
			if(flag1*10/set_SN_time>=5)		   //比如现在通行时间是20秒，那么通过的车大于等于10辆，那么下次通行时间加5秒，变为25秒
			{set_SN_time=set_SN_time+5;}		   //比如现在通行时间是25秒，那么通过的车大于等于12.5（也就是大于等于13辆），那么下次通行时间就加5秒，变为30秒
			else
			{								   //比如现在通行时间是20秒，那么通过的车小于10辆，那么下次通行时间减5秒，变为15秒
				set_SN_time=set_SN_time-5;	   //比如现在通行时间是25秒，那么通过的车小于12.5（也就是大于等于13辆），那么下次通行时间就减5秒，变为20秒
				if(set_SN_time<15)			   //但是减不能无限的减，最小通行时间是15秒
				{
					set_SN_time=15;
				}
			}
			flag1=0;			

			sec_SN=set_SN_time;			//重赋南北方向的起始值
			sec_EW=set_SN_time+5;		//重赋东西方向的起始值
		}		
		if(EW_SN==1&&sec_EW==0)			//当黄灯闪烁时间到
		{
			P2=0X00;					//重置东西南北的红绿灯状态
			Green_EW=1;					 //东西绿灯亮
			Red_SN=1;					 //南北红灯亮
			EW_SN=!EW_SN;				 //取反
			Lighting=0;					//闪烁

			if(flag2*10/set_EW_time>=5)		 //比如现在通行时间是20秒，那么通过的车大于等于10辆，那么下次通行时间加5秒，变为25秒
			{set_EW_time=set_EW_time+5;}		 //比如现在通行时间是25秒，那么通过的车大于等于12.5（也就是大于等于13辆），那么下次通行时间就加5秒，变为30秒
			else
			{								 //比如现在通行时间是20秒，那么通过的车小于10辆，那么下次通行时间减5秒，变为15秒
				set_EW_time=set_EW_time-5;	 //比如现在通行时间是25秒，那么通过的车小于12.5（也就是大于等于13辆），那么下次通行时间就减5秒，变为20秒
				if(set_EW_time<15)			 //但是减不能无限的减，最小通行时间是15秒
				{
					set_EW_time=15;
				}
			}
			flag2=0;

			sec_EW=set_EW_time;			//重赋东西方向的起始值
			sec_SN=set_EW_time+5;		//重赋南北方向的起始值
		}
	}
}
void time1(void) interrupt 3 	//定时中断子程序
{
	TH1=0X3C;							//重赋初值
	TL1=0XB0;							//12m晶振50ms//重赋初值
	countt1++;							//软件计数加1
	if(countt1==10)					   // 定时器中断次数=10时（即0.5秒）
	{	   
		if(flag3==1)
	    {
			Yellow_SN=0;				//南北黄灯灭
			Yellow_EW=0;				//东西黄灯灭   
		}	
	}                                                                                                    
	if(countt1==20)	                  	// 定时器中断次数=20时（即1秒时）
	{	    
		count2++;
		countt1=0;						//清零计数器
		BUZZ=1;
		if(flag3==1)
		{	
			Yellow_SN=1;					//南北黄灯亮
			Yellow_EW=1;			 
		} 	//东西黄灯亮
	}
}


//外部中断0
void int0(void) interrupt 0 using 1	   //只允许东西通行
{
	TR0=0;								//关定时器0
	TR1=1;flag3=0;								//关定时器1
	P2=0x00;							//灭显示
	Green_EW=1;							//东西方向置绿灯
	Red_SN=1;							//南北方向为红灯
	sec_EW=00;							//四个方向的时间都为00
	sec_SN=00;	
}

//外部中断1
void int1(void) interrupt 2 using 1	  	 //只允许南北通行 
{
	TR0=0;								//关定时器0
	TR1=1;flag3=0;							   //关定时器1
	P2=0x00;							//灭显示
	Green_SN=1;							//置南北方向为绿灯
	Red_EW=1;							//东西方向为红灯
	sec_SN=00;							//四个方向的时间都为00
	sec_EW=00;
}
void logo()//开机的Logo  "- - - -"
{ 
	for(n=0;n<50;n++)	//循环显示----50次
   	{
	    P0=0x40;  //送形“-”
	    P1=0xfe;	//第一位显示
		delay(1);	//延时
	    P1=0xfd;	//第二位显示
		delay(1);	//延时
		P1=0Xfb;	//第三位显示
		delay(1);	//延时
		P1=0Xf7;	//第四位显示
		delay(1);	//延时
	    P1 = 0xff;	//灭显示
	}
}

void delay(int ms)		//延时子程序
{
	uint j,k;
	for(j=0;j<ms;j++)			//延时ms
	   for(k=0;k<124;k++);		//大约1毫秒的延时
}