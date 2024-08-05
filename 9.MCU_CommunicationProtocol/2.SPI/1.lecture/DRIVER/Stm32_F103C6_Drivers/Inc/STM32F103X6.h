/*
 * stm32f103x6.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Mina-Karam
 */

#ifndef STM32F103X6_H_
#define STM32F103X6_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "Platform_Types.h"


/* ================================================================ */
/* ================= Base Addresses of Memories =================== */
/* ================================================================ */

#define FLASH_BASE 			((uint32_t)0x08000000)	/* FLASH base address in the alias region */
#define SRAM_BASE			((uint32_t)0x20000000)	/* SRAM base address in the alias region */
#define PERIPHERALS_BASE	((uint32_t)0x40000000)	/* Peripheral base address in the alias region */


#define APB1_BUS_BASE     	(PERIPHERALS_BASE)
#define APB2_BUS_BASE     	(PERIPHERALS_BASE + 0x10000)
#define AHB_BUS_BASE      	(PERIPHERALS_BASE + 0x20000)

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// NVIC (Non-Vectored Interrupt Controller)
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_BASE	0xE000E100UL

#define NVIC_ISER0			*(volatile uint32_t *)(NVIC_BASE + 0x00)
#define NVIC_ISER1			*(volatile uint32_t *)(NVIC_BASE + 0x04)
#define NVIC_ISER2			*(volatile uint32_t *)(NVIC_BASE + 0x08)
#define NVIC_ICER0			*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1			*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2			*(volatile uint32_t *)(NVIC_BASE + 0x88)

/* ================================================================ */
/* ====== AHBx and APBx Bus Peripheral Base Addresses ============= */
/* ================================================================ */

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base addresses for AHB Peripherals
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define RCC_BASE            0x40021000UL

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base addresses for APB2 Peripherals
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define AFIO_BASE           0x40010000UL

#define EXTI_BASE           0x40010400UL

#define GPIOA_BASE          0x40010800UL
#define GPIOB_BASE          0x40010C00UL
#define GPIOC_BASE          0x40011000UL
#define GPIOD_BASE          0x40011400UL
#define GPIOE_BASE          0x40011800UL

#define USART1_BASE         0x40013800UL

#define SPI1_BASE         	0x40013000UL

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Base addresses for APB1 Peripherals
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define USART2_BASE         0x40014400UL
#define USART3_BASE         0x40014800UL

#define SPI2_BASE         	0x40003800UL

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define SET_BIT(Reg,Bit)							(Reg |= (1 << Bit))
#define CLEAR_BIT(Reg,Bit)						(Reg &= ~ (1 << Bit))
#define TOGGLE_BIT(Reg,Bit)						(Reg ^= (1 << Bit))
#define READ_BIT(Reg,Bit)						((Reg >> Bit) & 1)

