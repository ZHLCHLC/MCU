#include "pbdata.h"



void Timer0Init()		//1毫秒@11.0592MHz
{
	/*定时器中断初始化*/
 	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xcd;		//设置定时初值
	TH0 = 0xd4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时 
  EA = 1;
  ET0 = 1;
	/*外部中断初始化*/
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。	
	EA=1;//打开总中断	
	
}

void time_init()  interrupt 1
{
  static int i=0;
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值         定时1毫秒
	
	i++;
	if(i==1000)
	{
		//Uart1SendByte('B');
		Uart1SendStr("空气湿度: ");
		Uart1SendByte(humidity/100+0x30);        //空气湿度
		Uart1SendByte(humidity%100/10+0x30);
		Uart1SendByte('.'); 
		Uart1SendByte(humidity%100%10+0x30); 
		Uart1SendStr("	   "); 
		
        Uart1SendStr("空气温度: ");
		Uart1SendByte(temp/100+0x30);        //空气温度
		Uart1SendByte(temp%100/10+0x30);
		Uart1SendByte('.'); 
		Uart1SendByte(temp%100%10+0x30);	
		Uart1SendStr("	 ");
/*		
		Uart1SendByte('D');
		Uart1SendByte(EC_data/10000+0x30);        //EC值
		Uart1SendByte(EC_data%10000/1000+0x30);
		Uart1SendByte('.');
		Uart1SendByte(EC_data%10000%1000/100+0x30);
		Uart1SendByte(EC_data%10000%1000%100/10+0x30);
		Uart1SendByte(EC_data%10000%1000%100%10+0x30);
/*		
		Uart1SendByte('E');
		Uart1SendByte(PH_date1/100+0x30);        //PH值
		Uart1SendByte(PH_date1%100/10+0x30);
		Uart1SendByte('.'); 
		Uart1SendByte(PH_date1%100%10+0x30);	
*/		
		Uart1SendStr("光照: ");
		Uart1SendByte(L_temp2/10000+0x30);        //光照传感器2
		Uart1SendByte(L_temp2%10000/1000+0x30);
		Uart1SendByte(L_temp2%10000%1000/100+0x30);
		Uart1SendByte(L_temp2%10000%1000%100/10+0x30);
		Uart1SendByte(L_temp2%10000%1000%100%10+0x30);
		Uart1SendStr("\r\n");
		Delay5ms2();
		i=0;
	}

}



