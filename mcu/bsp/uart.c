#include "pbdata.h"

typedef unsigned char u8;
typedef unsigned int u16;

char receive_1;
char receive_2;

volatile char ReceData[12];
volatile char flay485;

void UartInit1()   //����һ
{
	SCON = 0x50;       //REN=1�����н���״̬�����ڹ���ģʽ2     	   
	TMOD= 0x20;         //��ʱ��������ʽ2       8λ �Զ���װ�ض�ʱ��  ʵ�ֲ����� 
	AUXR=0X40;		 //����1Tģʽ
//	TL1 = 0xfd;	//���ò�����Ϊ115200
//	TH1 = 0xfd;
		TL1 = 0xdc;	//���ò�����Ϊ9600
	  TH1 = 0xdc;
	
	TR1  = 1;        //������ʱ��1                                                                      
	EA   = 1;        // �����ж� 
  ES=1;	
}	

void UartInit2()   //����2
{
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR|= 0x14;		//��ʱ��2ʱ��ΪFosc,��1T,������ʱ��2
//	T2L = 0xE8;		//�趨��ʱ��ֵ
//	T2H = 0xFF;		//�趨��ʱ��ֵ
	
	T2L = 0xe0;	//���ò�����Ϊ9600
	T2H = 0xfe; 
	
	IE2=0x01;           //����2�ж�ʹ�� 
	EA=1;
}

void UartInit3()		//9600bps@11.0592MHz
{
	S3CON = 0x50;		//8λ����,�ɱ䲨����
	T4T3M = 0x0a;		//��ʱ��3ʱ��ΪFosc,��1T
	T3L = 0xE0;		//�趨��ʱ��ֵ
	T3H = 0xFE;		//�趨��ʱ��ֵ  9600
//	T4T3M |= 0x08;		//������ʱ��3
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



//����1�����ַ���
void Uart1SendStr(unsigned char *str)
{
	while(*str!='\0')
	{
		Uart1SendByte(*str++);
		
	}
}

void Uart2SendByte(char dat)	  // ���Ͷ�(���͵����ַ�)
{
	S2BUF = dat;		          // ���ַ����봮��2�ķ��ͻ���Ĵ���
	while(!(S2CON&S2TI));	      // �жϷ����Ƿ������S2CON.bit2 = 0�������� 1�����ͽ���
	S2CON &= ~S2TI;			      // �ֶ������־λ����S2CON.bit2 = 0
}

//void Uart2SendStr(char *str)	  // ͨ�����÷����ַ������������ַ�����
//{
//	while(*str)
//	{
//		Uart2SendByte(*str);
//		str++;
//	}
//}

void Uart3SendByte(char dat)	  // ���Ͷ�(���͵����ַ�)
{
	S3BUF = dat;		          // ���ַ����봮��2�ķ��ͻ���Ĵ���
	while(!(S3CON&S3TI));	   // �жϷ����Ƿ������S2CON.bit2 = 0�������� 1�����ͽ���
	S3CON &= ~S3TI;			
	// �ֶ������־λ����S2CON.bit2 = 0
}



void Usart1() interrupt 4   using 1                 //����1�ж�
{
		receive_1=SBUF;//��ȥ���յ�������
		RI = 0;//��������жϱ�־λ
	  SBUF=receive_1;    //�����յ������ݷ��뵽���ͼĴ���
		while(!TI);			 //�ȴ������������
	  TI=0;
	
  						 //���������ɱ�־λ
//	S2BUF = receive_2;
//	while(!(S2CON&S2TI));	      //�ȴ������������
//  S2CON&= ~S2TI;            //���������ɱ�־λ
}


void Usart2() interrupt 8 using 2       //���ڶ��ж�
{
	receive_2 = S2BUF; 
	S2CON &= ~S2RI;
	S2BUF = receive_2;
  while(!(S2CON&S2TI));	      //�ȴ������������
  S2CON&= ~S2TI;            //���������ɱ�־λ
	
//	
//		SBUF=receive_1;    //�����յ������ݷ��뵽���ͼĴ���
//		while(!TI);			 //�ȴ������������
//	  TI=0;	
}

void Usart3() interrupt 17        //���ڶ��ж�
{
	S3CON &= ~S3RI;
	ReceData[flay485++] = S3BUF; 
	

	if(ReceData[0]!=0x04)
	{
		flay485=0;
	}
}
