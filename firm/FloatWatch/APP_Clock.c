/*
 * APP_Clock.c
 * 时间应用库
 * 占用TIMER1
 * 此库只适用于Atmega48/88/168单片机
 * 若应用于其他型号一些寄存器的值需要修改
 * Created: 2017/10/3 16:34:30
 *  Author: geneLocated
 */ 

#include "F_CPU.h"	/* 请在<F_CPU.h>中定义时钟频率*/
#include "APP_HeartRate.h"
#include "APP_Clock.h"

#ifndef F_CPU
# warning "F_CPU is not defined for APP_Clock.c"
#define F_CPU 8000000
#endif
#define	TCNT1_Init	(0xFFFF-(F_CPU/256))

unsigned char time[3] = {0, 30, 17};

void Clock_Init(void)
{
	//定时器1
	TCCR1B = (1<<CS12);	//256分频
	TCNT1 = TCNT1_Init;	//赋初始值，使1s后触发中断
	TIMSK1 |= (1<<TOIE1);	//开启定时器溢出中断
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = TCNT1_Init;	//TCNT1赋初始值
	unsigned char* t = time;	//定义指针t指向数组time
	(*t)++;	//秒加1
	if(*t==60){	//秒达到60
		*t=0;	//秒清零
		(*(t+1))++;	//分加一
	}
	t++;	//指向分
	if(*t==60){	//分达到60
		*t=0;	//分清零
		(*(t+1))++;	//分加一
	}
	t++;	//指向时
	if(*t==24){	//时达到24
		*t=0;	//时清零
	}
	Heart_Rate();
}
