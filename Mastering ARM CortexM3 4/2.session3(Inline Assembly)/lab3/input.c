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

void EXTI9_callback(void);
void Clock_Init()
{
	//open clock of AFIO
	RCC_AFIO_CLK_EN();

	//open clock of GPIOA
	RCC_GPIOA_CLK_EN();

	//open clock of GPIOB
	RCC_GPIOB_CLK_EN();
}
uint8_t IRQ_Flag = 0;
int val1 = 3;
int main(void)
{
	Clock_Init();


	EXTI_PINCONFIG_t EXTI_CFG;
	EXTI_CFG.EXTI_PIN = EXTI9PB9;
	EXTI_CFG.Trigger = EXTI_Trigger_RISING;
	EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable;
	EXTI_CFG.IRQ_CallBack = EXTI9_callback;
	EXTI_Init(&EXTI_CFG);

	__asm("NOP \n"
			"NOP \n"
			"NOP \n");
//move R0,val1
	__asm("mov R0,%0"
		  : //output
		  : "r" (val1) );//input

	__asm("NOP \n"
			"NOP \n"
			"NOP \n");

	/* Loop forever */
	while(1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}
		else { /* Misra */ }
	}
}
void EXTI9_callback(void)
{
	IRQ_Flag = 1;
}
