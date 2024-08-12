/*
 * ATMEGA32_REGISTERS.h
 *
 * Created: 7/4/2024 4:03:35 PM
 *  Author: ismail
 */ 


#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_
//Includes
#include <stdio.h>
#include <stdint.h>

//---------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
/* PORTA */
#define DDRA   *(volatile unsigned int *)(0x3A)
#define PORTA  *(volatile unsigned int *)(0x3B)
#define PINA   *(volatile unsigned int *)(0x39)
/* PORTB */
#define DDRB   *(volatile unsigned int *)(0x37)
#define PORTB  *(volatile unsigned int *)(0x38)
#define PINB   *(volatile unsigned int *)(0x36)
/* PORTC */
#define DDRC   *(volatile unsigned int *)(0x34)
#define PORTC  *(volatile unsigned int *)(0x35)
#define PINC   *(volatile unsigned int *)(0x33)
/* PORTD */
#define DDRD   *(volatile unsigned int *)(0x31)
#define PORTD  *(volatile unsigned int *)(0x32)
#define PIND   *(volatile unsigned int *)(0x30)
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: Global Interrupt
//-*-*-*-*-*-*-*-*-*-*-*
#define SREG   *(volatile unsigned int *)(0x5F)
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
#define GICR   *(volatile unsigned int *)(0x5B)
#define GIFR   *(volatile unsigned int *)(0x5A)
#define MCUCR  *(volatile unsigned int *)(0x55)
#define MCUCSR *(volatile unsigned int *)(0x54)
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: USART
//-*-*-*-*-*-*-*-*-*-*-*
//written in different way
typedef struct
{
	
	volatile unsigned char UBRRL;		/* USART Baud Rate Register Low, Address Offset: 0x09 */
	
	/* USART Control and Status Register B */
	volatile union {
		volatile unsigned char UCSRB;
		struct {
			volatile unsigned char TXB8	  :1;		/* Transmit Data Bit 8 */
			volatile unsigned char RXB8	  :1;		/* Receive Data Bit 8 */
			volatile unsigned char UCSZ2  :1;		/* Character Size */
			volatile unsigned char TXEN   :1;		/* Transmitter Enable */
			volatile unsigned char RXEN   :1;		/* Receiver Enable */
			volatile unsigned char UDRIE  :1;		/* USART Data Register Empty Interrupt Enable */
			volatile unsigned char TXCIE  :1;		/* TX Complete Interrupt Enable */
			volatile unsigned char RXCIE  :1;		/* RX Complete Interrupt Enable */
		}bits;
	}UCSRB;
	
	/* USART Control and Status Register A */
	volatile union
	{
		volatile unsigned char UCSRA;		/* USART Control and Status Register A, Address Offset: 0x0B  */
		struct
		{
			volatile unsigned char MPCM	:1;		/* Multi-processor Communication Mode */
			volatile unsigned char U2X	:1;		/* Double the USART Transmission Speed */
			volatile unsigned char PE	:1;		/* Parity Error */
			volatile unsigned char DOR	:1;		/* Data OverRun */
			volatile unsigned char FE	:1;		/* Frame Error */
			volatile unsigned char UDRE	:1;		/* USART Data Register Empty */
			volatile unsigned char TXC	:1;		/* USART Transmit Complete */
			volatile unsigned char RXC	:1;		/* USART Receive Complete */
		}bits;
	}UCSRA;
	
	volatile unsigned char UDR;			/* USART I/O Data Register, Address Offset: 0x0C  */
}USART_Typedef_t;
#define UCSRC			(*(volatile unsigned char*)(0x40))

#define UCPOL			0	/* Clock Polarity */
#define UCSZ0			1	/* Character Size */
#define UCSZ1			2	/* Character Size */
#define USBS			3	/* Stop Bit Select */
#define UPM0			4	/* Parity Mode */
#define UPM1			5	/* Parity Mode */
#define UMSEL			6	/* Mode Select */
#define URSEL			7	/* Register Select */

#define UBRRH			(*(volatile unsigned char*)(0x40))
#define USART			((USART_Typedef_t*) (0x29))

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: SPI
//-*-*-*-*-*-*-*-*-*-*-*
#define SPDR			(*(volatile unsigned char*)(0x2F))
#define SPSR			(*(volatile unsigned char*)(0x2E))
#define SPCR			(*(volatile unsigned char*)(0x2D))

#define SPI_DDR          DDRB
#define SPI_PORT         PORTB  

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: I2C
//-*-*-*-*-*-*-*-*-*-*-*
#define TWBR			(*(volatile unsigned char*)(0x20))
#define TWCR			(*(volatile unsigned char*)(0x21))
#define TWAR			(*(volatile unsigned char*)(0x22))
#define TWDR			(*(volatile unsigned char*)(0x23))

#define I2C_DDR          DDRC
#define I2C_PORT         PORTC
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: TIMER 0
#define TCNT0  (*(volatile unsigned char*)(0x52))
#define TCCR0  (*(volatile unsigned char*)(0x53))
#define TIFR   (*(volatile unsigned char*)(0x58))
#define TIMSK  (*(volatile unsigned char*)(0x59))
#define OCR0   (*(volatile unsigned char*)(0x5C))

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: WDT
#define WDTCR  (*(volatile unsigned char*)(0x41))
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: ADC
#define ADMUX   (*(volatile unsigned char*)(0x27))
#define ADCSRA  (*(volatile unsigned char*)(0x26))
#define ADCL	(*(volatile unsigned char*)(0x24))
#define ADCH	(*(volatile unsigned char*)(0x25))
#define ADCHL   (*(volatile unsigned char*)(0x24))
#define SFIOR   (*(volatile unsigned char*)(0x50))
#endif /* ATMEGA32_REGISTERS_H_ */