/* ================================================================ */
/* ===== Peripheral Register Type Definitions (Structures)========= */
/* ================================================================ */

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	 vuint32_t CR; 				/* Clock control register, 					Address offset: 0x00 */
	 vuint32_t CFGR;			/* Clock configuration register, 			Address offset: 0x04 */
	 vuint32_t CIR;				/* Clock interrupt register, 				Address offset: 0x08 */
	 vuint32_t APB2RSTR;		/* APB2 peripheral reset register, 			Address offset: 0x0C */
	 vuint32_t APB1RSTR;		/* APB1 peripheral reset register, 			Address offset: 0x10 */
	 vuint32_t AHBENR;			/* AHB peripheral clock enable register, 	Address offset: 0x14 */
	 vuint32_t APB2ENR;			/* APB2 peripheral clock enable register, 	Address offset: 0x18 */
	 vuint32_t APB1ENR;			/* APB1 peripheral clock enable register, 	Address offset: 0x1C */
	 vuint32_t BDCR;			/* Backup domain control register, 			Address offset: 0x20 */
	 vuint32_t CSR;				/* Control/status register, 				Address offset: 0x24 */
}RCC_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	 vuint32_t CRL;				/* Port configuration register low, 		Address offset: 0x00 */
	 vuint32_t CRH;				/* Port configuration register high, 		Address offset: 0x04 */
	 vuint32_t IDR;				/* Port input data register, 				Address offset: 0x08 */
	 vuint32_t ODR;				/* Port output data register, 				Address offset: 0x0C */
	 vuint32_t BSRR;			/* Port bit set/reset register, 			Address offset: 0x10 */
	 vuint32_t BRR;				/* Port bit reset register, 				Address offset: 0x14 */
	 vuint32_t LCKR;			/* Port configuration lock register, 		Address offset: 0x18 */
}GPIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	 vuint32_t EVCR;			/* Event control register, 							Address offset: 0x00 */
	 vuint32_t MAPR;			/* AF re-map and debug I/O configuration register, 	Address offset: 0x04 */
	 vuint32_t EXTICR[4];		/* External interrupt configuration register, 		Address offset: 0x08 - 0x14 */
	 uint32_t  RESERVED_0;		/* Clock control register, 							Address offset: 0x18 */
	 vuint32_t MAPR2;			/* AF re-map and debug I/O configuration register 2,Address offset: 0x1C */
}AFIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	 vuint32_t IMR;				/* Interrupt mask register, 				Address offset: 0x00 */
	 vuint32_t EMR;				/* Event mask register, 					Address offset: 0x04 */
	 vuint32_t RTSR;			/* Rising trigger selection register, 		Address offset: 0x08 */
	 vuint32_t FTSR;			/* Falling trigger selection register, 		Address offset: 0x0C */
	 vuint32_t SWIER;			/* Software interrupt event register, 		Address offset: 0x10 */
	 vuint32_t PR;				/* Pending register, 						Address offset: 0x14 */
}EXTI_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	 vuint32_t SR;				/* Status register, 						Address offset: 0x00 */
	 vuint32_t DR;				/* Data register , 							Address offset: 0x04 */
	 vuint32_t BRR;				/* Baud rate register, 						Address offset: 0x08 */
	 vuint32_t CR1;				/* Control register 1, 						Address offset: 0x0C */
	 vuint32_t CR2;				/* Control register 2, 						Address offset: 0x10 */
	 vuint32_t CR3;				/* Control register 3, 						Address offset: 0x14 */
	 vuint32_t GTPR;			/* Guard time and pre-scaler register, 		Address offset: 0x18 */
}USART_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	 vuint32_t CR1;				/* SPI control register 1, 					Address offset: 0x00 */
	 vuint32_t CR2;				/* SPI control register 2, 					Address offset: 0x04 */
	 vuint32_t SR;				/* SPI status register, 					Address offset: 0x08 */
	 vuint32_t DR;				/* SPI data register, 						Address offset: 0x0C */
	 vuint32_t CRCPR;			/* SPI CRC polynomial register2, 			Address offset: 0x10 */
	 vuint32_t RXCRCR;			/* SPI RX CRC register, 					Address offset: 0x14 */
	 vuint32_t TXCRCR;			/* SPI TX CRC register, 					Address offset: 0x18 */
	 vuint32_t I2SCFGR;			/* SPI I2S configuration register, 			Address offset: 0x1C */
	 vuint32_t I2SPR;			/* SPI I2S pre-scaler register, 			Address offset: 0x20 */
}SPI_t;

/* ================================================================ */
/* =================== Peripheral Instants  ======================= */
/* ================================================================ */

#define GPIOA			((GPIO_t *)GPIOA_BASE)
#define GPIOB			((GPIO_t *)GPIOB_BASE)
#define GPIOC			((GPIO_t *)GPIOC_BASE)
#define GPIOD			((GPIO_t *)GPIOD_BASE)
#define GPIOE			((GPIO_t *)GPIOE_BASE)

#define RCC				((RCC_t *)RCC_BASE)

#define EXTI			((EXTI_t *)EXTI_BASE)

