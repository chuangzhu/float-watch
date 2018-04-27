/*
 * APP_Clock.h
 * 时间应用库
 * 占用TIMER1
 * 此库只适用于Atmega48/88/168单片机
 * 若应用于其他型号一些寄存器的值需要修改
 * Created: 2017/10/3 16:35:17
 *  Author: geneLocated
 */ 


#ifndef APP_CLOCK_H_
#define APP_CLOCK_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/* 请在<F_CPU.h>中定义时钟频率和波特率*/

void Clock_Init(void);

extern unsigned char time[3];
#define	second	time[0]
#define	minute	time[1]
#define	hour	time[2]

#endif /* APP_CLOCK_H_ */