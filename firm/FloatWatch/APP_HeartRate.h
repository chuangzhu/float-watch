/*
 * APP_HeartRate.h
 *
 * Author: geneLocated
 */ 

#ifndef _APP_HEARTRATE_H_
#define _APP_HEARTRATE_H_

#include "HAL_ADC.h"

#define TRIGpin	4	//心率LED引脚
extern unsigned int HV;	//Heart Value
//extern unsigned char HT;	//Heartbeat Times
extern unsigned int HR;	//Heart Rate

#define Heart_GetValue() (ADConvert(7))
void Heart_Count(void);
void Heart_Rate(void);

#endif
