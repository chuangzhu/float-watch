/*
 * PW_1_1.h
 *
 * Created: 2017/10/4 10:18:12
 *  Author: geneLocated
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "F_CPU.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HAL_USART.h"
#include "HAL_TWI_MST.h"
#include "HAL_ADC.h"
#include "HAL_TIMER.h"
#include "DEV_ADXL345.h"
#include "APP_Clock.h"
#include "APP_HeartRate.h"
#include "APP_Display.h"

#define set(Reg, Bit)	Reg|=(1<<Bit)	//置位Reg寄存器的Bit位
#define clr(Reg, Bit)	Reg&=~(1<<Bit)	//清零Reg寄存器的Bit位
#define not(Reg, Bit)	Reg^=(1<<Bit)	//取反Reg寄存器的Bit位

#define INT0pin 2
#define INT1pin 3

#define UP_HR()	{\
	Heart_Count();\
	USART_Print(HV);\
	USART_SendByte('\t');\
	USART_Print(HR*10);\
	USART_SendByte('\t');\
	USART_SendLine();}\

#define UP_AC()	{\
	for(unsigned char i=0; i<3; i++){\
		USART_Print(aC[i]);\
		USART_SendByte('\t');}\
		USART_SendLine();}\

#endif /* MAIN_H_ */