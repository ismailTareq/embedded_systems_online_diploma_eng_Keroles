/*
 * UART.c
 *
 * Created: 8/3/2024 10:12:21 PM
 *  Author: ismail
 */ 
#include "UART.h"

void (*IRQ_CallBack)(void);
/* ================================================================
 * @Fn			-USART_Init.
 * @brief	    -initialize the USART according to config instance PinConfig.
 * @param [in] 	-PinConfig: pointer to USART_config that contains USART configuration.
 * @retval 		-none
 * Note			-none
 */
void USART_Init(USART_CONFIG * PinConfig)
{
	//set baudrate
	uint16_t  ubrr_value;
	
	ubrr_value = (uint16_t)(((F_CPU / (PinConfig->USART_BAUDRATE * 8UL))) - 1);
	
	USART->UBRRL = ubrr_value;
	
	UBRRH = ubrr_value >> 8;
	
	//make it asynchronous divider to 16 instead of 8
	USART->UCSRA.bits.U2X = 0;
	
	//set data mode
	/*		UCSZ2 UCSZ1 UCSZ0 Character Size
		 *   0     0     0     5-bit	
		 *   0     0     1     6-bit
		 *   0     1     0     7-bit
		 *   0     1     1     8-bit
		 *   1     1     1     9-bit
	*/
	switch(PinConfig->DATA_LENGTH)
	{
		//when writing on UCSRC it need to be one
		case USART_5_DATA_BITS:
		SET_BIT(UCSRC,7);
		CLR_BIT(UCSRC,1);
		CLR_BIT(UCSRC,2);
		USART->UCSRB.bits.UCSZ2 = 0;
		break;
		case USART_6_DATA_BITS:
		SET_BIT(UCSRC,7);
		SET_BIT(UCSRC,1);
		CLR_BIT(UCSRC,2);
		USART->UCSRB.bits.UCSZ2 = 0;
		break;
		case USART_7_DATA_BITS:
		SET_BIT(UCSRC,7);
		CLR_BIT(UCSRC,1);
		SET_BIT(UCSRC,2);
		USART->UCSRB.bits.UCSZ2 = 0;
		break;
		case USART_8_DATA_BITS:
		SET_BIT(UCSRC,7);
		SET_BIT(UCSRC,1);
		SET_BIT(UCSRC,2);
		USART->UCSRB.bits.UCSZ2 = 0;
		break;
		case USART_9_DATA_BITS:
		SET_BIT(UCSRC,7);
		SET_BIT(UCSRC,1);
		SET_BIT(UCSRC,2);
		USART->UCSRB.bits.UCSZ2 = 1;
		break;
	}
	//set parity
	switch(PinConfig->PARITY)
	{
		/* UPM1 UPM0 ParityMode // UCSRC
		 *  0    0   Disabled
		 *  1    0   Enabled, Even Parity
		 *  1    1   Enabled, Odd Parity
		 */
		
		//when writing on UCSRC it need to be one
		case UART_NOParity:
		SET_BIT(UCSRC,7);
		CLR_BIT(UCSRC,4);
		CLR_BIT(UCSRC,5);
		break;
		case UART_EVENParity:
		SET_BIT(UCSRC,7);
		CLR_BIT(UCSRC,4);
		SET_BIT(UCSRC,5);
		break;
		case UART_ODDParity:
		SET_BIT(UCSRC,7);
		SET_BIT(UCSRC,4);
		SET_BIT(UCSRC,5);
		break;
	}
	//set stop bit
	switch(PinConfig->STOPBITS)
	{
		/* USBS Stop Bit // UCSRC
		 *  0      1-bit
		 *  1      2-bit
		 */
		
		//when writing on UCSRC it need to be one
		case UART_1StopBits:
		SET_BIT(UCSRC,7);
		CLR_BIT(UCSRC,3);
		break;
		case UART_2StopBits:
		SET_BIT(UCSRC,7);
		SET_BIT(UCSRC,3);
		break;
	}
	//set USART mode
	switch(PinConfig->USART_MODE)
	{
		/* UMSEL Bit Settings Mode
		 *     0    Asynchronous Operation
		 *     1    Synchronous Operation
		 */
		
		//when writing on UCSRC it need to be one
		case USART_MODE_ASYNC:
		SET_BIT(UCSRC,7);
		CLR_BIT(UCSRC,6);
		break;
		case USART_MODE_SYNC:
		SET_BIT(UCSRC,7);
		SET_BIT(UCSRC,6);
		break;
	}
	
	//enable tx rx
	USART->UCSRB.bits.TXEN = 1;
	USART->UCSRB.bits.RXEN = 1;
	
	//enable/disable interrupt
	switch(PinConfig->IQR_ENABLE)
	{
		case UART_IRQ_Enable_NONE:
		USART->UCSRB.bits.TXCIE = 0;
		USART->UCSRB.bits.RXCIE = 0;
		Disable_GI();
		break;
		case UART_IRQ_Enable_TXCIE://when transmition is completed interrupt will be generated
		USART->UCSRB.bits.TXCIE = 1;
		USART->UCSRB.bits.RXCIE = 0;
		IRQ_CallBack = PinConfig->IRQ_CallBack;
		Enable_GI();
		break;
		case UART_IRQ_Enable_RXNEIE://when receiving is completed interrupt will be generated
		USART->UCSRB.bits.TXCIE = 0;
		USART->UCSRB.bits.RXCIE = 1;
		IRQ_CallBack = PinConfig->IRQ_CallBack;
		Enable_GI();
		break;
		case UART_IRQ_Enable_TXCIE_RXCIE://when both is completed interrupt will be generated
		USART->UCSRB.bits.TXCIE = 1;
		USART->UCSRB.bits.RXCIE = 1;
		IRQ_CallBack = PinConfig->IRQ_CallBack;
		Enable_GI();
		break;
	}
	
}
/* ================================================================
 * @Fn			-USART_DeInit.
 * @brief	    -deinitialize the USART.
 * @param [in] 	-none
 * @retval 		-none
 * Note			-none
 */
