/*
 * DEV_ADXL345.c
 * 适用于ADXL345加速度传感器
 * 此库需架构于HAL_TWI_MST.h之上使用
 * Modified: 2017/10/3
 * Author : geneLocated
 */ 

#include "DEV_ADXL345.h"

signed int aC[3];	//此处定义变量

void ADXL345_Init(void)
{
	ADXL_Write(0x31,0x0B);	//DATA_FORMAT	禁用自测，中断高电平有效，全分辨率，右对齐，范围+-16g
	ADXL_Write(0x2C,0x08);	//BW_RATE	输出速率25Hz，带宽12.5Hz
	ADXL_Write(0x2D,0x08);	//POWER_CTL	禁用自动休眠，开启测量模式
	ADXL_Write(0x2E,0x80);	//INT_ENABLE	启用DATA_READY中断
	ADXL_Write(0x1E,0x00);	//OFSX	X轴不进行偏移校准
	ADXL_Write(0x1F,0x00);	//OFSY	Y轴不进行偏移校准
	ADXL_Write(0x20,0x00);	//OFSZ	Z轴不进行偏移校准
	//ADXL_Write(0x20,0x05);	//OFSZ	Z轴进行78mg偏移校准
}

void ADXL345_GetData(void)
{
	unsigned char aData[6];	//储存DATAX0、DATAX1、DATAY0、DATAY1、DATAZ0和DATAZ1的数据
	ADXL_MultiQuery(0x32, aData, 6);	//从DATAX0连续读至DATAZ1储存在aData[]中
	union		//将TWI读出的字节拼接int的盒子
	{
		unsigned char oriData[2];	//原数据
		signed int conData;	//转换后的数据
	} patch ;
	for(unsigned char i=0; i<3; i++)
	{
		patch.oriData[0]=aData[2*i];
		patch.oriData[1]=aData[2*i+1];
		aC[i]=patch.conData * OUTratio;
	}
}
