/*
 * APP_HeartRate.c
 * 当前还没有用到动态阈值，正在改进
 * Author: geneLocated
 */ 

#include "APP_HeartRate.h"

/*#define PulseLStd	620	//2480
#define PulseHStd	720	//2880*/
#define PulseLStd	2480
#define PulseHStd	2880
unsigned int HV;	//Heart Value
unsigned char HT = 0;	//Heartbeat Times
unsigned int HR;	//Heart Rate

//#define ConReq() ((preHV<PulseLStd)&&(HV>PulseLStd)&&(HV<PulseHStd))
void Heart_Count(void)	//想办法短时间间隔不断执行
{
	static unsigned int oldHV;	//Last Heart Valve
	//HV = ADConvert(7);
	{	/*使曲线变光滑*/
		static unsigned int priHV[4]={0};	//Primary Heart Value
		for (unsigned char i=0; i<3; i++)	//将数组左移一个数据，丢掉旧的priHV[0]
			priHV[i]=priHV[i+1];
		priHV[3] = ADConvert(7);
		unsigned int SpriHV=0;
		for (unsigned char i=0; i<4; i++)	//数组所有项加在一起
			SpriHV += priHV[i];
		//HV=SpriHV/4;
		HV=SpriHV;
	}
	if((oldHV<PulseLStd)&&(HV>PulseLStd)&&(HV<PulseHStd))
		HT++;
	oldHV = HV;
}

void Heart_Rate(void)	//想办法每秒执行一次
{
	static unsigned char dHT[20]={0};
	for (unsigned char i=0; i<19; i++)	//将数组左移一个数据，丢掉旧的dHT[0]
	dHT[i]=dHT[i+1];
	dHT[19]=HT;
	HT=0;
	unsigned int sHT=0;
	for (unsigned char i=0; i<20; i++)	//数组所有项加在一起
	sHT += dHT[i];
	HR = sHT*3;
}
