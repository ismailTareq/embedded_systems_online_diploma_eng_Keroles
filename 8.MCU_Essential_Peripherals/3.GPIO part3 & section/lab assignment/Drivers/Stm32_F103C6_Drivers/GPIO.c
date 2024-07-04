/*
 * GPIO.c
 *
 *  Created on: Jul 3, 2024
 *      Author: ismail
 */
#include "GPIO.h"
uint8_t Get_PinPostion(uint16_t PinNumber)
{
	switch(PinNumber)
	{
		case GPIO_PIN_0:
		case GPIO_PIN_8:
			return 0;
		break;

		case GPIO_PIN_1:
		case GPIO_PIN_9:
			return 4;
		break;

		case GPIO_PIN_2:
		case GPIO_PIN_10:
			return 8;
		break;

		case GPIO_PIN_3:
		case GPIO_PIN_11:
			return 12;
		break;

		case GPIO_PIN_4:
		case GPIO_PIN_12:
			return 16;
		break;

		case GPIO_PIN_5:
		case GPIO_PIN_13:
			return 20;
		break;

		case GPIO_PIN_6:
		case GPIO_PIN_14:
			return 24;
		break;

		case GPIO_PIN_7:
		case GPIO_PIN_15:
			return 28;
		break;
	}
	return 0;
}
/**================================================================
 * @Fn			-GPIO_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PIN_Config
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant
 * @param [in] 	-PIN_Config: a pointer to GPIO_PIN_Configuration_t structure that contains
 * 							 the configuration information for the specified GPIO PIN(saving space)
 * @retval 		-none
 * Note			-STM32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 but LQFP48 Package has only GPIO A,B Part of C,D exported as external PINs from the MCU
================================================================**/
void GPIO_Init(GPIO_t *GPIOx,GPIO_Config_t *pin_config)
{
	// Port configuration register high (GPIOx_CRH) configure PINs from 0 >> 7
	// Port configuration register high (GPIOx_CRH) configure PINs from 8 >> 15
	volatile uint32_t *confg_reg = NULL;
	uint8_t PinConfig = 0;
	//see if it's CRL or CRH
	confg_reg = (pin_config->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL: &GPIOx->CRH ;
	//Reset CNF and MODE
	*confg_reg &= ~(0xf<<Get_PinPostion(pin_config->GPIO_PinNumber));//* because we will write value
	/*
		 * ------------------
		 * | CNF    | MODE	|
		 * ------------------
		 * |  3	| 2 | 1	| 0	| //clear it to write what i want
		 * ------------------
	*/
	//see if the pin is Input or Output so that if it's output i put the speed with it if input then it's only mode
	if((pin_config->GPIO_PinMode == GPIO_MODE_OUTPUT_PP)||(pin_config->GPIO_PinMode == GPIO_MODE_OUTPUT_OD)||(pin_config->GPIO_PinMode == GPIO_MODE_OUTPUT_AF_PP)||(pin_config->GPIO_PinMode == GPIO_MODE_OUTPUT_AF_OD))
	{
		/*
		 * 00: General purpose output push-pull		--> GPIO_MODE_OUTPUT_PP		>>	0x00000004u
		 * 01: General purpose output Open-drain	--> GPIO_MODE_OUTPUT_OD		>>	0x00000005u
		 * 10: Alternate function output Push-pull	--> GPIO_MODE_OUTPUT_AF_PP	>>	0x00000006u
		 * 11: Alternate function output Open-drain	--> GPIO_MODE_OUTPUT_AF_OD	>>	0x00000007u
		 */
		PinConfig = ((((pin_config->GPIO_PinMode - 4) <<2)|(pin_config->GPIO_PinSpeed))&0xf);
	}
	else
	{
		/*
		 * 00: Analog mode			--> GPIO_MODE_ANALOG		>>	0x00000000u
		 * 01: Floating input		--> GPIO_MODE_INPUT_FLO		>>	0x00000001u
		 * 01: Alternative input	--> GPIO_MODE_INPUT_FLO
		 * 11: Input with PU or PD	--> GPIO_MODE_INPUT_PU
		 * //the only thing to diff from PU or PD
		 * 		PU: ODR --> 1
		 * 		PD: ODR --> 0
		 */
		if((pin_config->GPIO_PinMode == GPIO_MODE_ANALOG)||(pin_config->GPIO_PinMode == GPIO_MODE_INPUT_FLO))
		{
			PinConfig = (((pin_config->GPIO_PinMode << 2))&0xf);
		}
		else if(pin_config->GPIO_PinMode == GPIO_MODE_INPUT_AF)
		{
			PinConfig = (((GPIO_MODE_INPUT_FLO << 2))&0xf);
		}
		else
		{
			PinConfig = (((GPIO_MODE_INPUT_PU << 2))&0xf);
			if(pin_config->GPIO_PinMode == GPIO_MODE_INPUT_PU)
				GPIOx->ODR |= pin_config->GPIO_PinNumber;
			else
				GPIOx->ODR &= ~pin_config->GPIO_PinNumber;
		}
	}
	//put values in CNF AND MODE
	*confg_reg |= (PinConfig<<Get_PinPostion(pin_config->GPIO_PinNumber));


}
/**================================================================
 * @Fn			-GPIO_DeInit
 * @brief 		-Reset All the GPIO Registers.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant
 * @retval 		-none
 * Note			-none
================================================================**/
void GPIO_DeInit(GPIO_t *GPIOx,GPIO_Config_t *pin_config)
{
	/*
	 * If MCU Dosen't Have Reset Controller:
	 * 		>> use the reset value of each register to reset the peripheral
	 * GPIOx->CRL =  0x44444444;
	 * GPIOx->CRH =  0x44444444;
	 * GPIOx->IDR; (Read Only)
	 * GPIOx->ODR  =  0x00000000;
	 * GPIOx->BSRR =  0x00000000;
	 * GPIOx->BRR =   0x00000000;
	 * GPIOx->LCKR =  0x00000000;
	 */

	/*
	 * APB2 peripheral reset register (RCC_APB2RSTR)
	 * IOPxRST: IO port x reset
	 * Set and cleared by software.
	 * 0: No effect
	 * 1: Reset IO port A
	 */
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=  (1 << 2);
		RCC->APB2RSTR &= ~(1 << 2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=  (1 << 3);
		RCC->APB2RSTR &= ~(1 << 3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=  (1 << 4);
		RCC->APB2RSTR &= ~(1 << 4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=  (1 << 5);
		RCC->APB2RSTR &= ~(1 << 5);
	}
}
/**================================================================
 * @Fn			-GPIO_READ_Pin,GPIO_READ_Port
 * @brief 		-Read Specific PIN.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PIN_DEFINE.
 * @retval 		-the I/P PIN Value (Two Values based on @ref GPIO_PIN_STATE >> SET or RESET)
 * Note			-none
================================================================**/
uint8_t GPIO_READ_Pin(GPIO_t *GPIOx,uint16_t pinnumber)
{
	if((GPIOx->IDR & pinnumber)!= GPIO_PIN_RESET)
		return GPIO_PIN_SET;
	else
		return GPIO_PIN_RESET;
}
uint16_t GPIO_READ_Port(GPIO_t *GPIOx)
{
	return (uint16_t)GPIOx->IDR;
}
/**================================================================
 * @Fn			-GPIO_WRITE_Pin,GPIO_WRITE_Port
 * @brief 		-Write a value on Specific PIN.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PIN_DEFINE.
 * @param [in] 	-Value: The value that will write to PIN (Two Values based on @ref GPIO_PIN_STATE >> SET or RESET).
 * @retval 		-none
 * Note			-none
================================================================**/
void GPIO_WRITE_Pin(GPIO_t *GPIOx,uint16_t pinnumber,uint8_t value)
{
	//we may write on ODR or on BSRR and BRR
	//check if we set or reset the pin
	/*
	 * BSRR >> Port Bit Set Reset Register
	 * Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
	 * These bits are write-only and can be accessed in Word mode only.
	 * 0: No action on the corresponding ODRx bit
	 * 1: Set the corresponding ODRx bit
	 */
	if(value != GPIO_PIN_RESET)
	{
		//GPIOx->ODR |= pinnumber;
		GPIOx->BSRR = (uint32_t)pinnumber;
	}
	else
		/*
		 * BRR >> Port Bit Reset Register
		 * Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		 * These bits are write-only and can be accessed in Word mode only.
		 * 0: No action on the corresponding ODRx bit
		 * 1: Reset the corresponding ODRx bit
		 */
		GPIOx->BRR = (uint32_t)pinnumber;
}
void GPIO_WRITE_Port(GPIO_t *GPIOx,uint8_t value)
{
	GPIOx->ODR |= (uint32_t)value;
}
/**================================================================
 * @Fn			-GPIO_TOGGLE_Pin
 * @brief 		-Toggle Specific PIN.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PIN_DEFINE.
 * @retval 		-none
 * Note			-none
================================================================**/
void GPIO_TOGGLE_Pin(GPIO_t *GPIOx,uint16_t pinnumber)
{
	GPIOx->ODR ^=(uint32_t)pinnumber;
}
/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-The locking mechanism allows the IO configuration to be frozen.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PINs_define.
 * @retval 		-it returns lock state according to @ref GPIO_LOCK_state (OK if pin config is locked else ERROR)
 * Note			-none
================================================================**/
uint8_t GPIO_LOCK_Pin(GPIO_t *GPIOx,uint16_t pinnumber)
{
	/*
	 * Bit 16 LCKK[16]: Lock key
	 * This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	 * LOCK key writing sequence:
	 * 		>> Write 1
	 * 		>> Write 0
	 * 		>> Write 1
	 * 		>> Read 0
	 * 		>> Read 1 (this read is optional but confirms that the lock is active)
	 * Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	 * 		 Any error in the lock sequence will abort the lock
	 *----------------------------------------------------------------------------------------
	 * Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	 * These bits are read write but can only be written when the LCKK bit is 0.
	 * 0: Port configuration not locked
	 * 1: Port configuration locked
	 */
	volatile uint32_t dummy = 1<<16;
	dummy |= pinnumber;
	//write 1
	GPIOx->LCKR = dummy;
	//write 0
	GPIOx->LCKR = pinnumber;
	//write 1
	GPIOx->LCKR = dummy;
	//read
	dummy = GPIOx->LCKR;
	if(((GPIOx->LCKR) & (1<<16))!=0)//returned 1 lock is active
		return GPIO_LOCK_OK;
	else
		return GPIO_LOCK_ERROR;

}

