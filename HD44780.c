#include "stm8s.h"
#include "HD44780.h"
#include "delay.h"
#include <assert.h>

static struct
{
	GPIO_TypeDef*    port;
	GPIO_Pin_TypeDef rs;
	GPIO_Pin_TypeDef e;
	GPIO_Pin_TypeDef data; 
} gLcd;

void WriteLowNibble(unsigned char cmd)
{
	unsigned char oldV = GPIO_ReadOutputData(gLcd.port);

	GPIO_Write(gLcd.port, (oldV & 0xF0) | (cmd & 0x0F));
	GPIO_WriteHigh(gLcd.port,gLcd.e);
	delay_ms(1);
	GPIO_WriteLow(gLcd.port,gLcd.e);
}

void WriteHighNibble(unsigned char cmd)
{
	unsigned char oldV = GPIO_ReadOutputData(gLcd.port);

	GPIO_Write(gLcd.port, (oldV & 0x0F) | ((cmd << 4) & 0xF0));
	GPIO_WriteHigh(gLcd.port,gLcd.e);
	delay_ms(1);
	GPIO_WriteLow(gLcd.port,gLcd.e);
}

void SendByte(unsigned char cmd)
{
	if (gLcd.data == GPIO_PIN_LNIB)
	{
		WriteLowNibble(cmd >> 4);
		WriteLowNibble(cmd);
	}
	else
	{
		WriteHighNibble(cmd >> 4);
		WriteHighNibble(cmd);
	}
}

void SendCommand(unsigned char cmd)
{
	GPIO_WriteLow(gLcd.port,gLcd.rs);

	SendByte(cmd);
	
	delay_us_n(60);
}

void SendData(unsigned char cmd)
{
	GPIO_WriteHigh(gLcd.port,gLcd.rs);

	SendByte(cmd);
	
	delay_us_n(60);
}

void ClearLcd(int dummy)
{
	SendCommand(0x1);
}

void SetLine(int line)
{
	if (line)
	{//1
		SendCommand(0xC0);
	}
	else
	{
		SendCommand(0x80);
	}
}

void Out(int line, char *str)
{
	SetLine(line);
	
	while(*str)
	{
		SendData(*str++);
	}
}

void InitLcd(GPIO_TypeDef* port, GPIO_Pin_TypeDef rs,GPIO_Pin_TypeDef e, GPIO_Pin_TypeDef data)
{
	assert((data == GPIO_PIN_LNIB) || (data == GPIO_PIN_HNIB));
	
	gLcd.port = port;
	gLcd.rs = rs;
	gLcd.e = e;
	gLcd.data = data;

	GPIO_DeInit(gLcd.port);
	GPIO_Init(gLcd.port, data | rs | e, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_WriteLow(gLcd.port, gLcd.e); 
	GPIO_WriteLow(gLcd.port, gLcd.rs);

	delay_ms(10);    //
	SendCommand(0x33);//
	SendCommand(0x2); //
	SendCommand(0x2C); //
	SendCommand(0x1); //
	SendCommand(0x6); //
}


