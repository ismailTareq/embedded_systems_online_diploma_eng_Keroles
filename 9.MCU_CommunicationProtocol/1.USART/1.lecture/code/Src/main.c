/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "STM32F103X6.h"
#include "GPIO.h"
#include "LCD.h"
#include "EXTI.h"
#include "USART.h"




void Clock_Init()
{
	//open clock of AFIO
	RCC_AFIO_CLK_EN();

	//open clock of GPIOA
	RCC_GPIOA_CLK_EN();

	//open clock of GPIOB
	RCC_GPIOB_CLK_EN();
}
unsigned char ch;
void interrupt_callback()
{
	UART_ReceiveData(USART1, &ch, disable);
	UART_SendData(USART1, &ch, disable);
}
int main(void)
{
	USART_CONFIG Usart_config;
	Clock_Init();
	Usart_config.USART_BAUDRATE = UART_BaudRate_115200;
	Usart_config.FLOW_CONTROL = UART_HwFlowCtl_NONE;
	Usart_config.IQR_ENABLE = UART_IRQ_Enable_RXNEIE ;
	Usart_config.IRQ_CallBack = interrupt_callback ;
	Usart_config.PARITY =UART_NOParity ;
	Usart_config.DATA_LENGTH = UART_DATA_Length_8B;
	Usart_config.STOPBITS = UART_1StopBits ;
	Usart_config.USART_MODE = UART_MODE_TX_RX ;

	UART_Init(USART1,&Usart_config);
	UART_GPIO_Set_Pins(USART1);
	/* Loop forever */
	while(1)
	{

	}
}

