/*
 * I2C.h
 *
 * Created: 8/6/2024 8:02:48 PM
 *  Author: ismail
 */ 


#ifndef I2C_H_
#define I2C_H_
//Includes
#include "DIO.h"
#include "ATMEGA32_REGISTERS.h"
#include "Global_Interrupt.h"

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
typedef enum
{
	I2C_InterruptDisabled,
	I2C_InterruptEnabled
} I2C_InterruptStatus_t;

typedef enum
{
	I2C_Read,
	I2C_Write
} I2C_ReadWrite_t;

typedef enum
{
	I2C_Master,
	I2C_Slave
} I2C_Mode_t;



typedef enum
{
	I2C_Prescaler_1,
	I2C_Prescaler_4,
	I2C_Prescaler_16,
	I2C_Prescaler_64
} I2C_Prescaler_t;

typedef struct  
{
	uint32_t SCL_Frequency; //set the I2C SCL freq
	//This parameter is set from FCPU
	
	uint8_t SCL_Prescaler; //set prescaler for I2C
	//This parameter is set from @ref I2C_PRESCALER_DEFINE
	
	uint8_t I2C_Address; // give ur MCU a Specific address
	
	uint8_t ACK_Enable; // set the ACK of I2C
	//This parameter is set from @ref I2C_ACK_DEFINE
	
	uint8_t IRQ_Enable; // set the Interrupt of I2C
	//This parameter is set from @ref I2C_INTERRUPT_DEFINE
	
	void(*IQR_CallBack)(void);
	
}I2C_Config_t;

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros Definitions
//-*-*-*-*-*-*-*-*-*-*-*
//@ref I2C_POLLING_DEFINE
#define I2C_POLLING_ENABLE      1
#define I2C_POLLING_DISABLE     0

//@ref I2C_SLAVE_WR_DEFINE
#define I2C_SLAVE_WRITE       0
#define I2C_SLAVE_READ        1

//@ref I2C_INTERRUPT_DEFINE
#define I2C_INTERRUPT_ENABLE	(uint8_t)0x01
#define I2C_INTERRUPT_DISABLE   (uint8_t)0x00

//@ref I2C_ACK_DEFINE
#define I2C_ACK_ENABLE			(uint8_t)0x40
#define I2C_ACK_DISABLE         (uint8_t)0x00

//@ref I2C_PRESCALER_DEFINE
#define I2C_PRESCALER1			(uint8_t)0x00
#define I2C_PRESCALER4			(uint8_t)0x01
#define I2C_PRESCALER16			(uint8_t)0x02
#define I2C_PRESCALER64			(uint8_t)0x03

//from data sheet
//@ref I2C_STATE
#define I2C_M_T_START_CONDITION_TRANSMITTED						0x08
#define I2C_M_T_REPEATED_START_TRANSMITTED						0x10
#define I2C_M_T_SLA_W_TRANSMITTED_ACK_RECEIVED					0x18
#define I2C_M_T_SLA_W_TRANSMITTED_NOT_ACK_RECEIVED				0x20
#define I2C_M_T_DATA_TRANSMITTED_ACK_RECEIVED					0x28
#define I2C_M_T_DATA_TRANSMITTED_NOT_ACK_RECEIVED				0x30
#define I2C_M_T_ARBITRATION_LOST								0x38

#define I2C_M_R_SLA_R_TRANSMITTED_ACK_RECEIVED					0x40
#define I2C_M_R_SLA_R_TRANSMITTED_NOT_ACK_RECEIVED				0x48
#define I2C_M_R_DATA_RECEIVED_ACK_RETURNED						0x50
#define I2C_M_R_DATA_RECEIVED_NOT_ACK_RETURNED					0x58
//---------------------------------------
//API
void I2C_Init(I2C_Config_t *I2C_Config);
void I2C_Start();
void I2C_Stop();
void I2C_Receive_Data(I2C_Config_t *I2C_Config , uint8_t Polling , uint8_t *data);
void I2C_Send_Data(I2C_Config_t *I2C_Config , uint8_t Data, uint8_t Polling);
void I2C_Send_Slave_Address(uint8_t Slave_Address, uint8_t Condition, uint8_t Polling);

#endif /* I2C_H_ */