void USART_DeInit(void)
{
	
}
/* ================================================================
 * @Fn			-UART_SendData.
 * @brief	    -transmits the data through USART.
 * @param [in] 	-pTxBuffer: data to be transmitted.
 * @retval 		-none
 * Note			-none
 */
void UART_SendData(uint8_t TxBuffer,Polling_mechism PollingEn)
{
	if(PollingEn == enable)
	{
		while(!(USART->UCSRA.bits.UDRE));
	}
	//TXB8 is the ninth data bit of the received character 
	//Must be written before writing the low bits from UDR
	if(USART->UCSRB.bits.UCSZ2)
	{
		USART->UCSRB.bits.TXB8 = (TxBuffer & (1<<8)>>8);
		USART->UDR = (uint8_t)TxBuffer;
	}
	else
	{
		USART->UDR = (uint8_t)TxBuffer;
	}
}
/* ================================================================
 * @Fn			-UART_ReceiveData.
 * @brief	    -reads the data received by USART.
 * @param [in] 	-none
 * @retval 		-RxBuffer: data received by USART.
 * Note			-none
 */
uint8_t UART_ReceiveData(Polling_mechism PollingEn)
{
	uint8_t RxBuffer = 0;
	if(PollingEn == enable)
	{
		while(!(USART->UCSRA.bits.RXC));
	}
	//RXB8 is the ninth data bit of the received character
	//Must be read before read the low bits from UDR
	if(USART->UCSRB.bits.UCSZ2)
	{
		RxBuffer |= USART->UCSRB.bits.RXB8 << 8;
		RxBuffer |= USART->UDR;
	}
	else
	{
		RxBuffer = USART->UDR;
	}
	return RxBuffer;
}
/* ================================================================
 * @Fn			-USART_SendString.
 * @brief	    -transmits a string through USART.
 * @param [in] 	-pTxBuffer: pointer to the string to be transmitted.
 * @retval 		-none
 * Note			-to work properly it is preferred to use 8bit data in frame
 */
void USART_SendString(uint8_t *TxBuffer)
{
	while (*TxBuffer != '\0')
	{
		while(!(USART->UCSRA.bits.UDRE));
		
		if (USART->UCSRB.bits.UCSZ2)
		{
			USART->UCSRB.bits.TXB8 = 0;
			USART->UDR = (uint8_t)(*TxBuffer);
		} 
		else
		{
			USART->UDR = *TxBuffer;
			TxBuffer++;
		}
	}
	while(!(USART->UCSRA.bits.UDRE));
	USART->UDR = '\0';
}
/* ================================================================
 * @Fn			-USART_ReceiveString.
 * @brief	    -reads the received string by USART char by char.
 * @param [in] 	-pRxBuffer: pointer to array of char to store received string.
 * @retval 		-none
 * Note			-to work properly it is preferred to use 8bit data in frame
 */
void USART_ReceiveString(uint8_t *RxBuffer)
{
	while (1)
	{
		while(!(USART->UCSRA.bits.RXC));
		*RxBuffer = USART->UDR;
		if(*RxBuffer == '\0')
		{
			break;
		}
		else
		{
			RxBuffer++;
		}
	}
}

ISR(USART_RXC_vect)
{
	if (IRQ_CallBack != NULL)
	{
		IRQ_CallBack();
	}
}

/*ISR(USART_TXC_vect)
{
	if (IRQ_CallBack != NULL)
	{
		IRQ_CallBack();
	}
}*/