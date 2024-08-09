/*
 * RCC.c
 *
 *  Created on: Aug 3, 2024
 *      Author: ismail
 */
#include "RCC.h"
//PPRE1[2:0]: APB Low-speed prescaler (APB1)
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
const uint8_t APBPrescTable[8U] = {0,0,0,0,1,2,3,4}; // Shift 1 right == multiply by 2

//Bits 7:4 HPRE[3:0]: AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBPrescTable[16U] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9}; // Shift 1 right == multiply by 2



uint32_t RCC_Get_SYSCLK_Frequency(void)
{
	//Bits 3:2 SWS[1:0]: System clock switch status
	//Set and cleared by hardware to indicate which clock source is used as system clock.
	//00: HSI oscillator used as system clock
	//01: HSE oscillator used as system clock
	//10: PLL used as system clock
	//11: Not applicable
	switch ((RCC->CFGR >> 2) & 0b11) {
	case 0:
		return HSI_RC_Clk;
		break;
	case 1:
		return HSE_Clock;
		break;
	case 2:
		return 16000000;
		break;
	}
	return HSI_RC_Clk;
}
uint32_t RCC_Get_HCLK_Frequency(void)
{
	//Get SYSCLK source and Compute HCLK frequency
	return (RCC_Get_SYSCLK_Frequency() >> AHBPrescTable[(RCC->CFGR >> 4) & 0xF]);
}
uint32_t RCC_Get_PCLK1_Frequency(void)
{
	//Get HCLK source and Compute PCLK1 frequency
	return (RCC_Get_HCLK_Frequency() >> APBPrescTable[(RCC->CFGR >> 8) & 0b111]);
}
uint32_t RCC_Get_PCLK2_Frequency(void)
{
	//Get HCLK source and Compute PCLK2 frequency
	return (RCC_Get_HCLK_Frequency() >> APBPrescTable[(RCC->CFGR >> 11) & 0b111]);
}

