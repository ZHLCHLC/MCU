#ifndef _guangzhao_H__
#define _guangzhao_H__

#define	SlaveAddress 0x46


extern int L_temp2;

//typedef unsigned char u8;
//typedef unsigned int u16;

//u8 BUF2[8];                         //接收数据缓存区      	
//u8 ge2,shi2,bai2,qian2,wan2;            //显示变量
//int dis_data2;                       //变量
//float temp2;



void Delay5us2();
void Delay5ms2();
void BH1750_Start2();
void BH1750_Stop2();	
void BH1750_SendACK2(bit ack);
bit BH1750_RecvACK2();
void BH1750_Senduchar2(char dat);
char BH1750_Recvuchar2();
void Single_Write_BH17502(char REG_Address);
void Multiple_read_BH17502(void);
void Init_BH17502();
void read_data_BH17502();



#endif