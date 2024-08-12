/*
 * Global_Interrupt.c
 *
 * Created: 7/31/2024 3:12:42 PM
 *  Author: ismail
 */ 
#include "Global_Interrupt.h"

void Enable_GI(void)
{
	//SET_BIT(SREG,7);
	//SREG |= 1<<7;
	sei();
}

void Disable_GI(void)
{
	//CLR_BIT(SREG,7);
	//SREG &= ~(1<<7);
	cli();
}