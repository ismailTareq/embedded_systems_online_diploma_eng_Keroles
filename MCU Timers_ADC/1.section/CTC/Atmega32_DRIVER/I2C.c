/*
 * I2C.c
 *
 * Created: 8/6/2024 8:02:38 PM
 *  Author: ismail
 */ 
#include "I2C.h"

void (*GP_I2C_IRQ_CallBack)(void);
void I2C_Init(I2C_Config_t *I2C_Config)
{
	TWCR = 0x00;
	
	//set the prescaler
	TWSR |= I2C_Config->SCL_Prescaler;
	
	uint8_t prescaler;
	switch (I2C_Config->SCL_Prescaler)
	{
		case I2C_PRESCALER1:
		prescaler = 1;
		break;
		case I2C_PRESCALER4:
		prescaler = 4;
		break;
		case I2C_PRESCALER16:
		prescaler = 16;
		break;
		case I2C_PRESCALER64:
		prescaler = 64;
		break;
	}
	TWBR |= (uint8_t)(((F_CPU / I2C_Config->SCL_Frequency) - 16) / (2 * prescaler));
	
	//set ACK
	TWCR |= I2C_Config->ACK_Enable;
	
	//set the slave address
	TWAR |= I2C_Config->I2C_Address & 0xFE;
	
	//set the interrupt
	if(I2C_Config->IRQ_Enable == I2C_INTERRUPT_ENABLE)
	{
		TWCR |= I2C_Config->IRQ_Enable;
		GP_I2C_IRQ_CallBack= I2C_Config->IQR_CallBack;
		Enable_GI();
	}
	//enable I2C
	TWCR |= (1<<2);
}

void I2C_Send_Data(I2C_Config_t *I2C_Config , uint8_t Data, uint8_t Polling)
{
		TWDR = Data;
		
		TWCR &= 0x4F;//clear7,5,4
		
		//clear TWINT write 1
		SET_BIT(TWCR,7);
		if (Polling == I2C_POLLING_ENABLE)
		{
			while(!(TWCR & (1<<7)));
		}
}
void I2C_Receive_Data(I2C_Config_t *I2C_Config , uint8_t Polling , uint8_t *data)
{
	TWCR &= 0x4F;//clear7,5,4
	
	//clear TWINT write 1
	SET_BIT(TWCR,7);
	
	if (Polling == I2C_POLLING_ENABLE)
	{
		while(!(TWCR & (1<<7)));
	}
	*data = TWDR;
}
void I2C_Send_Slave_Address(uint8_t Slave_Address, uint8_t Condition, uint8_t Polling)
{
	TWDR = Slave_Address + Condition;
	
	TWCR &= 0x4F;//clear7,5,4
	
	//clear TWINT write 1
	SET_BIT(TWCR,7);
	if (Polling == I2C_POLLING_ENABLE)
	{
		while(!(TWCR & (1<<7)));
	}
}

void I2C_Start()
{
	TWCR |= (1<<7)|(1<<5);
	while(!(TWCR & (1<<7)));
}

void I2C_Stop()
{
	TWCR |= (1<<7)|(1<<4);
	while(!(TWCR & (1<<7)));
}