#define AFIO			((AFIO_t *)AFIO_BASE)

#define USART1			((USART_t *)USART1_BASE)
#define USART2			((USART_t *)USART2_BASE)
#define USART3			((USART_t *)USART3_BASE)

#define SPI1			((SPI_t *)SPI1_BASE)
#define SPI2			((SPI_t *)SPI2_BASE)

/* ================================================================ */
/* =========== Clock Enable/Disable/Reset Macros ================== */
/* ================================================================ */

/*
 * Enable clock
 */
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1 << 2)  //IOPA enable is in bit 2
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1 << 3)  //IOPB enable is in bit 3
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1 << 4)  //IOPC enable is in bit 4
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1 << 5)  //IOPD enable is in bit 5
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1 << 6)  //IOPE enable is in bit 6

#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1 << 0)  //AFIO enable is in bit 0

#define RCC_USART1_CLK_EN()	(RCC->APB2ENR |= 1 << 14) //USART1 enable is in bit 14
#define RCC_USART2_CLK_EN()	(RCC->APB1ENR |= 1 << 17) //USART2 enable is in bit 17
#define RCC_USART3_CLK_EN()	(RCC->APB1ENR |= 1 << 18) //USART3 enable is in bit 18

#define RCC_SPI1_CLK_EN()	(RCC->APB2ENR |= 1 << 12) //SPI1 enable is in bit 12
#define RCC_SPI2_CLK_EN()	(RCC->APB1ENR |= 1 << 14) //SPI1 enable is in bit 14

/*
 * Disable clock
 */
#define RCC_USART1_CLK_DI()	(RCC->APB2ENR &= ~(1 << 14)) //USART1 disable is in bit 14
#define RCC_USART2_CLK_DI()	(RCC->APB1ENR &= ~(1 << 17)) //USART1 disable is in bit 17
#define RCC_USART3_CLK_DI()	(RCC->APB1ENR &= ~(1 << 18)) //USART1 disable is in bit 18

#define RCC_SPI1_CLK_DI()	(RCC->APB2ENR &= ~(1 << 12)) //SPI1 disable is in bit 12
#define RCC_SPI2_CLK_DI()	(RCC->APB1ENR &= ~(1 << 14)) //SPI2 disable is in bit 14

/*
 * Reset clock
 */
#define RCC_USART1_RESET()	(RCC->APB2RSTR |= 1 << 14) //USART1 reset is in bit 14
#define RCC_USART2_RESET()	(RCC->APB1RSTR |= 1 << 17) //USART1 reset is in bit 17
#define RCC_USART3_RESET()	(RCC->APB1RSTR |= 1 << 18) //USART1 reset is in bit 18

#define RCC_SPI1_RESET()	(RCC->APB2RSTR |= 1 << 12) //SPI1 reset is in bit 12
#define RCC_SPI2_RESET()	(RCC->APB1RSTR |= 1 << 14) //SPI2 reset is in bit 14


/* ================================================================ */
/* ================= Interrupt Vector Table ======================= */
/* ================================================================ */

/*
 * EXTI
 */
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40

/*
 * USART
 */
#define USART1_IRQ		37
#define USART2_IRQ		38
#define USART3_IRQ		39

/*
 * SPI
 */
#define SPI1_IRQ		35
#define SPI2_IRQ		36

//-*-*-*-*-*-*-*-*-*-*-*--*-*-*--*-*-*-
//NVIC IRQ Enable/Disable Macros
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-

/*  Enable Interrupt Requests  */

// We Started From IRQ6 Due To DataSheet
// ISER : Interrupt Set Register

