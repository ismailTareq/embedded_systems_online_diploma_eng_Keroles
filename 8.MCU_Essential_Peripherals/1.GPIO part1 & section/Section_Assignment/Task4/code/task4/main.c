/*
 * task3.c
 *
 * Created: 7/2/2024 5:44:26 PM
 * Author : ismail
 */ 


#include "ATMEGA_REG.h"
#include "macros.h"
#define  F_CPU 8000000UL
#include "util/delay.h"

unsigned char display[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
unsigned char ones;
int main(void)
{
	CLR_BIT(DDRD,PIN0);
	SET_BIT(DDRD,PIN5);
	
	while (1)
	{
		if(READ_BIT(PIND,PIN0) == 1)
		{
			SET_BIT(PORTD,PIN5);
			while(READ_BIT(PIND,PIN0) == 1);
		}
		else
		{
			CLR_BIT(PORTD,PIN5);
		}
	}
}