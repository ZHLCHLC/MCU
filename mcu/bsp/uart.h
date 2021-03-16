#ifndef _uart_H__
#define _uart_H__

extern volatile char ReceData[12];
extern volatile char flay485;


void UartInit1();
void UartInit2() ;
void UartInit3();
void Uart1SendByte(char dat);
void Uart2SendByte(char dat);
void Uart3SendByte(char dat);
void Uart1SendStr(unsigned char *str);
//void Uart1SendStr(char *str);
//void Uart2SendByte(char dat);
//void Uart2SendStr(char *str);


#endif