/*
 * HAL_USART.h
 * 此库只适用于Atmega48/88/168/328单片机
 * 若应用于其他型号一些寄存器的值需要修改
 * Modified: 2017/10/3
 * Author : geneLocated
 */ 

#ifndef _HAL_USART_H_
#define _HAL_USART_H_

#include <avr/io.h>

/* 请在<F_CPU.h>中定义时钟频率和波特率*/

void USART_Begin(void);	//开始USART通讯
void USART_SendByte(unsigned char x);	//发送一个字节
void USART_SendData(const char *data, unsigned int leng);	//向USART发送字符串（不换行）
void USART_Print(int data);	//向USART以ASCII形式发送int
void USART_SendLine(void);	//向USART发送回车换行

#endif
