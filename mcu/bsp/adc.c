#include "pbdata.h"


int PH_date1;
int PH_date0;

void init_adc()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	P1M0=0x00;
	P1M1=0x01;
	ADCCFG=0x0f;
	ADC_CONTR=0x80;
}

char get_adc(char ch)	//chs为模拟输入通道选择
{
  int PH_dat=0;
	ADC_CONTR = ADC_POWER | ADC_START | ch ;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while(!(ADC_CONTR&0x20));
	ADC_CONTR&=~0x20;
	PH_dat=ADC_RES;
	return PH_dat;
}

void read_adc()
{
	PH_date0=get_adc(0x07);
	PH_date1=(PH_date0*5*1000)/256;
}