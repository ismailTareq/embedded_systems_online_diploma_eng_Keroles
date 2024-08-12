/*
 * WDT.c
 *
 * Created: 8/12/2024 9:07:59 PM
 *  Author: ismail
 */ 
#include "WDT.h"

void WDT_OFF(void)
{
	WDTCR |= (1<<4)|(1<<3);
	WDTCR =0x00;
}

void WDT_ON(void)
{
	WDTCR |= (1 << 1) | (1 << 2) | (1 << 3);
	CLR_BIT(WDTCR,0);
}