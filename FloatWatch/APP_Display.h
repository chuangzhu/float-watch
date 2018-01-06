/*
 * APP_Display.h
 *
 * Created: 2017/10/14 7:21:48
 *  Author: geneLocated
 */ 


#ifndef APP_DISPLAY_H_
#define APP_DISPLAY_H_

#include <avr/io.h>
#include "APP_Clock.h"

void comReg(unsigned char Data);
/*	#define comReg(Data)	{PORTB|=(Data>>2);PORTB&=((Data>>2)+(0xFF<<6));PORTD|=(Data<<6);PORTD&=((Data<<6)+(0xFF>>2));}	*/

void displayTime(void);

extern unsigned char disStatus;

#endif /* APP_DISPLAY_H_ */