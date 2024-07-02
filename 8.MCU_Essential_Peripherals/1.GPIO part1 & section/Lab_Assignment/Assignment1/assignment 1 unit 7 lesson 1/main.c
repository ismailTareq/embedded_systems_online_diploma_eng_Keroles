/*
 * assignment 1 unit 7 lesson 1.c
 *
 * Created: 7/1/2024 7:27:22 PM
 * Author : ismail
 */ 

#include "util/delay.h"
#include "macros.h"
#include "ATMEGA_REG.h"
#define F_CPU 8000000
//PIN	-> READ
//PORT	-> WRITE
//DDR	-> CONFIG TO I/O
unsigned char PINS[] = {PIN5,PIN6,PIN7,PIN4};//5lit el PIN4 fi 25ir di bta4t el Buzzer
int main(void)
{
    SET_BIT(DDRD,PIN4);//output
	SET_BIT(DDRD,PIN5);//output
	SET_BIT(DDRD,PIN6);//output
	SET_BIT(DDRD,PIN7);//output
	
	
    while (1) 
    {
		for (int i =0;i<4;i++)
		{
			SET_BIT(PORTD,PINS[i]);
			_delay_ms(2000);
			CLR_BIT(PORTD,PINS[i]);
		}
    }
}

