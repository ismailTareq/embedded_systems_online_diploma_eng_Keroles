/*
 * UART.h
 *
 * Created: 8/3/2024 10:12:37 PM
 *  Author: ismail
 */ 


#ifndef UART_H_
#define UART_H_
#include "ATMEGA32_REGISTERS.h"
#include "DIO.h"

typedef struct
{
	uint8_t USART_MODE;   // Specifies the TX/RX Mode
	// This parameter must be set based on @ref UART_Mode_define

	uint32_t USART_BAUDRATE;  // Specifies the  baud rate for the communcation
	// This parameter must be set based on @ref UART_BaudRate_define

	uint8_t DATA_LENGTH;  //Specifies the number of data bits transmitted or received in a frame
	// This parameter must be set based on @ref UART_Payload_Length_define

	uint8_t PARITY;  //Specifies the parity mode
	// This parameter must be set based on @ref UART_Parity_define

	uint8_t STOPBITS;  //Specifies the Stop Bits
	// This parameter must be set based on @ref UART_StopBits_define

	uint8_t IQR_ENABLE;  ////Specifies enable or disable UART IRQ TX/RX
	// This parameter must be set based on @ref UART_IRQ_Enable_define

	void(* IRQ_CallBack)(void);
}USART_CONFIG;

typedef enum {
	enable ,
	disable
}Polling_mechism;

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*
// @ref UART_Mode_define
#define USART_MODE_ASYNC				0
#define USART_MODE_SYNC					1

//@ref UART_BaudRate_define
//f_osc = 8.0000MHz
#define USART_BAUD_RATE_2400			207
#define USART_BAUD_RATE_4800			103
#define USART_BAUD_RATE_9600			51
#define USART_BAUD_RATE_14400			34
#define USART_BAUD_RATE_19200			25
#define USART_BAUD_RATE_28800			16
#define USART_BAUD_RATE_38400			12
#define USART_BAUD_RATE_57600			8
#define USART_BAUD_RATE_76800			6
#define USART_BAUD_RATE_115200			3
#define USART_BAUD_RATE_230400			1
#define USART_BAUD_RATE_250000			1

//@ref UART_Payload_Length_define
#define USART_5_DATA_BITS				0
#define USART_6_DATA_BITS				1
#define USART_7_DATA_BITS				2
#define USART_8_DATA_BITS				3
#define USART_9_DATA_BITS				4

//@ref UART_Parity_define
#define UART_NOParity                    	0
#define UART_EVENParity                    	1
#define UART_ODDParity                     	2

// @ref UART_StopBits_define
#define UART_1StopBits                     	0
#define UART_2StopBits                    	1

//@ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE                 0
#define UART_IRQ_Enable_TXCIE				 1
#define UART_IRQ_Enable_RXNEIE               2
#define UART_IRQ_Enable_TXCIE_RXCIE          3                    
//---------------------------------------
//API
void USART_Init(USART_CONFIG * PinConfig);
void USART_DeInit(void);

void UART_SendData(uint8_t TxBuffer,Polling_mechism PollingEn);
uint16_t UART_ReceiveData(Polling_mechism PollingEn);

void USART_SendString(uint8_t *TxBuffer);
void USART_ReceiveString(uint8_t *RxBuffer);


#endif /* UART_H_ */