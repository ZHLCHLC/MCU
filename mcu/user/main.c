#include "pbdata.h"

void main()
{
	UartInit1() ;   //����1��ʼ��
	UartInit2() ;   //����2��ʼ��
//	UartInit3();     //����3��ʼ��
	Timer0Init();     //��ʱ��0��ʼ��
//	init_adc();       //ad��ʼ��
	Init_BH17502();   //��ʼ�����մ�����2
	while(1)
	{
		count_H_T();       //��ȡ������ʪ��
		read_data_BH17502(); //��ȡ���մ�����2
		
	}
}
