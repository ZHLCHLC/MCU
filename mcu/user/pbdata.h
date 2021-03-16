#ifndef __pbdata_H__
#define __pbdata_H__


#include  "STC8.h"
#include <intrins.h>
#include "air.h"
#include "guangzhao.h"
#include <stdio.h>
#include "timer.h"
#include "uart.h"
#include "RS485.h"
#include "adc.h"

sbit  P2_0  = P1^6;  //air
sbit SCL2=P1^2;      //IIC时钟引脚定义 guangzhao
sbit SDA2=P1^3;      //IIC数据引脚定义 guangzhao
sbit RE_DE=P0^2;    //RS485

#endif