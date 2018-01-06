/*
 * APP_Display.c
 *
 * Created: 2017/10/14 7:21:35
 *  Author: geneLocated
 */ 

#include "APP_Display.h"

unsigned char disStatus=0;	//清零后允许一个周期显示，置位后表示已显示完一个周期

const unsigned char fontData[11][5]=
{	//字体数据，第七位在最上方
	{0x7E, 0xFF, 0x81, 0xFF, 0x7E},	//0
	{0x00, 0x40, 0xFF, 0xFF, 0x00},	//1
	{0x71, 0xF1, 0x87, 0xFD, 0x79},	//2
	{0x63, 0xC3, 0x91, 0xFF, 0x6E},	//3
	{0x38, 0x78, 0xC8, 0xFF, 0xFF},	//4
	{0xE6, 0xE7, 0xA1, 0xBF, 0x9E},	//5
	{0x7E, 0xFF, 0x91, 0x9F, 0x4E},	//6
	{0xE0, 0xC7, 0x9F, 0xF8, 0xE0},	//7
	{0x6E, 0xFF, 0xA1, 0xFF, 0x6E},	//8
	{0x70, 0xF9, 0x8B, 0xFE, 0x7C},	//9
	{0x00, 0x42, 0x66, 0x42, 0x00}	//:
};

void comReg(unsigned char Data)
{
	PORTB|=(Data>>2);
	PORTB&=((Data>>2)+(0xFF<<6));
	PORTD|=(Data<<6);
	PORTD&=((Data<<6)+(0xFF>>2));
}

void displayTime(void)	//显示时间数字下一帧
{
	if(disStatus==0)
	{
		static unsigned char charNum=0;	//时间共有五个字符，之间有四个大的空隙
		static unsigned char colNum=0;	//一个字符有五帧，之间有4个空隙
		unsigned char charInside=11;
		switch(charNum)
		{
			case 0: charInside=hour/10; break;	//时十位
			case 2: charInside=hour%10; break;	//时个位
			case 4: charInside=10; break;	//冒号
			case 6: charInside=minute/10; break;	//分十位
			case 8: charInside=minute%10; break;	//分个位
			default: charInside=11; break;
		}
		if ((charInside!=11) && (colNum%2==0))
			comReg(fontData[charInside][colNum/2]);
		else
			comReg(0x00);
		
		colNum++;
		if(colNum>8)	//算上空隙共8个
		{
			colNum=0;
			charNum++;
		}
		if(charNum>12)
		{
			charNum=0;
			disStatus=1;
		}
	}
}