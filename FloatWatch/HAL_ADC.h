/*
 * HAL_ADC.h
 * 此库只适用于Atmega48/88/168/328单片机
 * 若应用于其他型号一些寄存器的值需要修改
 * Modified: 2017/10/3
 * Author : geneLocated
 */ 

#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_

#include <avr/io.h>

void ADC_Init(void);
unsigned int ADConvert(unsigned char Channel);

#endif
