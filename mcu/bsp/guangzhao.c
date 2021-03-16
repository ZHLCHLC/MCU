#include "pbdata.h"


typedef unsigned char u8;
typedef unsigned int u16;

u8 BUF2[8];                         //接收数据缓存区      	
int dis_data2;                       //变量
int L_temp2;

void Delay5us2()
{
     unsigned char a;
    for(a=27;a>0;a--);
}

void Delay5ms2()
{
  unsigned char a,b;
    for(b=202;b>0;b--)
        for(a=147;a>0;a--);
}



//起始信号
void BH1750_Start2()
{
    SDA2 = 1;                    //拉高数据线
    SCL2 = 1;                    //拉高时钟线
    Delay5us2();                 //延时
    SDA2 = 0;                    //产生下降沿
    Delay5us2();                 //延时
    SCL2 = 0;                    //拉低时钟线
}

//停止信号
void BH1750_Stop2()
{
    SDA2 = 0;                    //拉低数据线
    SCL2 = 1;                    //拉高时钟线
    Delay5us2();                 //延时
    SDA2 = 1;                    //产生上升沿
    Delay5us2();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK2(bit ack)
{
    SDA2 = ack;                  //写应答信号
    SCL2 = 1;                    //拉高时钟线
    Delay5us2();                 //延时
    SCL2 = 0;                    //拉低时钟线
    Delay5us2();                 //延时
}

//接收应答信号
bit BH1750_RecvACK2()
{
    SCL2 = 1;                    //拉高时钟线
    Delay5us2();                 //延时
    CY = SDA2;                   //读应答信号
    SCL2 = 0;                    //拉低时钟线
    Delay5us2();                 //延时
    return CY;
}

//向IIC总线发送一个字节数据
void BH1750_Senduchar2(char dat)
{
    u8 i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA2 = CY;               //送数据口
        SCL2 = 1;                //拉高时钟线
        Delay5us2();             //延时
        SCL2 = 0;                //拉低时钟线
        Delay5us2();             //延时
    }
    BH1750_RecvACK2();
}

//从IIC总线接收一个字节数据
char BH1750_Recvuchar2()
{
    u8 i;
    u8 dat = 0;
    SDA2 = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL2 = 1;                //拉高时钟线
        Delay5us2();             //延时
        dat |= SDA2;             //读数据               
        SCL2 = 0;                //拉低时钟线
        Delay5us2();             //延时
    }
    return dat;
}

void Single_Write_BH17502(char REG_Address)
{
    BH1750_Start2();                  //起始信号
    BH1750_Senduchar2(SlaveAddress);   //发送设备地址+写信号
    BH1750_Senduchar2(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    BH1750_Stop2();                   //发送停止信号
}

//连续读出BH1750内部数据
void Multiple_read_BH17502(void)
{   
	u8 i;	
	BH1750_Start2();                          //起始信号
	BH1750_Senduchar2(SlaveAddress+1);         //发送设备地址+读信号
	for (i=0; i<3; i++)                      //连续读取6个地址数据，存储中BUF
	{
	    BUF2[i] = BH1750_Recvuchar2();          //BUF[0]存储0x32地址中的数据
	    if (i == 3)
	       BH1750_SendACK2(1);                //最后一个数据需要回NOACK
	    else
	      BH1750_SendACK2(0);                //回应ACK
	}
	BH1750_Stop2();                          //停止信号
	Delay5ms2();
}

//初始化BH1750
void Init_BH17502()
{
	Single_Write_BH17502(0x01);  
	Single_Write_BH17502(0x10); 
}

void read_data_BH17502()
{
	Multiple_read_BH17502();       //连续读出数据，存储在BUF中
	dis_data2=BUF2[0];
	dis_data2=(dis_data2<<8)+BUF2[1];   //合成数据 
	L_temp2=(float)dis_data2/1.2;
}
