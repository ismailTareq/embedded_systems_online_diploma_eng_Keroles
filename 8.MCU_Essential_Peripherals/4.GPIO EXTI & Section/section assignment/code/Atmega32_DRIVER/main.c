/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 

#include "DIO.h"
#include "KeyPad.h"
#include "LCD.h"

LCD_4bit_t LCD1 = {
	.RS.port = PORTB_INDEX,
	.RS.pin = DIO_PIN1,
	.RS.direction = DIO_DIRECTION_OUTPUT,
	.RS.logic = DIO_LOW,
	.EN.port = PORTB_INDEX,
	.EN.pin = DIO_PIN3,
	.EN.direction = DIO_DIRECTION_OUTPUT,
	.EN.logic = DIO_LOW,
	.DATA[0].port = PORTA_INDEX,
	.DATA[0].pin = DIO_PIN4,
	.DATA[0].direction = DIO_DIRECTION_OUTPUT,
	.DATA[0].logic = DIO_LOW,
	.DATA[1].port = PORTA_INDEX,
	.DATA[1].pin = DIO_PIN5,
	.DATA[1].direction = DIO_DIRECTION_OUTPUT,
	.DATA[1].logic = DIO_LOW,
	.DATA[2].port = PORTA_INDEX,
	.DATA[2].pin = DIO_PIN6,
	.DATA[2].direction = DIO_DIRECTION_OUTPUT,
	.DATA[2].logic = DIO_LOW,
	.DATA[3].port = PORTA_INDEX,
	.DATA[3].pin = DIO_PIN7,
	.DATA[3].direction = DIO_DIRECTION_OUTPUT,
	.DATA[3].logic = DIO_LOW,
};

int main(void)
{
	unsigned char pressed;
	LCD_4bit_Init(&LCD1);
	LCD_4bit_SendString_Position(&LCD1,"hi there ismail",1,1);
	LCD_4bit_SendString_Position(&LCD1,"learn in depth",2,1);
	_delay_ms(500);
	
}

