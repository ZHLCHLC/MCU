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
	   	//超时则跳出for循环		  
	   	 if(U8FLAG==1)break;
	   	//判断数据位是0还是1	 
	   	   
		// 如果高电平高过预定0高电平值则数据位为 1 
	   	 
		   U8comdata<<=1;
	   	   U8comdata|=U8temp;        //0
	     }//rof
	   
	}


void RH()
{
	  //主机拉低18ms 
       P2_0=0;
	delay18ms() ;
	   P2_0=1;
	 //总线由上拉电阻拉高 主机延时20us
	    delay10us();
	delay10us();
	delay10us();
	delay10us();
	 //主机设为输入 判断从机响应信号 
	   P2_0=1;
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	   if(!P2_0)		 //T !	  
	   {
			 U8FLAG=2;
		 //判断从机是否发出 80us 的低电平响应信号是否结束	 
			 while((!P2_0)&&U8FLAG++);
			 U8FLAG=2;
		 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
			 while((P2_0)&&U8FLAG++);
		 //数据接收状态		 
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
		 //数据校验 
		 
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
	humidity=U8RH_data_H*256+(U8RH_data_L>>4)*16+(U8RH_data_L&0x0f);         //湿度
	temp=U8T_data_H*256+(U8T_data_L>>4)*16+(U8T_data_L&0x0f);               //温度
}