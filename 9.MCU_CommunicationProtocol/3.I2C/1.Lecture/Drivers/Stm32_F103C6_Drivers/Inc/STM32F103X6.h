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

#define I2C1_BASE			0x40005400UL
#define I2C2_BASE			0x40005800UL

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

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	vuint32_t CR1;				/* I2C control register 1, 					Address offset: 0x00 */
	vuint32_t CR2;				/* I2C control register 2, 					Address offset: 0x04 */
	vuint32_t OAR1;				/* I2C Own address register 1, 				Address offset: 0x08 */
	vuint32_t OAR2;				/* I2C Own address register 2, 				Address offset: 0x0C */
	vuint32_t DR;				/* I2C Data, 								Address offset: 0x10 */
	vuint32_t SR1;				/* I2C Status register 1, 					Address offset: 0x14 */
	vuint32_t SR2;				/* I2C Status register 2, 					Address offset: 0x18 */
	vuint32_t CCR;				/* I2C Clock control register, 				Address offset: 0x1C */
	vuint32_t TRISE;			/* I2C TRISE register, 						Address offset: 0x20 */

} I2C_t;
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

#define I2C1			((I2C_t *)I2C1_BASE)
#define I2C2			((I2C_t *)I2C2_BASE)

/* ================================================================ */
/* =========== Clock Enable/Disable/Reset Macros ================== */
/* ================================================================ */

/*
 * Enable clock
 */
#define RCC_GPIOA_CLK_EN()	SET_BIT(RCC->APB2ENR,2)//IOPA enable is in bit 2
#define RCC_GPIOB_CLK_EN()	SET_BIT(RCC->APB2ENR,3)  //IOPB enable is in bit 3
#define RCC_GPIOC_CLK_EN()	SET_BIT(RCC->APB2ENR,4)  //IOPC enable is in bit 4
#define RCC_GPIOD_CLK_EN()	SET_BIT(RCC->APB2ENR,5)  //IOPD enable is in bit 5
#define RCC_GPIOE_CLK_EN()	SET_BIT(RCC->APB2ENR,6)  //IOPE enable is in bit 6

#define RCC_AFIO_CLK_EN()	SET_BIT(RCC->APB2ENR,0)  //AFIO enable is in bit 0

#define RCC_USART1_CLK_EN()	SET_BIT(RCC->APB2ENR,14) //USART1 enable is in bit 14
#define RCC_USART2_CLK_EN()	SET_BIT(RCC->APB1ENR,17) //USART2 enable is in bit 17
#define RCC_USART3_CLK_EN()	SET_BIT(RCC->APB1ENR,18) //USART3 enable is in bit 18

#define RCC_SPI1_CLK_EN()	SET_BIT(RCC->APB2ENR,12) //SPI1 enable is in bit 12
#define RCC_SPI2_CLK_EN()	SET_BIT(RCC->APB1ENR,14) //SPI1 enable is in bit 14

#define RCC_I2C1_CLK_EN()	(RCC->APB1ENR |= 1<<21)	//I2C1 enable is in bit 21
#define RCC_I2C2_CLK_EN()	(RCC->APB1ENR |= 1<<22)	//I2C2 enable is in bit 22
/*
 * Disable clock
 */
#define RCC_USART1_CLK_DI()	CLEAR_BIT(RCC->APB2ENR,14) //USART1 disable is in bit 14
#define RCC_USART2_CLK_DI()	CLEAR_BIT(RCC->APB1ENR,17) //USART1 disable is in bit 17
#define RCC_USART3_CLK_DI()	CLEAR_BIT(RCC->APB1ENR,18) //USART1 disable is in bit 18

#define RCC_SPI1_CLK_DI()	CLEAR_BIT(RCC->APB2ENR,12) //SPI1 disable is in bit 12
#define RCC_SPI2_CLK_DI()	CLEAR_BIT(RCC->APB1ENR,14) //SPI2 disable is in bit 14

/*
 * Reset clock
 */
#define RCC_USART1_RESET()	(RCC->APB2RSTR |= 1 << 14) //USART1 reset is in bit 14
#define RCC_USART2_RESET()	(RCC->APB1RSTR |= 1 << 17) //USART1 reset is in bit 17
#define RCC_USART3_RESET()	(RCC->APB1RSTR |= 1 << 18) //USART1 reset is in bit 18

#define RCC_SPI1_RESET()	(RCC->APB2RSTR |= 1 << 12) //SPI1 reset is in bit 12
#define RCC_SPI2_RESET()	(RCC->APB1RSTR |= 1 << 14) //SPI2 reset is in bit 14

#define RCC_I2C1_Reset()	(RCC->APB1RSTR |= 1<<21)	//I2C1 disable is in bit 21
#define RCC_I2C2_Reset()	(RCC->APB1RSTR |= 1<<22)	//I2C2 disable is in bit 22
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

/*
 * I2C
 */
#define 	I2C1_EV_IRQ			31
#define 	I2C1_ER_IRQ			32
#define 	I2C2_EV_IRQ			33
#define 	I2C2_ER_IRQ			34


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

