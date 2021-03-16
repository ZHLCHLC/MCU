#include "pbdata.h"

void main()
{
	UartInit1() ;   //串口1初始化
	UartInit2() ;   //串口2初始化
//	UartInit3();     //串口3初始化
	Timer0Init();     //定时器0初始化
//	init_adc();       //ad初始化
	Init_BH17502();   //初始化光照传感器2
	while(1)
	{
		count_H_T();       //读取空气温湿度
		read_data_BH17502(); //读取光照传感器2
		
	}
}
