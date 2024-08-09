/*
 * USART.c
 *
 *  Created on: Aug 3, 2024
 *      Author: ismail
 */
#include "USART.h"

USART_CONFIG* Global_config = NULL;

/**================================================================
 * @Fn				-UART_Init
 * @brief 			- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration EXTI_PinConfig_t
 * @retval 			-none
 * Note				-none
 */
void UART_Init(USART_t *USARTx, USART_CONFIG* UART_Config)
{
	Global_config = UART_Config;
	uint32_t Pclk,BRR;

	//enable the Clock for USART
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
	}
	//enable USART Module
	//CR1  Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13 ;

	//Enable USART Tx and Rx
	//CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_Config->USART_MODE;

	//PAYLOAD Width
	//CR1  Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->DATA_LENGTH;

	//parity control bit
	//CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->PARITY;

	//number of stop bits
	//CR2  Bits 13:12 STOP: STOP bits
	USARTx->CR1 |= UART_Config->STOPBITS;

	//flow control
	//CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR1 |= UART_Config->FLOW_CONTROL;

	//config baud rate
	if(USARTx == USART1)
	{
		Pclk = RCC_Get_PCLK2_Frequency();
	}
	else
	{
		Pclk = RCC_Get_PCLK1_Frequency();
	}
	BRR = UART_BRR_Register(Pclk,UART_Config->USART_BAUDRATE);

	USARTx->BRR = BRR;

	//ENABLE / DISABLE Interrupt
	if(UART_Config->IQR_ENABLE != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_Config->IQR_ENABLE;
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_Enable();
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_Enable();
		}
		else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_Enable();
		}
	}
}
/**================================================================
 * @Fn				-UART_DeInit
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void UART_DeInit(USART_t *USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_DI();
		NVIC_IRQ37_USART1_Disable();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_DI();
		NVIC_IRQ38_USART2_Disable();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_DI();
		NVIC_IRQ39_USART3_Disable();
	}
}
void UART_GPIO_Set_Pins(USART_t *USARTx)
{
	GPIO_Config_t Pin_Config;
	if(USARTx == USART1)
	{
		//PA9 TX
		Pin_Config.GPIO_PinNumber = GPIO_PIN_9;
		Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		GPIO_Init(GPIOA, &Pin_Config);

		// PA10 Rx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_10;
		Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
		GPIO_Init(GPIOA, &Pin_Config);
		//PA11 CTS
		if((Global_config->FLOW_CONTROL == UART_HwFlowCtl_CTS)||(Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS_CTS))
		{
			// PA11 CTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_11;
			Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			GPIO_Init(GPIOA, &Pin_Config);
		}
		//PA12 RTS
		if((Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS)||(Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS_CTS))
		{
			// PA12 RTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_12;
			Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
			GPIO_Init(GPIOA, &Pin_Config);
		}

	}
	else if(USARTx == USART2)
	{
		// PA2 Tx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_2;
		Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		GPIO_Init(GPIOA, &Pin_Config);

		// PA3 Rx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_3;
		Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
		GPIO_Init(GPIOA, &Pin_Config);
		//PA0 CTS
		if((Global_config->FLOW_CONTROL == UART_HwFlowCtl_CTS)||(Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS_CTS))
		{
			// PA0 CTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_0;
			Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			GPIO_Init(GPIOA, &Pin_Config);
		}
		//PA1 RTS
		if((Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS)||(Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS_CTS))
		{
			// PA1 RTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_1;
			Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
			GPIO_Init(GPIOA, &Pin_Config);
		}
	}
	else if(USARTx == USART3)
	{
		// PB10 Tx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_10;
		Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		GPIO_Init(GPIOB, &Pin_Config);

		// PB11 Rx
		Pin_Config.GPIO_PinNumber = GPIO_PIN_11;
		Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
		GPIO_Init(GPIOB, &Pin_Config);
		//PB13 CTS
		if((Global_config->FLOW_CONTROL == UART_HwFlowCtl_CTS)||(Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS_CTS))
		{
			// PA11 CTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_13;
			Pin_Config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			GPIO_Init(GPIOB, &Pin_Config);
		}
		//PB14 RTS
		if((Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS)||(Global_config->FLOW_CONTROL == UART_HwFlowCtl_RTS_CTS))
		{
			// PA12 RTS
			Pin_Config.GPIO_PinNumber = GPIO_PIN_14;
			Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
			GPIO_Init(GPIOB, &Pin_Config);
		}
	}
}
void UART_SendData(USART_t *USARTx, uint16_t *pTxBuffer,Polling_mechism Polling)
{
	if(Polling == enable)
		while(!(USARTx->SR & 1<<7));//when TXE is empty it's set by 1
	//			When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//			the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//			because it is replaced by the parity.
	//			When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//			bit.
	if(Global_config->DATA_LENGTH == UART_DATA_Length_8B)
	{
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
	}
	else
	{
		USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);
	}
}
void UART_ReceiveData(USART_t *USARTx, uint16_t *pTxBuffer ,Polling_mechism Polling)
{
	if(Polling == enable)
		while(!(USARTx->SR & 1<<5));//when RXNE is empty it's set by 1
	if(Global_config->DATA_LENGTH == UART_DATA_Length_9B)
	{
		if(Global_config->PARITY == UART_NOParity)
		{
			//9bit are data
			*pTxBuffer = USARTx->DR;
		}
		else
		{
			//8bit are data and 1bit is parity
			*pTxBuffer = (USARTx->DR & (uint8_t)0xFF);
		}
	}
	else
	{
		if(Global_config->PARITY == UART_NOParity)
		{
			//8bit are data
			*pTxBuffer = (USARTx->DR & (uint8_t)0xFF);
		}
		else
		{
			//7bit are data and 1bit is parity
			*pTxBuffer = (USARTx->DR & (uint8_t)0x7F);
		}
	}
}
void UART_TRANS_COMPLETE(USART_t *USARTx )
{
	while(USARTx->SR & 1<<6);
}
void USART1_IRQHandler (void)
{
	Global_config->IRQ_CallBack();
}
void USART2_IRQHandler (void)
{
	Global_config->IRQ_CallBack();
}
void USART3_IRQHandler (void)
{
	Global_config->IRQ_CallBack();
}
