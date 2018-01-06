/*
 * HAL_TWI_MST.h
 * TWI/IIC/I2C主机库
 * 此库只适用于Atmega48/88/168/328单片机
 * 若应用于其他型号一些寄存器的值需要修改
 * Modified: 2017/10/3
 * Author : geneLocated
 */ 

#include "HAL_TWI_MST.h"

//等待TWINT置位，它会在START/STOP信号发送完成或接收到从机ACK信号时置位
#define	TWI_WaitAck()	while(!(TWCR & _BV(TWINT)))

//接收ACK信号
#define	TWI_RecvAck()	({TWI_WaitAck();	(TW_STATUS);})
//等待从机发送ACK

//发送START信号
void TWI_Start(void)	{PORTC |= (_BV(SDApin)|_BV(SCLpin));	TWCR = (_BV(TWINT)|_BV(TWSTA)|_BV(TWEN));	TWI_WaitAck();}
//TWI接口启用内部上拉电阻	//发送START信号	//等待开始信号发送结束

//发送一个字节，自带接收ACK
#define	TWI_SendByte(data)	({TWDR = data;	TWCR = (_BV(TWINT)|_BV(TWEN));	(TWI_RecvAck());})

//接收一个字节
#define	TWI_RecvByte()	({TWCR = _BV(TWINT)|_BV(TWEA)|_BV(TWEN);	TWI_WaitAck();	(TWDR);})

//发送ACK信号
#define	TWI_SendAck()	TWCR |= _BV(TWEA)

//发送NACK信号
#define	TWI_SendNoAck()	{TWCR &= ~(_BV(TWEA));	TWI_WaitAck();}

//发送STOP信号
#define	TWI_Stop()	TWCR = (_BV(TWINT)|_BV(TWSTO)|_BV(TWEN))



/*以下为可调用的函数*/

void TWI_Init(void)
{
	TWBR = TWBR_Init;	//设置TWI波特率
}

void TWI_Write(unsigned char SlaveAddress, unsigned char RegisterAddress, unsigned char data)
{
	unsigned char dataArray[1]={data};
	TWI_MultiWrite(SlaveAddress, RegisterAddress, dataArray, 1);
	/*	以下为旧版内容
	TWI_Start();	//发送START信号
	TWI_SendByte(SlaveAddress|TW_WRITE);	//指定从机地址，方向写
	TWI_SendByte(RegisterAddress);	//发送数据地址
	TWI_SendByte(data);	//写入数据
	TWI_Stop();
	*/
}

void TWI_MultiWrite(unsigned char SlaveAddress, unsigned char RegisterAddress, unsigned char data[], unsigned char leng)
{
	TWI_Start();	//发送START信号
	TWI_SendByte(SlaveAddress|TW_WRITE);	//指定从机地址，方向写
	TWI_SendByte(RegisterAddress);	//发送数据地址
	for(unsigned char i=0; i<leng; i++) TWI_SendByte(data[i]);	//写入数据
	TWI_Stop();
}

unsigned char TWI_Query(unsigned char SlaveAddress, unsigned char RegisterAddress)
{
	//查询从机，要求其返回指定内寄存器的值
	unsigned char ResultArray[1];
	TWI_MultiQuery(SlaveAddress, RegisterAddress, ResultArray, 1);
	return ResultArray[0];
	/*	以下为旧版内容
	unsigned char Result;
	TWI_Start();	//发送START信号
	TWI_SendByte(SlaveAddress|TW_WRITE);	//指定从机地址，方向写
	TWI_SendByte(RegisterAddress);	//发送数据地址
	TWI_Start();	//发送RESTART信号
	TWI_SendByte(SlaveAddress|TW_READ);	//指定从机地址，方向读
	Result=TWI_RecvByte();	//读出返回的结果
	TWI_SendNoAck();	//发送NACK信号
	TWI_Stop();	//发送STOP信号
	return Result;
	*/
}

void TWI_MultiQuery(unsigned char SlaveAddress, unsigned char RegisterAddress, unsigned char Result[], unsigned char leng)
{
	TWI_Start();	//发送START信号
	TWI_SendByte(SlaveAddress|TW_WRITE);	//指定从机地址，方向写
	TWI_SendByte(RegisterAddress);	//发送数据地址
	TWI_Start();	//发送RESTART信号
	TWI_SendByte(SlaveAddress|TW_READ);	//指定从机地址，方向读
	for(unsigned char i=0; i<(leng-1); i++)
	{
		Result[i]=TWI_RecvByte();	//读出返回的结果
		TWI_SendAck();	//发送ACK信号
	}
	Result[(leng-1)]=TWI_RecvByte();	//读出返回的结果
	TWI_SendNoAck();	//发送NACK信号
	TWI_Stop();	//发送STOP信号
}
