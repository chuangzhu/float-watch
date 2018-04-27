/*
 * HAL_TIMER.h
 * TIMER硬件抽象库
 * 仅适用于ATmega48/88/168/328
 * 若应用于其他型号一些寄存器的值需要更改
 * 请在<F_CPU.h>中定义时钟频率及TIMER0溢出的周期
 * Created: 2017/10/5 22:43:01
 *  Author: geneLocated
 */ 

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "F_CPU.h"

#ifndef F_CPU	/*晶振的频率，单位Hz*/	/*请在<F_CPU.h>中定义*/
	# warning "F_CPU is not defined for HAL_TIMER.c"
	#define F_CPU 1000000
#endif

#ifndef TIMER0_Period /*TIMER0溢出的周期，单位us (Micro Sencond)*/	/*请在<F_CPU.h>中定义*/
	# warning "TIMER0_Period is not defined for HAL_TIMER.c"
	#define TIMER0_Period 50000
#endif

#ifndef TIMER2_Period /*TIMER2溢出的周期，单位us (Micro Sencond)*/	/*请在<F_CPU.h>中定义*/
	# warning "TIMER2_Period is not defined for HAL_TIMER.c"
	#define TIMER2_Period 50000
#endif

#define TxF0 (TIMER0_Period*(F_CPU/1000000))	/*TIMER0_Period 单位为微秒，除以1 000 000转换为国际单位*/
#define TxF2 (TIMER2_Period*(F_CPU/1000000))

#if TxF0<=256
	#define TCCR0B_Init	0x01	/*1分频*/
	#define TCNT0_Init	(256-TxF0)
#elif TxF0<=(256*8)
	#define TCCR0B_Init	0x02	/*8分频*/
	#define TCNT0_Init	(256-(TxF0/8))
#elif TxF0<=(256*64)
	#define TCCR0B_Init	0x03	/*64分频*/
	#define TCNT0_Init	(256-(TxF0/64))
#elif TxF0<=(256*256)
	#define TCCR0B_Init	0x04	/*256分频*/
	#define TCNT0_Init	(256-(TxF0/256))
#elif TxF0<=(256*1024)
	#define TCCR0B_Init	0x05	/*1024分频*/
	#define TCNT0_Init	(256-(TxF0/1024))
#else
	# warning "Time period is too long for TIMER0"
	#define TCCR0B_Init	0x05	/*1024分频*/
	#define TCNT0_Init	0
#endif

#if TxF2<=256
	#define TCCR2B_Init	0x01	/*1分频*/
	#define TCNT2_Init	(256-TxF2)
#elif TxF2<=(256*8)
	#define TCCR2B_Init	0x02	/*8分频*/
	#define TCNT2_Init	(256-(TxF2/8))
#elif TxF2<=(256*64)
	#define TCCR2B_Init	0x03	/*64分频*/
	#define TCNT2_Init	(256-(TxF2/64))
#elif TxF2<=(256*256)
	#define TCCR2B_Init	0x04	/*256分频*/
	#define TCNT2_Init	(256-(TxF2/256))
#elif TxF2<=(256*1024)
	#define TCCR2B_Init	0x05	/*1024分频*/
	#define TCNT2_Init	(256-(TxF2/1024))
#else
	# warning "Time period is too long for TIMER2"
	#define TCCR2B_Init	0x05	/*1024分频*/
	#define TCNT2_Init	0
#endif

#define TIMER0_Init()	{\
	TCCR0B=TCCR0B_Init;\
	TCNT0=TCNT0_Init;\
	TIMSK0|=(1<<TOIE0);}

#define TIMER2_Init()	{\
	TCCR2B=TCCR2B_Init;\
	TCNT2=TCNT2_Init;\
	TIMSK2|=(1<<TOIE2);}

#endif /* HAL_TIMER_H_ */

/* 写中断函数时应该这么写：
	ISR(TIMER0_OVF_vect)
	{
		TCNT0=TCNT0_Init;	//这句一定要加上！
		{
			//要写的函数内容
		}
	}
 */