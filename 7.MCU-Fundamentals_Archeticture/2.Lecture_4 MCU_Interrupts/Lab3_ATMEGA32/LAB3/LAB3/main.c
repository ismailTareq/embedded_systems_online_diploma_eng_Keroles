/*
 * LAB3.c
 *
 * Created: 6/26/2024 2:34:58 PM
 * Author : ismail
 */ 

#include "avr/io.h"
#include "avr/interrupt.h"
#include "avr/delay.h"
#define F_CPU 8000000UL
#define SET_BIT(ADDRESS, BIT) ADDRESS |= (1<<BIT)
#define CLR_BIT(ADDRESS, BIT) ADDRESS &= ~(1<<BIT)
void EXTI_Init()
{
	//INT0 generated in any logical change
	SET_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);
	//INT1 generated in a rising edge
	SET_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
	//INT2 generated in falling edge
	CLR_BIT(MCUCSR,6);
	//enable interrupts
	SET_BIT(GICR,7); 
	SET_BIT(GICR,6); 
	SET_BIT(GICR,5); 
	//Global interrupt enable
	SET_BIT(SREG,7);
}
void Gpio_Init()
{
	//set the direction for pins (5,6,7) as output pins
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,6);
	SET_BIT(DDRD,7);
}
int main(void)
{
	Gpio_Init();
	EXTI_Init();
    while (1) 
    {
		CLR_BIT(PORTD,5);
		CLR_BIT(PORTD,6);
		CLR_BIT(PORTD,7);
    }
}
ISR(INT0_vect)
{
	SET_BIT(PORTD,5);
	_delay_ms(2000);
}
ISR(INT1_vect)
{
	SET_BIT(PORTD,6);
	_delay_ms(2000);
}
ISR(INT2_vect)
{
	SET_BIT(PORTD,7);
	_delay_ms(2000);
}
