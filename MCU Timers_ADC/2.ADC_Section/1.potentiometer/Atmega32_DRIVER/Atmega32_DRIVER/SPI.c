/*
 * SPI.c
 *
 * Created: 8/4/2024 3:15:21 PM
 *  Author: ismail
 */ 
#include "SPI.h"
SPI_Config_t *G_SPI_Config = NULL;	
ReturnType SPI_Init(const SPI_Config_t* SPI_Config)
{
	ReturnType ret;
	if (NULL == SPI_Config)
	{
		ret = E_NOT_OK;
	} 
	else
	{
		G_SPI_Config = &SPI_Config;
		
		uint8_t SPCR_Init = 0x00; //0000 0000 use it to gather all of it and then SPCR = SPCR_Init
		
		SPCR_Init |= 1<<6;//enable SPI
		
		//set the master pins as output except MISO by writing
			/*master		slave
			*
			*  OUTPUT       INPUT   MOSI
			*  INPUT       OUTPUT   MISO
			*  OUTPUT       INPUT   SCK
			*  OUTPUT       INPUT   SS
			*
			*/ 
		//Set Master or Slave
		SPCR_Init |= SPI_Config->SPI_Mode;
		
		if (SPI_Config->SPI_Mode == SPI_MODE_MASTER)
		{
			SPI_DDR |=  ( (1 << 7) | (1 << 5) | (1 << 4) );
			SPI_DDR &= ~(1 << 6);
			SPCR_Init |= (1 << 4);
			
		} 
		else if(SPI_Config->SPI_Mode == SPI_MODE_SLAVE)
		{
			SPI_DDR |= 1<<6;//output
			
			SPI_DDR &= ~((1<<7) | (1<<5) | (1<<4));//input
			
			SPCR_Init &= ~(1 << 4);
		}
			
		//config the clock u choose 
		// CPOL AND CPHA are related	//leading		//trailing
		/*	0		 0				 sampling(rising)	setup(falling)	  mode0
		 *	0		 1				 setup(rising)		sampling(falling) mode1
		 *	1		 0				 sampling(falling)	setup(rising)	  mode2
		 *	1		 1				 setup(falling)	sampling(rising)	  mode3	
		*/
		SPCR_Init |= SPI_Config->SPI_Polarity;
		SPCR_Init |= SPI_Config->SPI_phase;
			
		//set the frequency of SCK rate
		// SPI2X	SPR1	SPR2	SCK Frequency
		/*	0		 0		 0		    f/4
		 *	0		 0		 1			f/16
		 *	0		 1		 0			f/64
		 *	0		 1		 1			f/128
		 *	1		 0		 0			f/2  double speed
		 *	1		 0		 1			f/8  double speed
		 *	1		 1		 0			f/32 double speed
		 *	1		 1		 1			f/64 double speed
		 */
		if (SPI_Config->SPI_DoupleSpeed == CLK_SPEED_LOW)
		{
			SPCR_Init |= SPI_Config->SPI_Prescaler;
		} 
		else
		{
			SPCR_Init |= SPI_Config->SPI_Prescaler;
			SPSR |= 1<<0;
		}
			
		//set which one is gonna be sent first MSB or LSB 
		/* DORD 
		 *  0      MSB First
		 *  1      LSB First
		 */
		SPCR_Init |= SPI_Config->SPI_DataOrder;
		
		//set the interrupt
		if (SPI_Config->SPI_Interrupt == IRQ_ENABLE)
		{
			Enable_GI();
			SPCR_Init |= SPI_Config->SPI_Interrupt;
		} 
		else
		{
			SPCR_Init |= SPI_Config->SPI_Interrupt;
		}
		
		//init the SPCR Register
		SPCR = SPCR_Init;
		
		ret = E_OK;
	}
	return ret;
}

ReturnType SPI_SendData(const SPI_Config_t* SPI_Config,unsigned char data)
{
	ReturnType ret ;
	if (NULL == SPI_Config)
	{
		ret = E_NOT_OK;
	}
	else
	{
		SPDR = data;
		while(!(SPSR & 1<<7));
		ret = E_OK;
	}
	return ret;
}

ReturnType SPI_ReceiveData(const SPI_Config_t* SPI_Config,unsigned char *data)
{
	ReturnType ret ;
	if (NULL == SPI_Config)
	{
		ret = E_NOT_OK;
	}
	else
	{
		while(!(SPSR & 1<<7));
		*data = SPDR;
		ret = E_OK;
	}
	return ret;
}

uint8_t SPI_sendReceive(uint8_t data)
{
	SPDR = data;

	while(BIT_IS_CLEAR(SPSR,SPIF))
	
	return SPDR;
}

ReturnType SPI_sendString(const SPI_Config_t* SPI_Config,unsigned char *data)
{
	unsigned char i=0;
	
	while (data[i] != '\0')
	{
		SPI_SendData(SPI_Config,data[i]);
		i++;
	}
}

ReturnType SPI_receiveString(const SPI_Config_t* SPI_Config,unsigned char *data)
{
	unsigned char i=0;
	
	while (data[i] != '\0')
	{
		
		SPI_ReceiveData(SPI_Config,data[i]);
		i++;
	}
	data[i] = '\0';
	
}
