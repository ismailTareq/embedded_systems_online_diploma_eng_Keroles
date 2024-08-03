/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 

#include "DIO.h"
#include "LCD.h"
#include "UART.h"
LCD_4bit_t LCD1 = {
	.RS.port = PORTC_INDEX,
	.RS.pin = DIO_PIN1,
	.RS.direction = DIO_DIRECTION_OUTPUT,
	.RS.logic = DIO_LOW,
	.EN.port = PORTC_INDEX,
	.EN.pin = DIO_PIN3,
	.EN.direction = DIO_DIRECTION_OUTPUT,
	.EN.logic = DIO_LOW,
	.DATA[0].port = PORTC_INDEX,
	.DATA[0].pin = DIO_PIN4,
	.DATA[0].direction = DIO_DIRECTION_OUTPUT,
	.DATA[0].logic = DIO_LOW,
	.DATA[1].port = PORTC_INDEX,
	.DATA[1].pin = DIO_PIN5,
	.DATA[1].direction = DIO_DIRECTION_OUTPUT,
	.DATA[1].logic = DIO_LOW,
	.DATA[2].port = PORTC_INDEX,
	.DATA[2].pin = DIO_PIN6,
	.DATA[2].direction = DIO_DIRECTION_OUTPUT,
	.DATA[2].logic = DIO_LOW,
	.DATA[3].port = PORTC_INDEX,
	.DATA[3].pin = DIO_PIN7,
	.DATA[3].direction = DIO_DIRECTION_OUTPUT,
	.DATA[3].logic = DIO_LOW,
};

USART_CONFIG uartpinconfig;
uint8_t buffer[30];
uint8_t data;
int main(void)
{
	uartpinconfig.DATA_LENGTH = USART_8_DATA_BITS;
	uartpinconfig.USART_BAUDRATE = USART_BAUD_RATE_9600;
	uartpinconfig.IQR_ENABLE = UART_IRQ_Enable_NONE;
	uartpinconfig.USART_MODE = USART_MODE_ASYNC;
	uartpinconfig.STOPBITS = UART_1StopBits;
	uartpinconfig.IRQ_CallBack = NULL;
	uartpinconfig.PARITY = UART_NOParity;
	
	USART_Init(&uartpinconfig);
	LCD_4bit_Init(&LCD1);
	//LCD_4bit_SendData_Position(&LCD1,'M',2,1);
	while (1)
	{
		data = UART_ReceiveData(enable);
		UART_SendData(data,enable);
		LCD_4bit_SendData(&LCD1,data);
	}
}

