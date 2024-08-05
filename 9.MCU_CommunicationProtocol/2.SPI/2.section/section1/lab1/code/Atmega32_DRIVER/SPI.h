/*
 * SPI.h
 *
 * Created: 8/4/2024 3:15:30 PM
 *  Author: ismail
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "DIO.h"
#include "ATMEGA32_REGISTERS.h"
#include "Global_Interrupt.h"

typedef struct
{
	unsigned char			SPI_Polarity;//choosing the clock polarity and phase
	// This parameter must be set based on @ref SPI_CLOCK_define
	
	unsigned char			SPI_phase;//choosing the clock polarity and phase
	// This parameter must be set based on @ref SPI_CLOCK_define
	
	unsigned char		SPI_Prescaler;//setting frequency for tp control SCK rate /clock getting out of the master
	// This parameter must be set based on @ref SPI_FREQUENCY_define
	
	unsigned char			SPI_Mode;//config the pins either to be master or slave
	// This parameter must be set based on @ref SPI_MODE_define
	
	unsigned char   SPI_DoupleSpeed;//making the master give double the speed
	// This parameter must be set based on @ref SPI_DOUBLESPEED_define
	
	unsigned char		SPI_DataOrder;//config which bit will be send first
	// This parameter must be set based on @ref SPI_DATAORDER_define
	
	unsigned char		SPI_Interrupt;//config to enable/disable interrupt
	// This parameter must be set based on @ref SPI_INTERRUPT_define
	
	void(*IRQ_CallBack)(void)
	
}SPI_Config_t;

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*
// @ref SPI_CLOCK_define
/*3 – CPOL:Clock Polarity -> 0: Rising Falling / 1: Falling Rising*/
#define CLK_POLARITY_RISING_FALLING				(unsigned char) (0)		
#define CLK_POLARITY_FALLING_RISING				(unsigned char) (1<<3)  

/*2 – CPHA:Clock Phase -> 0: Sample Setup / 1: Setup Sample */
#define CLK_PHASE_SAMPLE_SETUP					(unsigned char) (0)		
#define CLK_PHASE_SETUP_SAMPLE					(unsigned char) (1<<2)

// @ref SPI_FREQUENCY_define
/* 1:0  SPRn:SPI Clock Rate Select */
#define BAUDERATE_PRESCALER_4					(unsigned char) (0<<0)
#define BAUDERATE_PRESCALER_16					(unsigned char) (1<<0)
#define BAUDERATE_PRESCALER_64					(unsigned char) (2<<0)
#define BAUDERATE_PRESCALER_128					(unsigned char) (3<<0)

/* 0  SPI2X:Double SPI Speed Bit */
#define BAUDERATE_PRESCALER_DOUBLE_SPEED_2		(unsigned char) (0<<0)
#define BAUDERATE_PRESCALER_DOUBLE_SPEED_8		(unsigned char) (1<<0)
#define BAUDERATE_PRESCALER_DOUBLE_SPEED_32		(unsigned char) (2<<0)
#define BAUDERATE_PRESCALER_DOUBLE_SPEED_64		(unsigned char) (3<<0)

// @ref SPI_MODE_define
/*4  MSTR:Master/Slave Select -> 1: Master configuration/ 0: slave configuration*/
#define SPI_MODE_MASTER							(unsigned char) (1<<4) 	
#define SPI_MODE_SLAVE							(unsigned char) (0)

// @ref SPI_DOUBLESPEED_define
#define CLK_SPEED_LOW							(unsigned char) (0)
#define CLK_SPEED_HIGH							(unsigned char) (0)

// @ref SPI_DATAORDER_define
/*5 – DORD:Data Order -> 0: MSB transmitted first / 1: LSB transmitted first */
#define FRAME_FORMAT_MSB_FIRST					(unsigned char) (0)		
#define FRAME_FORMAT_LSB_FIRST					(unsigned char) (1<<5)

// @ref SPI_INTERRUPT_define
/*7 – SPIE:SPI Interrupt Enable -> 0: Disable / 1: Enable*/
#define IRQ_DISABLE								(unsigned char) (0)		
#define IRQ_ENABLE								(unsigned char) (1<<7)


typedef enum
{
	disable,
	enable
}Polling_Mechanism;


//---------------------------------------

//API
ReturnType SPI_Init(const SPI_Config_t* SPI_Config);
ReturnType SPI_SendData(const SPI_Config_t* SPI_Config,unsigned char data);
ReturnType SPI_ReceiveData(const SPI_Config_t* SPI_Config,unsigned char *data);


ReturnType SPI_SendString(const SPI_Config_t* SPI_Config,unsigned char *data);
ReturnType SPI_ReceiveString(const SPI_Config_t* SPI_Config,unsigned char *data);

#endif /* SPI_H_ */