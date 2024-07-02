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
	DDRD = 0xFF;
	PORTC= 0X00;
	
	while (1)
	{
			for(ones = 0; ones<10 ;ones++)
			{
				PORTC = 0b0111 | (display[ones]<<4);
				_delay_ms(1000);
			}
	}
}