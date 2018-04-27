/*
 * FloatWatch.c
 *
 * Created: 2017/10/4 10:15:04
 * Author : geneLocated
 */ 

#include "main.h"

int main(void)
{
	DDRB=0x3F;	//0011 1111	(XTAL2:0, XTAL1:0, DIS7:1, DIS6:1, DIS5:1, DIS4:1, DIS3:1, DIS2:1)
	DDRD=0xD2;	//1101 0010	(DIS1:1, DIS0:1, PD5:0, TRIG:1, INT1:0, INT0:0, TXD:1, RXD:0)
	set(PORTD, INT0pin);
	//ADC_Init();
	ADXL345_Init();
	//USART_Begin();
	Clock_Init();
	TIMER0_Init();
	//comReg(0xFF);
	//set(PORTD, TRIGpin);
	sei();
    while(1)
    {
		//_delay_ms(10);
    }
}

ISR(TIMER0_OVF_vect)
{
	TCNT0=TCNT0_Init;	//这句必须保留
	{
		ADXL345_GetData();
		if(aZ<-1600)
			disStatus=0;	//允许一个周期开始显示
		if(aZ<350)
			displayTime();
		if(!(PIND & (1<<INT0pin)))
		{
			hour=12;
			minute=0;
			second=0;
		}
	}
}

