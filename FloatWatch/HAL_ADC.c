/*
 * HAL_ADC.c
 * 此库只适用于Atmega48/88/168/328单片机
 * 若应用于其他型号一些寄存器的值需要修改
 * Modified: 2017/10/3
 * Author : geneLocated
 */ 

#include "HAL_ADC.h"

void ADC_Init(void)	//ADC初始化
{
	ADCSRA = 0x00;	//禁用ADC
	ADMUX = 0x40;	//设置参考电压为AVCC，右对齐
	ADCSRA = 0x86;	//设置分频数为64，使能ADC
}

unsigned int ADConvert(unsigned char Channel)	//AD转换
{
	unsigned int CData;
	ADMUX = 0x40;	//清零
	ADMUX |= (Channel & 0x07);	//通道只有8个（三位）
	ADCSRA |= (1<<ADSC);	//启动AD转换
	while(ADCSRA & (1<<ADSC));	//等待转换结束
	CData = ADCL;	//获取低8位转换数据
	CData |= ((unsigned int)(ADCH & 0x03))<<8;	//获取高2位
	return CData;	//返回数据
}
