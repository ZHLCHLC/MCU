#include "pbdata.h"


typedef unsigned char u8;
typedef unsigned int u16;

u8 BUF2[8];                         //�������ݻ�����      	
int dis_data2;                       //����
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



//��ʼ�ź�
void BH1750_Start2()
{
    SDA2 = 1;                    //����������
    SCL2 = 1;                    //����ʱ����
    Delay5us2();                 //��ʱ
    SDA2 = 0;                    //�����½���
    Delay5us2();                 //��ʱ
    SCL2 = 0;                    //����ʱ����
}

//ֹͣ�ź�
void BH1750_Stop2()
{
    SDA2 = 0;                    //����������
    SCL2 = 1;                    //����ʱ����
    Delay5us2();                 //��ʱ
    SDA2 = 1;                    //����������
    Delay5us2();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK2(bit ack)
{
    SDA2 = ack;                  //дӦ���ź�
    SCL2 = 1;                    //����ʱ����
    Delay5us2();                 //��ʱ
    SCL2 = 0;                    //����ʱ����
    Delay5us2();                 //��ʱ
}

//����Ӧ���ź�
bit BH1750_RecvACK2()
{
    SCL2 = 1;                    //����ʱ����
    Delay5us2();                 //��ʱ
    CY = SDA2;                   //��Ӧ���ź�
    SCL2 = 0;                    //����ʱ����
    Delay5us2();                 //��ʱ
    return CY;
}

//��IIC���߷���һ���ֽ�����
void BH1750_Senduchar2(char dat)
{
    u8 i;
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA2 = CY;               //�����ݿ�
        SCL2 = 1;                //����ʱ����
        Delay5us2();             //��ʱ
        SCL2 = 0;                //����ʱ����
        Delay5us2();             //��ʱ
    }
    BH1750_RecvACK2();
}

//��IIC���߽���һ���ֽ�����
char BH1750_Recvuchar2()
{
    u8 i;
    u8 dat = 0;
    SDA2 = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL2 = 1;                //����ʱ����
        Delay5us2();             //��ʱ
        dat |= SDA2;             //������               
        SCL2 = 0;                //����ʱ����
        Delay5us2();             //��ʱ
    }
    return dat;
}

void Single_Write_BH17502(char REG_Address)
{
    BH1750_Start2();                  //��ʼ�ź�
    BH1750_Senduchar2(SlaveAddress);   //�����豸��ַ+д�ź�
    BH1750_Senduchar2(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
    BH1750_Stop2();                   //����ֹͣ�ź�
}

//��������BH1750�ڲ�����
void Multiple_read_BH17502(void)
{   
	u8 i;	
	BH1750_Start2();                          //��ʼ�ź�
	BH1750_Senduchar2(SlaveAddress+1);         //�����豸��ַ+���ź�
	for (i=0; i<3; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
	{
	    BUF2[i] = BH1750_Recvuchar2();          //BUF[0]�洢0x32��ַ�е�����
	    if (i == 3)
	       BH1750_SendACK2(1);                //���һ��������Ҫ��NOACK
	    else
	      BH1750_SendACK2(0);                //��ӦACK
	}
	BH1750_Stop2();                          //ֹͣ�ź�
	Delay5ms2();
}

//��ʼ��BH1750
void Init_BH17502()
{
	Single_Write_BH17502(0x01);  
	Single_Write_BH17502(0x10); 
}

void read_data_BH17502()
{
	Multiple_read_BH17502();       //�����������ݣ��洢��BUF��
	dis_data2=BUF2[0];
	dis_data2=(dis_data2<<8)+BUF2[1];   //�ϳ����� 
	L_temp2=(float)dis_data2/1.2;
}
