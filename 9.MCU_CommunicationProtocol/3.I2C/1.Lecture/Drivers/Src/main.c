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
#include "EEPROM.h"
/* =========== Main Program ========== */
/* ========= Global Macros ========== */

/* ========= Global variables ========== */
uint16_t data;

/* ========== Prototypes ========= */
static void Clock_Init(void);


int main(void)
{
	/* Initialization */
	Clock_Init();

	EEPROM_Init();

	uint8_t CH1_To_Write[7] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07};
	uint8_t CH2_To_Read[7] = {0};

	EEPROM_Write_NBytes(0xAF, CH1_To_Write, 7);
	EEPROM_Read_NBytes(0xAF, CH2_To_Read, 7);



	CH1_To_Write[0] = 0xA;
	CH1_To_Write[1] = 0xB;
	CH1_To_Write[2] = 0xC;
	CH1_To_Write[3] = 0xD;

	EEPROM_Write_NBytes(0xFFF, CH1_To_Write, 4);
	EEPROM_Read_NBytes(0xFFF, CH2_To_Read, 4);

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






