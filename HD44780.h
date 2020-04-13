#ifndef __HD44780_H__
#define __HD44780_H__

void InitLcd(GPIO_TypeDef* port, GPIO_Pin_TypeDef rs, GPIO_Pin_TypeDef e, GPIO_Pin_TypeDef data);

void ClearLcd(int dummy);//dummy needs for Cosmic - WTF?

void Out(int line, char *str);
#endif
