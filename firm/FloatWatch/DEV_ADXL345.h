/*
 * DEV_ADXL345.h
 * 适用于ADXL345加速度传感器
 * 此库需架构于HAL_TWI_MST.h之上使用
 * Modified: 2017/10/3
 * Author : geneLocated
 */ 

#ifndef _DEV_ADXL345_H_
#define _DEV_ADXL345_H_

#include "HAL_TWI_MST.h"

#define SLAVEaddr	(0x53<<1)	//ADXL345地址，如果ALT ADDRESS悬空它为(0x1D<<1)，如果接地它为(0x53<<1)
#define OUTratio 4	//全分辨率下XOUT,YOUT,ZOUT比例因子，(mg/LSB)

#define ADXL_Write(RegisterAddress, data)	TWI_Write(SLAVEaddr, RegisterAddress, data)
#define ADXL_Query(RegisterAddress)	TWI_Query(SLAVEaddr, RegisterAddress)
#define ADXL_MultiWrite(RegisterAddress, data, leng)	TWI_MultiWrite(SLAVEaddr, RegisterAddress, data, leng)
#define ADXL_MultiQuery(RegisterAddress, Result, leng)	TWI_MultiQuery(SLAVEaddr, RegisterAddress, Result, leng)

//全局变量储存换算后的加速度，单位mg
extern signed int aC[3];	//此处声明变量，外部定义
#define aX	aC[0]
#define aY	aC[1]
#define aZ	aC[2]

void ADXL345_Init(void);	//初始化传感器
void ADXL345_GetData(void);	//获取加速度数据，储存在aC中

#endif
