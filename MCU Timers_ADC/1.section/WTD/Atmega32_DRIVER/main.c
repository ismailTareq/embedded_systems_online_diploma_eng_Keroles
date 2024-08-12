/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 
#define F_CPU 8000000UL
#include "WDT.h"
#include "Macros.h"
#include <util/delay.h>
int main(void)
{	
	SET_BIT(DDRC,0);
	while(1)
	{
		WDT_ON();
		TOG_BIT(PORTC,0);
		_delay_ms(5000);
		WDT_OFF();
	}
}