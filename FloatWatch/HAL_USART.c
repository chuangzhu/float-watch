/*
 * HAL_USART.c
 * 此库只适用于Atmega48/88/168/328单片机
 * 若应用于其他型号一些寄存器的值需要修改
 * Modified: 2017/10/3
 * Author : geneLocated
 */ 
#include "F_CPU.h"	/* 请在<F_CPU.h>中定义时钟频率和波特率*/
#include "HAL_USART.h"

#ifndef F_CPU
# warning "F_CPU not defined for <HAL_USART.c>"
#define F_CPU 8000000
#endif

#ifndef baud
# warning "baud not defined for <HAL_USART.c>"
#define baud 9600
#endif

//开始USART通讯
void USART_Begin(void)
{
	UBRR0H=(F_CPU/16/baud-1)/256;
	UBRR0L=(F_CPU/16/baud-1)%256;
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);	//使能发送接收
	//UCSR0B|=(1<<RXCIE0);	//使能接收中断
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);	//8bit
}

//发送一个字节
void USART_SendByte(unsigned char x)
{
	while(!((UCSR0A)&(1<<UDRE0)));
	UDR0=x;
}

//向USART发送字符串（不换行）
void USART_SendData(const char *data, unsigned int leng)
{
	while(leng)
	{
		while(!((UCSR0A)&(1<<UDRE0)));
		UDR0=*data;
		data++;
		leng--;
	}
}

//向USART以ASCII形式发送int
void USART_Print(int data)
{
	if(data<0)
	{
		data=~data+1;
		USART_SendByte('-');	//负号
	}
	USART_SendByte(data/10000+48);	//万位
	USART_SendByte(data%10000/1000+48);	//千位
	USART_SendByte(data%1000/100+48);	//百位
	USART_SendByte(data%100/10+48);	//十位
	USART_SendByte(data%10+48);	//个位
}

//向USART发送回车换行
void USART_SendLine(void)
{
	USART_SendByte(0X0D);	//回车CR(\r)
	USART_SendByte(0X0A);	//换行LF(\n)
}