#define NVIC_IRQ_6_EXTI0_Enable()			(NVIC_ISER0 |= 1<<6)				// EXTI0 ---> PIN6 in NVIC
#define NVIC_IRQ_7_EXTI1_Enable()			(NVIC_ISER0 |= 1<<7)				// EXTI1 ---> PIN7 in NVIC
#define NVIC_IRQ_8_EXTI2_Enable()			(NVIC_ISER0 |= 1<<8)				// EXTI2 ---> PIN8 in NVIC
#define NVIC_IRQ_9_EXTI3_Enable()			(NVIC_ISER0 |= 1<<9)				// EXTI3 ---> PIN9 in NVIC
#define NVIC_IRQ_10_EXTI4_Enable()			(NVIC_ISER0 |= 1<<10)				// EXTI4 ---> PIN10 in NVIC
#define NVIC_IRQ_23_EXTI5_9_Enable()		(NVIC_ISER0 |= 1<<23)				// EXTI5, EXTI6, EXTI7, EXTI8, EXTI9 ---> PIN23 in NVIC

// 40 - 32 = 8
#define NVIC_IRQ_40_EXTI10_15_Enable()		(NVIC_ISER1 |= 1<<8)				// EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15
																			//  ---> PIN40 in NVIC

#define NVIC_IRQ37_USART1_Enable()			(NVIC_ISER1 |= 1<<(USART1_IRQ - 32))// USART1
#define NVIC_IRQ38_USART2_Enable()			(NVIC_ISER1 |= 1<<(USART2_IRQ - 32))// USART2
#define NVIC_IRQ39_USART3_Enable()			(NVIC_ISER1 |= 1<<(USART3_IRQ - 32))// USART3

#define NVIC_IRQ35_SPI1_Enable()			(NVIC_ISER1 |= 1<<(SPI1_IRQ - 32))	// SPI1
#define NVIC_IRQ36_SPI2_Enable()			(NVIC_ISER1 |= 1<<(SPI2_IRQ - 32))	// SPI2

/* Disable Interrupt Requests */

// We Started From IRQ6 Due To DataSheet
// ICER : Interrupt Clear Register

#define NVIC_IRQ_6_EXTI0_Disable()			(NVIC_ICER0 |= 1<<6)				// EXTI0 ---> PIN6 in NVIC
#define NVIC_IRQ_7_EXTI1_Disable()			(NVIC_ICER0 |= 1<<7)				// EXTI1 ---> PIN7 in NVIC
#define NVIC_IRQ_8_EXTI2_Disable()			(NVIC_ICER0 |= 1<<8)				// EXTI2 ---> PIN8 in NVIC
#define NVIC_IRQ_9_EXTI3_Disable()			(NVIC_ICER0 |= 1<<9)				// EXTI3 ---> PIN9 in NVIC
#define NVIC_IRQ_10_EXTI4_Disable()			(NVIC_ICER0 |= 1<<10)				// EXTI4 ---> PIN10 in NVIC
#define NVIC_IRQ_23_EXTI5_9_Disable()			(NVIC_ICER0 |= 1<<23)				// EXTI5, EXTI6, EXTI7, EXTI8, EXTI9 ---> PIN23 in NVIC

// 40 - 32 = 8
#define NVIC_IRQ_40_EXTI10_15_Disable()		(NVIC_ICER1 |= 1<<8)				// EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15
																			//  ---> PIN40 in NVIC

#define NVIC_IRQ37_USART1_Disable()			(NVIC_ICER1 |= 1<<(USART1_IRQ - 32))// USART1
#define NVIC_IRQ38_USART2_Disable()			(NVIC_ICER1 |= 1<<(USART2_IRQ - 32))// USART2
#define NVIC_IRQ39_USART3_Disable()			(NVIC_ICER1 |= 1<<(USART3_IRQ - 32))// USART3

#define NVIC_IRQ35_SPI1_Disable()			(NVIC_ICER1 |= 1<<(SPI1_IRQ - 32))	// SPI1
#define NVIC_IRQ36_SPI2_Disable()			(NVIC_ICER1 |= 1<<(SPI2_IRQ - 32))	// SPI2

/* ================================================================ */
/* ====================== Generic Macros ========================== */
/* ================================================================ */



#endif /* STM32F103X6_H_ */
