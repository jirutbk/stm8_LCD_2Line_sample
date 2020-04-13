#include "stm8s.h"
#include "HD44780.h"

int main(void) 
{
        //init clock
        //ClockInit(); // registers are reset         
  
	InitLcd(GPIOD, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_LNIB);

	Out(0, " Ruk love Mi ");
	Out(1, "easyelectronics.");

	while(1);
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}
#endif
