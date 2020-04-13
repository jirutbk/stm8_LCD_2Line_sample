#include "delay.h"

void ClockInit(void) 
{  
  //init clock
  CLK_DeInit(); // registers are reset 
  CLK_HSICmd (ENABLE); // internal high-speed clock enable 
  CLK_HSIPrescalerConfig (CLK_PRESCALER_HSIDIV8); // internal divide-2M 
}	


void delay_us(void) 
{  
    asm("nop"); //asm("nop")100ns 
    //asm("nop"); 
    //asm("nop"); 
    //asm("nop"); 
} 

void delay_us_n(unsigned int time) 
{      
    unsigned int i; 
    while(time--)   
    for(i=2;i>0;i--) 
    delay_us();
} 

void delay_ms(unsigned int time) 
{ 
    unsigned int i; 
    while(time--)   
    for(i=100;i>0;i--) //ค่าเดิม 900
    delay_us();

} 
