#ifndef  __adc_H__
#define  __adc_H__

extern int PH_date1;


void init_adc();
char get_adc(char ch);	//chs为模拟输入通道选择
void read_adc();



#endif