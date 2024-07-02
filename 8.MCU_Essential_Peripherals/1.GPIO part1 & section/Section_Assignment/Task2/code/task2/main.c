/*
 * task1.c
 *
 * Created: 7/2/2024 4:39:58 PM
 * Author : ismail
 */ 

#include "ATMEGA_REG.h"
#include "macros.h"
#define  F_CPU 8000000UL
#include "util/delay.h"

unsigned char LEDS[] = {PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7};
int i=0;
int main(void)
{
    SET_BIT(DDRA,PIN0);
	SET_BIT(DDRA,PIN1);
	SET_BIT(DDRA,PIN2);
	SET_BIT(DDRA,PIN3);
	SET_BIT(DDRA,PIN4);
	SET_BIT(DDRA,PIN5);
	SET_BIT(DDRA,PIN6);
	SET_BIT(DDRA,PIN7);
	
	CLR_BIT(DDRD,PIN0);//pinA1 is input
	
    while (1) 
    {
		while(i<8)
		{
			if(READ_BIT(PIND,PIN0) == 1)
			{
				SET_BIT(PORTA,LEDS[i++]);
				while(READ_BIT(PIND,PIN0) == 1);//waiting until the button is released
			}
		}
		while(i>=0)
		{
			if(READ_BIT(PIND,PIN0) == 1)
			{
				CLR_BIT(PORTA,LEDS[i--]);
				while(READ_BIT(PIND,PIN0) == 1);//waiting until the button is released
			}
		}
    }
}

