#include "pbdata.h"


int EC_data;

void delay80ms()   
{
    unsigned char a,b,c;
    for(c=165;c>0;c--)
        for(b=233;b>0;b--)
            for(a=10;a>0;a--);
    _nop_();  
}

void add485Data()
{
	IE2=0;
	RE_DE=1;                   //����Ϊ����ģʽ
	flay485=0;            
	
	Uart3SendByte(0x04);// delay10us();      //���͵�ַ
	Uart3SendByte(0x03);// delay10us();
	Uart3SendByte(0x00);// delay10us();
	Uart3SendByte(0x00);// delay10us();
	Uart3SendByte(0x00);// delay10us();
	Uart3SendByte(0x01);// delay10us();
	Uart3SendByte(0x84);// delay10us();
	Uart3SendByte(0x5f);// delay10us();
	
  IE2=0x08;             //����3�ж�ʹ�� 
	RE_DE=0;            //����Ϊ����ģʽ
  delay80ms();delay80ms();delay80ms();delay80ms();delay80ms();delay80ms();
			
	  EC_data=(ReceData[3]<<8)+ReceData[4];
	
//  RE_DE=1;
}

