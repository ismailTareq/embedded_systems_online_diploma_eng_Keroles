/*
 * RCC.h
 *
 *  Created on: Aug 3, 2024
 *      Author: ismail
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_
//Includes
#include "STM32F103X6.h"
#include "GPIO.h"
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*
#define HSE_Clock  (uint32_t)16000000
#define HSI_RC_Clk (uint32_t)8000000

//API
uint32_t RCC_Get_SYSCLK_Frequency(void);
uint32_t RCC_Get_HCLK_Frequency(void);
uint32_t RCC_Get_PCLK1_Frequency(void);
uint32_t RCC_Get_PCLK2_Frequency(void);


#endif /* INC_RCC_H_ */
