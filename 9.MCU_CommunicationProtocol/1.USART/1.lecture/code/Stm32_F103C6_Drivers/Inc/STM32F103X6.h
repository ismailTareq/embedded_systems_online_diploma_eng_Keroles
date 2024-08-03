/*
 * STM32F103X6.h
 *
 *  Created on: Jul 3, 2024
 *      Author: ismail
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_
//Includes
#include <stdio.h>
#include <stdint.h>

//---------------------------------------
//Base addresses for Memories

#define FLASH_Memory_BASE 							0x08000000UL
#define System_Memory_BASE 							0x1FFFF000UL
#define SRAM_Memory_BASE 							0x20000000UL
#define Peripherals_BASE 							0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE 		0xE0000000UL

//---------------------------------------
//NVIC Register MAP
#define NVIC_BASE      0xE000E100UL
#define NVIC_ISER0	    *(volatile uint32_t *)(NVIC_BASE + 0x00)
#define NVIC_ISER1		*(volatile uint32_t *)(NVIC_BASE + 0x04)
#define NVIC_ISER2		*(volatile uint32_t *)(NVIC_BASE + 0x08)

#define NVIC_ICER0		*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1		*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2		*(volatile uint32_t *)(NVIC_BASE + 0x88)
//---------------------------------------
//Base addresses for AHB Peripherals

#define RCC_BASE       0x40021000UL
//or we can write it like this (Peripherals_BASE + 0x00021000UL)

//---------------------------------------
//Base addresses for APB2 Peripherals

//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE     0x40010800UL
#define GPIOB_BASE     0x40010C00UL

//C,D partial included in LQFP48 Package
#define GPIOC_BASE     0x40011000UL
#define GPIOD_BASE     0x40011400UL

//EXTI
#define EXTI_BASE	   0x40010400UL

//AFIO
#define AFIO_BASE      0x40010000UL

//USART1
#define USART1_BASE    0x40013800UL


//---------------------------------------
//Base addresses for APB1 Peripherals
//USART2
#define USART2_BASE    0x40014400UL
//USART3
#define USART3_BASE    0x40014800UL


//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define SET_BIT(Reg,Bit)							(Reg |= (1 << Bit))
#define CLEAR_BIT(Reg,Bit)						(Reg &= ~ (1 << Bit))
#define TOGGLE_BIT(Reg,Bit)						(Reg ^= (1 << Bit))
#define READ_BIT(Reg,Bit)						((Reg >> Bit) & 1)
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t reserved;//0x18
	volatile uint32_t MAPR2;
}AFIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_t;

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA     ((GPIO_t *)GPIOA_BASE)
#define GPIOB     ((GPIO_t *)GPIOB_BASE)
#define GPIOC     ((GPIO_t *)GPIOC_BASE)
#define GPIOD     ((GPIO_t *)GPIOD_BASE)
//or GPIO_t *GPIOA = (GPIO_t *)GPIOA_BASE

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO     ((AFIO_t *)AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: RCC
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC     ((RCC_t *)RCC_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI     ((EXTI_t *)EXTI_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: USART
//-*-*-*-*-*-*-*-*-*-*-*
//USART1
#define USART1   ((USART_t *)USART1_BASE)

//USART2
#define USART2   ((USART_t *)USART2_BASE)

//USART3
#define USART3   ((USART_t *)USART3_BASE)

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()							SET_BIT(RCC->APB2ENR,2)
#define RCC_GPIOB_CLK_EN()							SET_BIT(RCC->APB2ENR,3)
#define RCC_GPIOC_CLK_EN()							SET_BIT(RCC->APB2ENR,4)
#define RCC_GPIOD_CLK_EN()							SET_BIT(RCC->APB2ENR,5)
#define RCC_GPIOE_CLK_EN()							SET_BIT(RCC->APB2ENR,6)
#define RCC_AFIO_CLK_EN()							SET_BIT(RCC->APB2ENR,0)

#define RCC_USART1_CLK_EN()							SET_BIT(RCC->APB2ENR,14)
#define RCC_USART2_CLK_EN()							SET_BIT(RCC->APB1ENR,17)
#define RCC_USART3_CLK_EN()							SET_BIT(RCC->APB1ENR,18)

#define RCC_USART1_CLK_DIS()						SET_BIT(RCC->APB2RSTR,14)
#define RCC_USART2_CLK_DIS()						SET_BIT(RCC->APB1RSTR,17)
#define RCC_USART3_CLK_DIS()						SET_BIT(RCC->APB1RSTR,18)

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//EXTI Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define 	EXTI0_IRQ			6
#define 	EXTI1_IRQ			7
#define 	EXTI2_IRQ			8
#define 	EXTI3_IRQ			9
#define 	EXTI4_IRQ			10
#define 	EXTI5_IRQ			23
#define 	EXTI6_IRQ			23
#define 	EXTI7_IRQ			23
#define 	EXTI8_IRQ			23
#define 	EXTI9_IRQ			23
#define 	EXTI10_IRQ			40
#define 	EXTI11_IRQ			40
#define 	EXTI12_IRQ			40
#define 	EXTI13_IRQ			40
#define 	EXTI14_IRQ			40
#define 	EXTI15_IRQ			40

//USART
#define 	USART1_IRQ			37
#define 	USART2_IRQ			38
#define 	USART3_IRQ			39

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ Enable/Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define  NVIC_IRQ_6_EXTI0_Enable()    		SET_BIT(NVIC_ISER0,6)
#define  NVIC_IRQ_7_EXTI1_Enable()    		SET_BIT(NVIC_ISER0,7)
#define  NVIC_IRQ_8_EXTI2_Enable()    		SET_BIT(NVIC_ISER0,8)
#define  NVIC_IRQ_9_EXTI3_Enable()    		SET_BIT(NVIC_ISER0,9)
#define  NVIC_IRQ_10_EXTI4_Enable()    		SET_BIT(NVIC_ISER0,10)
#define  NVIC_IRQ_23_EXTI5_9_Enable()    	SET_BIT(NVIC_ISER0,23)
#define  NVIC_IRQ_40_EXTI10_15_Enable()    	SET_BIT(NVIC_ISER1,8)//40-32 = 8

#define  NVIC_IRQ_6_EXTI0_Disable()    		SET_BIT(NVIC_ICER0,6)
#define  NVIC_IRQ_7_EXTI1_Disable()    		SET_BIT(NVIC_ICER0,7)
#define  NVIC_IRQ_8_EXTI2_Disable()    		SET_BIT(NVIC_ICER0,8)
#define  NVIC_IRQ_9_EXTI3_Disable()    		SET_BIT(NVIC_ICER0,9)
#define  NVIC_IRQ_10_EXTI4_Disable()    	SET_BIT(NVIC_ICER0,10)
#define  NVIC_IRQ_23_EXTI5_9_Disable()    	SET_BIT(NVIC_ICER0,23)
#define  NVIC_IRQ_40_EXTI10_15_Disable()    SET_BIT(NVIC_ICER1,8)//40-32 = 8

//USART
#define  NVIC_IRQ_37_USART1_Enable()    	SET_BIT(NVIC_ISER1,(USART1_IRQ -32))//37-32 = 5
#define  NVIC_IRQ_38_USART2_Enable()    	SET_BIT(NVIC_ISER1,(USART2_IRQ -32))//38-32 = 6
#define  NVIC_IRQ_39_USART3_Enable()    	SET_BIT(NVIC_ISER1,(USART3_IRQ -32))//39-32 = 7

#define  NVIC_IRQ_37_USART1_Disable()    	SET_BIT(NVIC_ICER1,(USART1_IRQ -32))//37-32 = 5
#define  NVIC_IRQ_38_USART2_Disable()    	SET_BIT(NVIC_ICER1,(USART2_IRQ -32))//38-32 = 6
#define  NVIC_IRQ_39_USART3_Disable()    	SET_BIT(NVIC_ICER1,(USART3_IRQ -32))//39-32 = 7

#endif /* INC_STM32F103X6_H_ */