#define NVIC_IRQ31_I2C1_EV_Enable()   		(NVIC_ISER0 |= 1<<( I2C1_EV_IRQ )) //NVIC_ISER0
#define NVIC_IRQ32_I2C1_ER_Enable()   		(NVIC_ISER1 |= 1<<( I2C1_ER_IRQ - 32 )) //NVIC_ISER1 32-32
#define NVIC_IRQ33_I2C2_EV_Enable()   		(NVIC_ISER1 |= 1<<( I2C2_EV_IRQ - 32 )) //NVIC_ISER1 33-32
#define NVIC_IRQ34_I2C2_ER_Enable()   		(NVIC_ISER1 |= 1<<( I2C2_ER_IRQ - 32 )) //NVIC_ISER1 34-32


/* Disable Interrupt Requests */

// We Started From IRQ6 Due To DataSheet
// ICER : Interrupt Clear Register

#define NVIC_IRQ_6_EXTI0_Disable()			(NVIC_ICER0 |= 1<<6)				// EXTI0 ---> PIN6 in NVIC
#define NVIC_IRQ_7_EXTI1_Disable()			(NVIC_ICER0 |= 1<<7)				// EXTI1 ---> PIN7 in NVIC
#define NVIC_IRQ_8_EXTI2_Disable()			(NVIC_ICER0 |= 1<<8)				// EXTI2 ---> PIN8 in NVIC
#define NVIC_IRQ_9_EXTI3_Disable()			(NVIC_ICER0 |= 1<<9)				// EXTI3 ---> PIN9 in NVIC
#define NVIC_IRQ_10_EXTI4_Disable()			(NVIC_ICER0 |= 1<<10)				// EXTI4 ---> PIN10 in NVIC
#define NVIC_IRQ_23_EXTI5_9_Disable()		(NVIC_ICER0 |= 1<<23)				// EXTI5, EXTI6, EXTI7, EXTI8, EXTI9 ---> PIN23 in NVIC


#define NVIC_IRQ_40_EXTI10_15_Disable()		(NVIC_ICER1 |= 1<<8)// 40 - 32 = 8				// EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15
																			//  ---> PIN40 in NVIC

#define NVIC_IRQ37_USART1_Disable()			(NVIC_ICER1 |= 1<<(USART1_IRQ - 32))// USART1
#define NVIC_IRQ38_USART2_Disable()			(NVIC_ICER1 |= 1<<(USART2_IRQ - 32))// USART2
#define NVIC_IRQ39_USART3_Disable()			(NVIC_ICER1 |= 1<<(USART3_IRQ - 32))// USART3

#define NVIC_IRQ35_SPI1_Disable()			(NVIC_ICER1 |= 1<<(SPI1_IRQ - 32))	// SPI1
#define NVIC_IRQ36_SPI2_Disable()			(NVIC_ICER1 |= 1<<(SPI2_IRQ - 32))	// SPI2

#define NVIC_IRQ31_I2C1_EV_Disable()   		(NVIC_ICER0 |= 1<<( I2C1_EV_IRQ )) //NVIC_ICER1 //31
#define NVIC_IRQ32_I2C1_ER_Disable()   		(NVIC_ICER1 |= 1<<( I2C1_ER_IRQ - 32 )) //NVIC_ICER1 32-32
#define NVIC_IRQ33_I2C2_EV_Disable()   		(NVIC_ICER1 |= 1<<( I2C2_EV_IRQ - 32 )) //NVIC_ICER1 33-32
#define NVIC_IRQ34_I2C2_ER_Disable()   		(NVIC_ICER1 |= 1<<( I2C2_ER_IRQ - 32 )) //NVIC_ICER1 34-32

/* ================================================================ */
/* ====================== Bit definition ========================== */
/* ================================================================ */
//Bit definition for I2C_CR1 register
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */

#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */

#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */

#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */

#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */

#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */

#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */

#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */

#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */

#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */

#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */

#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */

#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */

#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */

//Bit definition for I2C_CR2 register
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */

#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */

#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */

#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */

#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */

#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */

//Bit definition for I2C_OAR2 register
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000000 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */

#define I2C_OAR2_ADD2_Pos                   (1U)
#define I2C_OAR2_ADD2_Msk                   (0x1UL << I2C_OAR2_ADD2_Pos)		/*!< 0x00000001 */
#define I2C_OAR2_ADD2						I2C_OAR2_ADD2_Msk				   /*!<  Interface address */

// Bit definition for I2C_SR1 register
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */

#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */

#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */

#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */

#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */

#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */

#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */

#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */

#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */

#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */

#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */

#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */

#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */

#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

//Bit definition for I2C_SR2 register
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */

#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */

#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */

#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */

#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */

#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */

#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */

#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */


#endif /* STM32F103X6_H_ */
