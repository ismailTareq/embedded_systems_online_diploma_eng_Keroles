/*
 * main.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Mina Karam
 */

/* ======================================= */
/* ============= Includes ================ */
/* ======================================= */

#include "STM32F103x6.h"
#include "GPIO.h"
#include "USART.h"
#include "SPI.h"
#include "EXTI.h"
#include "KPD.h"
#include "LCD.h"
/* =========== Main Program ========== */
/* ========= Global Macros ========== */
#define MCU_Act_As_Master
//#define MCU_Act_As_Slave

/* ========= Global variables ========== */
uint16_t data;

/* ========== Prototypes ========= */
static void Clock_Init(void);
static void USART1_CallBack(void);
static void SPI1_CallBack(IRQ_SOURCE IRQ_src);

int main(void)
{
	/* Initialization */
		Clock_Init();

		/* Configuration of USART1 */
		USART_CONFIG USART1_Config;

		USART1_Config.USART_BAUDRATE = UART_BaudRate_9600;
		USART1_Config.FLOW_CONTROL = UART_HwFlowCtl_NONE;
		USART1_Config.IQR_ENABLE = UART_IRQ_Enable_RXNEIE;
		USART1_Config.IRQ_CallBack = USART1_CallBack;
		USART1_Config.PARITY = UART_NOParity;
		USART1_Config.DATA_LENGTH = UART_DATA_Length_8B;
		USART1_Config.STOPBITS = UART_1StopBits;
		USART1_Config.USART_MODE = UART_MODE_TX_RX;

		UART_Init(USART1, &USART1_Config);
		UART_GPIO_Set_Pins(USART1);

		/* Configuration of SPI1 */
		SPI_Config_t SPI1_Config;

		/* Common Configuration */
		SPI1_Config.BaudRate_Prescaler = SPI_BAUDRATEPRESCALER_8;
		SPI1_Config.CLKPhase = SPI_CLKPHASE_SECONDEDGE;
		SPI1_Config.CLKPolarity = SPI_CLKPOLARITY_HIGH_IDLE;
		SPI1_Config.Data_Order = SPI_MSB_TRANSMITTED_FIRST;
		SPI1_Config.Data_Size = SPI_8BIT_DATASIZE;
		SPI1_Config.Communication_Mode = SPI_DIRECTION_2LINES;

	#ifdef MCU_Act_As_Master
		SPI1_Config.SPI_Mode = SPI_MASTER_MODE;
		SPI1_Config.IRQ_Enable = SPI_IRQ_Disable;
		SPI1_Config.IRQ_CallBack = NULL;
		SPI1_Config.NSS = SPI_NSS_Soft_NSSInternalSoft_Set;	/* To Control when open & when close, Set as Active High */

		/* Configuration of SS */
		GPIO_Config_t SS_Config;

		/* Configure SS at PA4 by GPIO */
		SS_Config.GPIO_PinNumber = GPIO_PIN_4;
		SS_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		SS_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;

		GPIO_Init(GPIOA, &SS_Config);

		/* Force the slave select (High) idle mode */
		GPIO_WRITE_Pin(GPIOA, GPIO_PIN_4, GPIO_HIGH);
	#endif

	#ifdef MCU_Act_As_Slave
		SPI1_Config.SPI_Mode = SPI_SLAVE_MODE;
		SPI1_Config.IRQ_Enable = SPI_IRQ_Enable_RXNEIE;
		SPI1_Config.NSS = SPI_NSS_Hard_Slave;
		SPI1_Config.IRQ_CallBack = SPI1_CallBack;
	#endif
		SPI_Init(SPI1, &SPI1_Config);
		SPI_GPIO_Set_Pins(SPI1);

		/* Loop For Ever */
		while(1){}
	return 0;
}
/* ======== clock Initialize definition ======= */
static void Clock_Init(void)
{
	/* Enable clock GPIOA */
	RCC_GPIOA_CLK_EN();

	/* Enable clock GPIOB */
	RCC_GPIOB_CLK_EN();

	/* Enable Clock For AFIO */
	RCC_AFIO_CLK_EN();
}



static void USART1_CallBack(void)
{
#ifdef MCU_Act_As_Master
	UART_ReceiveData(USART1, &data, disable);
	UART_SendData(USART1, &data, enable);

	/* ========= Send Data To SPI1 =========== */

	/* Slave Selection (Low), to listen  */
	GPIO_WRITE_Pin(GPIOA, GPIO_PIN_4, GPIO_LOW);

	/* Send & Receive data */
	SPI_TX_RX(SPI1, &data, SPIenable);

	/* Slave Selection (High) idle mode */
	GPIO_WRITE_Pin(GPIOA, GPIO_PIN_4, GPIO_HIGH);
#endif
}

static void SPI1_CallBack(IRQ_SOURCE IRQ_src)
{
#ifdef MCU_Act_As_Slave
	/* If RX Buffer Not Empty Interrupt */
	if(IRQ_src.RXNE)
	{
		/* Receive data */
		SPI_ReceiveData(SPI1, &data, SPIenable);

		/* Send the Received data to the terminal to see it */
		UART_SendData(USART1, &data, enable);
	}
#endif
}
