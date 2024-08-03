/*
 * EXTI.c
 *
 *  Created on: Jul 30, 2024
 *      Author: ismail
 */
#include "EXTI.h"
#include "GPIO.h"
#include "STM32F103X6.h"

void(*call_back[15])(void); /* array of pointers (15) --> each pointer is pointer to the ISR function */

static void Enable_NVIC (uint16_t IRQ);
static void Disable_NVIC (uint16_t IRQ);
static void Update_EXTI (EXTI_PINCONFIG_t* EXTI_Config);

void(*call_back[15])(void); /* array of pointers (15) --> each pointer is pointer to the ISR function */


/*Generic Macros*/
#define AFIO_GPIO_EXTI_Mapping(x) ( (x == GPIOA)?0:\
									(x == GPIOB)?1:\
									(x == GPIOC)?2:\
									(x == GPIOD)?3:0)

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @brief 		-Initializes the EXTI according to the specified parameters in the EXTI_Config
 * @param [in] 	-EXTI_Config: it's contain the configuration of the Interrupt and this must put according to @ref EXTI_Define
 * 						-EXTI_PIN & Trigger & IRQ_EN & IRQ_CallBack
 * @retval 		-none
================================================================**/
void EXTI_Init(EXTI_PINCONFIG_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}
/**================================================================
 * @Fn			-EXTI_Update
 * @brief 		-it's used to update the EXTI according to the specified parameters in the EXTI_Config at the runtime.
 * @param [in] 	-EXTI_Config: it's contain the configuration of the Interrupt
 * 						-EXTI_PIN & Trigger & IRQ_EN & IRQ_CallBack
 * @retval 		-none
================================================================**/
void EXTI_Update(EXTI_PINCONFIG_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/**================================================================
 * @Fn			-EXTI_DeInit
 * @brief 		-reset  EXTI Registers and NVIC
 * @retval 		-none
================================================================**/

void EXTI_DeInit(void)
{
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->PR = 0xFFFFFFFF;//CLEAR by Writing 1

	//Disable EXT IRQ from NVIC
	NVIC_IRQ_6_EXTI0_Disable();
	NVIC_IRQ_7_EXTI1_Disable();
	NVIC_IRQ_8_EXTI2_Disable();
	NVIC_IRQ_9_EXTI3_Disable();
	NVIC_IRQ_10_EXTI4_Disable();
	NVIC_IRQ_23_EXTI5_9_Disable();
	NVIC_IRQ_40_EXTI10_15_Disable();
}
/**================================================================
 * @Fn			-Update_EXTI
 * @brief 		-it's used to perform the function of initialize or update the interrupt
 * @param [in] 	-EXTI_CFG: it's contain the configuration of the Interrupt and this must put according to @ref EXTI_Define
 * 						-EXTI_PIN & Trigger & IRQ_EN & IRQ_CallBack
 * @retval 		-none
================================================================**/
void Update_EXTI (EXTI_PINCONFIG_t* EXTI_Config)
{
	/* 1. Configure GPIO PIN as floating input (GPIO_MODE_INPUT_FLO) */
	GPIO_Config_t PIN_CFG;
	PIN_CFG.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PIN_CFG.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
	GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_PORT, &PIN_CFG);

	// 2. convert it from AFIO to EXTI
	uint8_t AFIO_EXTICR_index = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber / 4); /* index 0 or 1 or 2 or 3 */


	uint8_t AFIO_EXTICR_position = ((EXTI_Config->EXTI_PIN.EXTI_InputLineNumber % 4) * 4);	/* Position 0 or 4 or 8 or 12 */

	//clear the 4 bits first
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_position);

	//write the values on the 4 bits according to @ref AFIO_GPIO_EXTI_Mapping
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_PORT) & 0xF) << AFIO_EXTICR_position);

	// 3. Choose the trigger case
	//clear it first
	CLEAR_BIT(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	CLEAR_BIT(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	if(EXTI_Config->Trigger == EXTI_Trigger_RISING)
	{
		SET_BIT(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger == EXTI_Trigger_FALLING)
	{
		SET_BIT(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger == EXTI_Trigger_RISING_and_FALLING)
	{
		SET_BIT(EXTI->RTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		SET_BIT(EXTI->FTSR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	// 4. Update IRQ Handling CALLBACK
	call_back[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->IRQ_CallBack;

	//==========================================================================================

	// 5. Enable or Disable IRQ according to (EXTI_CONFIG->EXTI_IRQ_EN)

	// enable interrupt mask register (IMR) at EXTI
	if(EXTI_Config->IRQ_EN == IRQ_Enable)
	{
		SET_BIT(EXTI->IMR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

		// interrupt set enable register (NVIC_ISER) at NVIC
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->IRQ_EN == IRQ_Disable)
	{
		SET_BIT(EXTI->IMR,EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

		// interrupt clear enable register (NVIC_ICER) at NVIC
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}


}
/**================================================================
 * @Fn			-Enable_NVIC
 * @brief 		-it's used to enable the corresponding bit on NVIC to enable IRQ
 * @param [in] 	-input_line_number: it's the input line number to enable the corresponding bit on NVIC
 * @retval 		-none
================================================================**/
void Enable_NVIC(uint16_t input_line_number)
{
	switch(input_line_number)
	{
	case 0:
		NVIC_IRQ_6_EXTI0_Enable();
		break;

	case 1:
		NVIC_IRQ_7_EXTI1_Enable();
		break;

	case 2:
		NVIC_IRQ_8_EXTI2_Enable();
		break;

	case 3:
		NVIC_IRQ_9_EXTI3_Enable();
		break;

	case 4:
		NVIC_IRQ_10_EXTI4_Enable();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ_23_EXTI5_9_Enable();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ_40_EXTI10_15_Enable();
		break;
	}
}

/**================================================================
 * @Fn			-Disable_NVIC
 * @brief 		-it's used to disable the corresponding bit on NVIC to disable IRQ
 * @param [in] 	-input_line_number: it's the input line number to disable the corresponding bit on NVIC
 * @retval 		-none
================================================================**/
void Disable_NVIC(uint16_t input_line_number)
{
	switch(input_line_number)
	{
	case 0:
		NVIC_IRQ_6_EXTI0_Disable();
		break;

	case 1:
		NVIC_IRQ_7_EXTI1_Disable();
		break;

	case 2:
		NVIC_IRQ_8_EXTI2_Disable();
		break;

	case 3:
		NVIC_IRQ_9_EXTI3_Disable();
		break;

	case 4:
		NVIC_IRQ_10_EXTI4_Disable();
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ_23_EXTI5_9_Disable();
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ_40_EXTI10_15_Disable();
		break;
	}
}

void EXTI0_IRQHandler (void)
{
	//cleared by writing 1 into the bit Pending register
	SET_BIT(EXTI->PR,EXTI0);
	//EXTI->PR |= 1<<0;

	//IRQ callback
	call_back[EXTI0]();
}

void EXTI1_IRQHandler (void)
{
	//cleared by writing 1 into the bit Pending register
	SET_BIT(EXTI->PR,EXTI1);
	//EXTI->PR |= 1<<1;

	//IRQ callback
	call_back[EXTI1]();
}
void EXTI2_IRQHandler (void)
{
	//cleared by writing 1 into the bit Pending register
	SET_BIT(EXTI->PR,EXTI2);
	//EXTI->PR |= 1<<2;

	//IRQ callback
	call_back[EXTI2]();
}
void EXTI3_IRQHandler (void)
{
	//cleared by writing 1 into the bit Pending register
	SET_BIT(EXTI->PR,EXTI3);
	//EXTI->PR |= 1<<3;

	//IRQ callback
	call_back[EXTI3]();
}
void EXTI4_IRQHandler (void)
{
	//cleared by writing 1 into the bit Pending register
	SET_BIT(EXTI->PR,EXTI4);
	//EXTI->PR |= 1<<4;

	//IRQ callback
	call_back[EXTI4]();
}
void EXTI9_5_IRQHandler (void)
{
	if(EXTI->PR & 1<<5){SET_BIT(EXTI->PR,EXTI5);call_back[EXTI5]();}
	if(EXTI->PR & 1<<6){SET_BIT(EXTI->PR,EXTI6);call_back[EXTI6]();}
	if(EXTI->PR & 1<<7){SET_BIT(EXTI->PR,EXTI7);call_back[EXTI7]();}
	if(EXTI->PR & 1<<8){SET_BIT(EXTI->PR,EXTI8);call_back[EXTI8]();}
	if(EXTI->PR & 1<<9){SET_BIT(EXTI->PR,EXTI9);call_back[EXTI9]();}
}
void EXTI15_10_IRQHandler (void)
{
	if(EXTI->PR & 1<<10){SET_BIT(EXTI->PR,EXTI10);call_back[EXTI10]();}
	if(EXTI->PR & 1<<11){SET_BIT(EXTI->PR,EXTI11);call_back[EXTI11]();}
	if(EXTI->PR & 1<<12){SET_BIT(EXTI->PR,EXTI12);call_back[EXTI12]();}
	if(EXTI->PR & 1<<13){SET_BIT(EXTI->PR,EXTI13);call_back[EXTI13]();}
	if(EXTI->PR & 1<<14){SET_BIT(EXTI->PR,EXTI14);call_back[EXTI14]();}
	if(EXTI->PR & 1<<15){SET_BIT(EXTI->PR,EXTI15);call_back[EXTI15]();}
}
