/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include <stdio.h>
#include <stdint.h>
typedef volatile unsigned int vuint32_t;
//RCC
#define RCC_BASE       0x40021000
#define RCC_APB2ENR   *(vuint32_t *)(RCC_BASE+0x18)
#define RCC_IOPAEN    (1<<2)
#define RCC_IOPBEN    (1<<3)

//GPIO PORTA
#define GPIOA_BASE     0x40010800
#define GPIOA_CRH      *(vuint32_t *)(GPIOA_BASE+0x04)
#define GPIOA_CRL	   *(vuint32_t *)(GPIOA_BASE+0x00)
#define GPIOA_ODR      *(vuint32_t *)(GPIOA_BASE+0x0C)
#define GPIOA_IDR      *(vuint32_t *)(GPIOA_BASE+0x08)


//PORTB
#define GPIOB_BASE     0x40010C00
#define GPIOB_CRH      *(vuint32_t *)(GPIOB_BASE+0x04)
#define GPIOB_CRL	   *(vuint32_t *)(GPIOB_BASE+0x00)
#define GPIOB_ODR      *(vuint32_t *)(GPIOB_BASE+0x0C)
#define GPIOB_IDR      *(vuint32_t *)(GPIOB_BASE+0x08)

void clock_init(){

	//enable clock for GPIO port A
	RCC_APB2ENR  |= RCC_IOPAEN;
	//enable clock for GPIO port B
	RCC_APB2ENR  |= RCC_IOPBEN;

}
void GPIO_init(void){
	GPIOA_CRL =0x0;
	GPIOB_CRL =0x0;

	//PA1 input Hi-z
	//00: INPUT MODE
	GPIOA_CRL &= ~(0b11<<4);
	//CNF 01: FLOATING INPUT
	GPIOA_CRL |= (0b01<<6);

	//PB1 output push pull mode
	//01: OUTPUT MODE
	GPIOB_CRL |= (0b01<<4); //MODE
	//CNF 00: OUTPUT PUSH PULL
	GPIOB_CRL &= ~(0b11<<6);//CNF clearing to make it 00

	//PA13 input Hi-z
	//00: INPUT MODE
	GPIOA_CRH &= ~(0b11<<20);//MODE clearing to make it 00
	//CNF 01: FLOATING INPUT
	GPIOA_CRH |= (0b01<<22);// CNF

	//PB13 output push pull mode
	//01: OUTPUT MODE
	GPIOB_CRH |= (0b01<<20);//MODE
	//CNF 00: OUTPUT PUSH PULL
	GPIOB_CRH &= ~(0b11<<22);// CNF
}

void delay(int x){

	unsigned int i,j;
	for (i=0; i<x;i++)
	{
		for(j=0;j<255;j++);
	}
}

int main(void)
{
	clock_init();
	GPIO_init();

	while(1)
	{
		//for single press PULLUP
		if(((GPIOA_IDR & (1<<1)) >> 1) ==0)
		{
			GPIOB_ODR ^= (1<<1);
			while((((GPIOA_IDR & (1<<1)) >>1)==0));
		}
		//for multi press PULLDOWN
		if(((GPIOA_IDR & (1<<13)) >> 13) ==1)
		{
			GPIOB_ODR ^= (1<<13);
		}
		delay(1);
	}
}
