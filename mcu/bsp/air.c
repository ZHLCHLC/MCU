#include "pbdata.h"

typedef unsigned char u8;
typedef unsigned int u16;


u8  U8FLAG,k;
u8  U8count,U8temp;
u8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
u8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
u8  U8comdata;


int temp,humidity;


void delay10us()   
{
    unsigned char a,b;
    for(b=21;b>0;b--)
        for(a=1;a>0;a--);
}

void delay18ms() 
{
    unsigned char a,b,c;
    for(c=148;c>0;c--)
        for(b=122;b>0;b--)
            for(a=4;a>0;a--);
}

	
void  COM(void)
      {
     
	        u8 i;
          
       for(i=0;i<8;i++)	   
	    {
		
	   	    U8FLAG=2;	
	   	while((!P2_0)&&U8FLAG++);
				delay10us();
				delay10us();
				delay10us();
	  		U8temp=0;
	     if(P2_0)U8temp=1;
		    U8FLAG=2;
		 while((P2_0)&&U8FLAG++);
	   	//��ʱ������forѭ��		  
	   	 if(U8FLAG==1)break;
	   	//�ж�����λ��0����1	 
	   	   
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;        //0
	     }//rof
	   
	}


void RH()
{
	  //��������18ms 
       P2_0=0;
	delay18ms() ;
	   P2_0=1;
	 //������������������ ������ʱ20us
	    delay10us();
	delay10us();
	delay10us();
	delay10us();
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
	   P2_0=1;
	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	   if(!P2_0)		 //T !	  
	   {
			 U8FLAG=2;
		 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
			 while((!P2_0)&&U8FLAG++);
			 U8FLAG=2;
		 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
			 while((P2_0)&&U8FLAG++);
		 //���ݽ���״̬		 
			 COM();
			 U8RH_data_H_temp=U8comdata;
			 COM();
			 U8RH_data_L_temp=U8comdata;
			 COM();
			 U8T_data_H_temp=U8comdata;
			 COM();
			 U8T_data_L_temp=U8comdata;
			 COM();
			 U8checkdata_temp=U8comdata;
			 P2_0=1;
		 //����У�� 
		 
			 U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
			 if(U8temp==U8checkdata_temp)
			 {
					U8RH_data_H=U8RH_data_H_temp;
					U8RH_data_L=U8RH_data_L_temp;
					U8T_data_H=U8T_data_H_temp;
					U8T_data_L=U8T_data_L_temp;
					U8checkdata=U8checkdata_temp;
			 }//fi
	   }//fi 
}

void count_H_T()
{
	RH();
	humidity=U8RH_data_H*256+(U8RH_data_L>>4)*16+(U8RH_data_L&0x0f);         //ʪ��
	temp=U8T_data_H*256+(U8T_data_L>>4)*16+(U8T_data_L&0x0f);               //�¶�
}