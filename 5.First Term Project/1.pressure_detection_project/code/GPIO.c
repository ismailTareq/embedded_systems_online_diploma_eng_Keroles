#include "GPIO.h"

GPIO_STATE Enable_clock(void)
{
	SET_BIT(APB2ENR,2);
	return GPIO_ENABLE_CLOCK;
}

GPIO_STATE GPIO_Initialization(void)
{
	if(Enable_clock() == GPIO_ENABLE_CLOCK)//means the clock is init.
	{
		return GPIO_INIT;
	}
	else
	{
		return GPIO_ERROR;
	}
}

GPIO_STATE GPIO_Write_Pin(uint8 Port,uint8 Pin,uint8 Logic)
{
	switch(Port)
	{
		case 'A':
		if (Logic == GPIO_HIGH)
		{
			SET_BIT(GPIOA_ODR, Pin);
		}
		else if (Logic == GPIO_LOW)
		{
			CLR_BIT(GPIOA_ODR, Pin);
		}
		break;
	}
	return GPIO_WRITTEN;
}