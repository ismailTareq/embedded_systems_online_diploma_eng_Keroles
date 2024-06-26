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

#include <stdint.h>

#define RCC_Base 0x40021000
#define PORTA_Base 0x40010800
#define RCC_APB2EN *((volatile uint32_t *) (RCC_Base +0x18))
#define GPIO_CRH   *((volatile uint32_t *) (PORTA_Base +0x04))
#define GPIO_ODR   *((volatile uint32_t *) (PORTA_Base +0x0c))
int main(void)
{
	RCC_APB2EN |=1<<2;
	GPIO_CRH &= 0xff0fffff;
	GPIO_CRH |=0x00200000;
	while(1)
	{
		int i;
		GPIO_ODR |= 1<<13;
		for(int i =0;i<5000;i++);
			GPIO_ODR &=~(1<<13);
		for(int i =0;i<5000;i++);
	}
}
