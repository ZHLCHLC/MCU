#include "pbdata.h"



void Timer0Init()		//1����@11.0592MHz
{
	/*��ʱ���жϳ�ʼ��*/
 	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xcd;		//���ö�ʱ��ֵ
	TH0 = 0xd4;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ 
  EA = 1;
  ET0 = 1;
	/*�ⲿ�жϳ�ʼ��*/
	IT0=1;//�����س�����ʽ���½��أ�
	EX0=1;//��INT0���ж�����	
	EA=1;//�����ж�	
	
}

void time_init()  interrupt 1
{
  static int i=0;
	TL0 = 0xCD;		//���ö�ʱ��ֵ
	TH0 = 0xD4;		//���ö�ʱ��ֵ         ��ʱ1����
	
	i++;
	if(i==1000)
	{
		//Uart1SendByte('B');
		Uart1SendStr("����ʪ��: ");
		Uart1SendByte(humidity/100+0x30);        //����ʪ��
		Uart1SendByte(humidity%100/10+0x30);
		Uart1SendByte('.'); 
		Uart1SendByte(humidity%100%10+0x30); 
		Uart1SendStr("	   "); 
		
        Uart1SendStr("�����¶�: ");
		Uart1SendByte(temp/100+0x30);        //�����¶�
		Uart1SendByte(temp%100/10+0x30);
		Uart1SendByte('.'); 
		Uart1SendByte(temp%100%10+0x30);	
		Uart1SendStr("	 ");
/*		
		Uart1SendByte('D');
		Uart1SendByte(EC_data/10000+0x30);        //ECֵ
		Uart1SendByte(EC_data%10000/1000+0x30);
		Uart1SendByte('.');
		Uart1SendByte(EC_data%10000%1000/100+0x30);
		Uart1SendByte(EC_data%10000%1000%100/10+0x30);
		Uart1SendByte(EC_data%10000%1000%100%10+0x30);
/*		
		Uart1SendByte('E');
		Uart1SendByte(PH_date1/100+0x30);        //PHֵ
		Uart1SendByte(PH_date1%100/10+0x30);
		Uart1SendByte('.'); 
		Uart1SendByte(PH_date1%100%10+0x30);	
*/		
		Uart1SendStr("����: ");
		Uart1SendByte(L_temp2/10000+0x30);        //���մ�����2
		Uart1SendByte(L_temp2%10000/1000+0x30);
		Uart1SendByte(L_temp2%10000%1000/100+0x30);
		Uart1SendByte(L_temp2%10000%1000%100/10+0x30);
		Uart1SendByte(L_temp2%10000%1000%100%10+0x30);
		Uart1SendStr("\r\n");
		Delay5ms2();
		i=0;
	}

}



