/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 

#include "DIO.h"
#include "KeyPad.h"
#include "LCD.h"
keypad_t keypad = {
	.row_pins[0].port = PORTD_INDEX,
	.row_pins[0].pin = DIO_PIN0,
	.row_pins[0].direction = DIO_DIRECTION_OUTPUT,
	.row_pins[0].logic = DIO_LOW,
	.row_pins[1].port = PORTD_INDEX,
	.row_pins[1].pin = DIO_PIN1,
	.row_pins[1].direction = DIO_DIRECTION_OUTPUT,
	.row_pins[1].logic = DIO_LOW,
	.row_pins[2].port = PORTD_INDEX,
	.row_pins[2].pin = DIO_PIN2,
	.row_pins[2].direction = DIO_DIRECTION_OUTPUT,
	.row_pins[2].logic = DIO_LOW,
	.row_pins[3].port = PORTD_INDEX,
	.row_pins[3].pin = DIO_PIN3,
	.row_pins[3].direction = DIO_DIRECTION_OUTPUT,
	.row_pins[3].logic = DIO_LOW,
	.column_pins[0].port = PORTD_INDEX,
	.column_pins[0].pin = DIO_PIN4,
	.column_pins[0].direction = DIO_DIRECTION_INPUT,
	.column_pins[0].logic = DIO_LOW,
	.column_pins[1].port = PORTD_INDEX,
	.column_pins[1].pin = DIO_PIN5,
	.column_pins[1].direction = DIO_DIRECTION_INPUT,
	.column_pins[1].logic = DIO_LOW,
	.column_pins[2].port = PORTD_INDEX,
	.column_pins[2].pin = DIO_PIN6,
	.column_pins[2].direction = DIO_DIRECTION_INPUT,
	.column_pins[2].logic = DIO_LOW,
	.column_pins[3].port = PORTD_INDEX,
	.column_pins[3].pin = DIO_PIN7,
	.column_pins[3].direction = DIO_DIRECTION_INPUT,
	.column_pins[3].logic = DIO_LOW,
};
LCD_8bit_t LCD1 = {
	.RS.port = PORTB_INDEX,
	.RS.pin = DIO_PIN2,
	.RS.direction = DIO_DIRECTION_OUTPUT,
	.RS.logic = DIO_LOW,
	.EN.port = PORTB_INDEX,
	.EN.pin = DIO_PIN3,
	.EN.direction = DIO_DIRECTION_OUTPUT,
	.EN.logic = DIO_LOW,
	.DATA[0].port = PORTA_INDEX,
	.DATA[0].pin = DIO_PIN0,
	.DATA[0].direction = DIO_DIRECTION_OUTPUT,
	.DATA[0].logic = DIO_LOW,
	.DATA[1].port = PORTA_INDEX,
	.DATA[1].pin = DIO_PIN1,
	.DATA[1].direction = DIO_DIRECTION_OUTPUT,
	.DATA[1].logic = DIO_LOW,
	.DATA[2].port = PORTA_INDEX,
	.DATA[2].pin = DIO_PIN2,
	.DATA[2].direction = DIO_DIRECTION_OUTPUT,
	.DATA[2].logic = DIO_LOW,
	.DATA[3].port = PORTA_INDEX,
	.DATA[3].pin = DIO_PIN3,
	.DATA[3].direction = DIO_DIRECTION_OUTPUT,
	.DATA[3].logic = DIO_LOW,
	.DATA[4].port = PORTA_INDEX,
	.DATA[4].pin = DIO_PIN4,
	.DATA[4].direction = DIO_DIRECTION_OUTPUT,
	.DATA[4].logic = DIO_LOW,
	.DATA[5].port = PORTA_INDEX,
	.DATA[5].pin = DIO_PIN5,
	.DATA[5].direction = DIO_DIRECTION_OUTPUT,
	.DATA[5].logic = DIO_LOW,
	.DATA[6].port = PORTA_INDEX,
	.DATA[6].pin = DIO_PIN6,
	.DATA[6].direction = DIO_DIRECTION_OUTPUT,
	.DATA[6].logic = DIO_LOW,
	.DATA[7].port = PORTA_INDEX,
	.DATA[7].pin = DIO_PIN7,
	.DATA[7].direction = DIO_DIRECTION_OUTPUT,
	.DATA[7].logic = DIO_LOW,
};

int main(void)
{
	unsigned char pressed;
	LCD_8bit_Init(&LCD1);
	LCD_8bit_SendString_Position(&LCD1,"hi there",1,5);
	LCD_8bit_SendString_Position(&LCD1,"Ismail",2,5);
	_delay_ms(500);
	LCD_8bit_SendCommand(&LCD1,LCD_CLEAR);
	_delay_ms(500);
	LCD_8bit_SendString_Position(&LCD1,"keypad is ready",1,1);
	KeyPad_Init(&keypad);
    while (1) 
    {
		get_key_pressed(&keypad,&pressed);
		switch (pressed)
		{
			case '#':
			break;
			
			default:
			LCD_8bit_SendData_Position(&LCD1,pressed,2,1);
			break;
		}
    }
}

