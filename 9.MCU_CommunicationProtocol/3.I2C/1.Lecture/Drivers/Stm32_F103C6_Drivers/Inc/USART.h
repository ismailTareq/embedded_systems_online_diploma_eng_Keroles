/*
 * USART.h
 *
 *  Created on: Aug 3, 2024
 *      Author: ismail
 */

#ifndef INC_USART_H_
#define INC_USART_H_
#include "STM32F103X6.h"
#include "GPIO.h"
#include "RCC.h"
//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
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

	uint8_t FLOW_CONTROL;  ////Specifies whether the hardware flow control mode is enabled or disabled
	// This parameter must be set based on @ref UART_HwFlowCtl_define

	uint8_t IQR_ENABLE;  ////Specifies enable or disable UART IRQ TX/RX
	// This parameter must be set based on @ref UART_IRQ_Enable_define

	void(* IRQ_CallBack)(void) ;
}USART_CONFIG;

typedef enum {
	disable,
	enable
}Polling_mechism;

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*
// @ref UART_Mode_define
#define UART_MODE_RX                        (uint32_t) (1<<2)  //RE =1
#define UART_MODE_TX                        (uint32_t) (1<<3) //TE =1
#define UART_MODE_TX_RX                     ((uint32_t)(1<<2 | 1<<3))

//@ref UART_BaudRate_define
#define UART_BaudRate_2400                   2400
#define UART_BaudRate_9600                   9600
#define UART_BaudRate_19200                  19200
#define UART_BaudRate_57600                  57600
#define UART_BaudRate_115200                 115200
#define UART_BaudRate_230400                 230400
#define UART_BaudRate_460800                 460800
#define UART_BaudRate_921600                 921600
#define UART_BaudRate_2250000                2250000
#define UART_BaudRate_4500000                4500000

//@ref UART_Payload_Length_define
#define UART_DATA_Length_8B                  (uint32_t)(0)
#define UART_DATA_Length_9B                  (uint32_t)(1<<12)

//@ref UART_Parity_define
#define UART_NOParity                    	(uint32_t)(0)
#define UART_EVENParity                    	((uint32_t)1<<10)
#define UART_ODDParity                     	((uint32_t)(1<<10 | 1<<9))

// @ref UART_StopBits_define
#define UART_HalfStopBits                 	(uint32_t)(1<<12)
#define UART_1StopBits                     	(uint32_t)(0)
#define UART_1HalfStopBits                	(uint32_t)(3<<12)//101
#define UART_2StopBits                    	(uint32_t)(2<<12)//010

//@ref UART_HwFlowCtl_define
#define UART_HwFlowCtl_NONE                  (uint32_t)(0)
#define UART_HwFlowCtl_RTS                   ((uint32_t)1<<8)
#define UART_HwFlowCtl_CTS                   ((uint32_t)1<<9)
#define UART_HwFlowCtl_RTS_CTS               ((uint32_t)(1<<8 | 1<<9))

//@ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE                 (uint32_t)(0)
#define UART_IRQ_Enable_TXE                  (uint32_t)(1<<7) //Transmit data register empty
#define UART_IRQ_Enable_TC                   (uint32_t)(1<<6) //Transmission complete
#define UART_IRQ_Enable_RXNEIE               (uint32_t)(1<<5) //Received data ready to be read & Overrun error detected
#define UART_IRQ_Enable_PE                   (uint32_t)(1<<8) //Parity error

#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )


//API
void UART_Init(USART_t *USARTx, USART_CONFIG* UART_Config);
void UART_DeInit(USART_t *USARTx);
void UART_GPIO_Set_Pins(USART_t *USARTx);
void UART_SendData(USART_t *USARTx, uint16_t *pTxBuffer,Polling_mechism Polling);
void UART_ReceiveData(USART_t *USARTx, uint16_t *pTxBuffer ,Polling_mechism Polling);
void UART_TRANS_COMPLETE(USART_t *USARTx ) ;


#endif /* INC_USART_H_ */
