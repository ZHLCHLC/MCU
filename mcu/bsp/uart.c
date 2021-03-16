#include "pbdata.h"

typedef unsigned char u8;
typedef unsigned int u16;

char receive_1;
char receive_2;

volatile char ReceData[12];
volatile char flay485;

void UartInit1()   //串口一
{
	SCON = 0x50;       //REN=1允许串行接受状态，串口工作模式2     	   
	TMOD= 0x20;         //定时器工作方式2       8位 自动重装载定时器  实现波特率 
	AUXR=0X40;		 //开启1T模式
//	TL1 = 0xfd;	//设置波特率为115200
//	TH1 = 0xfd;
		TL1 = 0xdc;	//设置波特率为9600
	  TH1 = 0xdc;
	
	TR1  = 1;        //开启定时器1                                                                      
	EA   = 1;        // 开总中断 
  ES=1;	
}	

void UartInit2()   //串口2
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR|= 0x14;		//定时器2时钟为Fosc,即1T,启动定时器2
//	T2L = 0xE8;		//设定定时初值
//	T2H = 0xFF;		//设定定时初值
	
	T2L = 0xe0;	//设置波特率为9600
	T2H = 0xfe; 
	
	IE2=0x01;           //串口2中断使能 
	EA=1;
}

void UartInit3()		//9600bps@11.0592MHz
{
	S3CON = 0x50;		//8位数据,可变波特率
	T4T3M = 0x0a;		//定时器3时钟为Fosc,即1T
	T3L = 0xE0;		//设定定时初值
	T3H = 0xFE;		//设定定时初值  9600
//	T4T3M |= 0x08;		//启动定时器3
	IE2 = 0x08;
  EA = 1;
}

void Uart1SendByte(char dat)
{
	SBUF = dat;
	RI=0;
	while(TI == 0);
	TI = 0;
}



//串口1发送字符串
void Uart1SendStr(unsigned char *str)
{
	while(*str!='\0')
	{
		Uart1SendByte(*str++);
		
	}
}

void Uart2SendByte(char dat)	  // 发送端(发送的是字符)
{
	S2BUF = dat;		          // 将字符送入串口2的发送缓冲寄存器
	while(!(S2CON&S2TI));	      // 判断发送是否结束：S2CON.bit2 = 0：发送中 1：发送结束
	S2CON &= ~S2TI;			      // 手动清零标志位，令S2CON.bit2 = 0
}

//void Uart2SendStr(char *str)	  // 通过调用发送字符函数来发送字符数组
//{
//	while(*str)
//	{
//		Uart2SendByte(*str);
//		str++;
//	}
//}

void Uart3SendByte(char dat)	  // 发送端(发送的是字符)
{
	S3BUF = dat;		          // 将字符送入串口2的发送缓冲寄存器
	while(!(S3CON&S3TI));	   // 判断发送是否结束：S2CON.bit2 = 0：发送中 1：发送结束
	S3CON &= ~S3TI;			
	// 手动清零标志位，令S2CON.bit2 = 0
}



void Usart1() interrupt 4   using 1                 //串口1中断
{
		receive_1=SBUF;//出去接收到的数据
		RI = 0;//清除接收中断标志位
	  SBUF=receive_1;    //将接收到的数据放入到发送寄存器
		while(!TI);			 //等待发送数据完成
	  TI=0;
	
  						 //清除发送完成标志位
//	S2BUF = receive_2;
//	while(!(S2CON&S2TI));	      //等待发送数据完成
//  S2CON&= ~S2TI;            //清除发送完成标志位
}


void Usart2() interrupt 8 using 2       //串口二中断
{
	receive_2 = S2BUF; 
	S2CON &= ~S2RI;
	S2BUF = receive_2;
  while(!(S2CON&S2TI));	      //等待发送数据完成
  S2CON&= ~S2TI;            //清除发送完成标志位
	
//	
//		SBUF=receive_1;    //将接收到的数据放入到发送寄存器
//		while(!TI);			 //等待发送数据完成
//	  TI=0;	
}

void Usart3() interrupt 17        //串口二中断
{
	S3CON &= ~S3RI;
	ReceData[flay485++] = S3BUF; 
	

	if(ReceData[0]!=0x04)
	{
		flay485=0;
	}
}
