/*
 * I2C.c
 *
 *  Created on: Aug 7, 2024
 *      Author: ismail
 */
#include "I2C.h"

static I2C_Flagstatus I2C_Get_FlagStatus(I2C_t *I2Cx, Status Flag);
static void I2C_Start(I2C_t *I2Cx,START_Condition Start, Functional_State State);
static void I2C_Stop(I2C_t *I2Cx, Functional_State State);
static void I2C_Send_Address(I2C_t *I2Cx, uint16_t Device_Address,I2C_Direction Direction);
static void I2C_ACK(I2C_t *I2Cx, Functional_State State);
static void Slave_States (I2C_t* I2Cx  ,Slave_State state);
I2C_Config_t Global_I2C_Config[2] = {0};


/* ================================================================
 * @Fn 				- I2C_Init
 * @brief 			- Initializes I2Cx according to the specified parameters in I2C_Config
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- I2C_Config : a pointer to I2C_Config_t structure that contains the configuration information for the specified I2C Module
 * @retval 			- None
 * Note 			- Supported for I2C SM mode only
 * 					- Support only 7-bit address mode
 */
void I2C_Init(I2C_t *I2Cx, I2C_Config_t *I2C_Config)
{
	uint16_t Temp = 0 , Frequency = 0, Result = 0;
	uint32_t Pclk1 = 0;

	// Enable the RCC Clock
	if(I2Cx == I2C1)
	{
		// If I2C1 Put all configurations in the global configuration
		Global_I2C_Config[0] = *I2C_Config;

		// Open the I2C1 RCC Clock
		RCC_I2C1_CLK_EN();
	}
	else if(I2Cx == I2C2)
	{
		// If I2C2 Put all configurations in the global configuration
		Global_I2C_Config[1] = *I2C_Config;

		// Open the I2C2 RCC Clock
		RCC_I2C2_CLK_EN();
	}

	// Set I2C Mode
	if(I2C_Config->I2C_Mode == I2C_MODE_I2C)
	{
		//     Initialize Timing
		/*
		 * --- I2C_CR2 -> Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		 */

		Temp = I2Cx->CR2;

		// Clear frequency
		Temp &= ~(I2C_CR2_FREQ_Msk); // (0x3FUL << 0) clear first 5bits

		// Get Pclk1 frequency value
		Pclk1 = RCC_Get_PCLK1_Frequency();

		// Set frequency bits depending in Pclk1 value
		Frequency = (uint16_t)(Pclk1/1000000);

		// Move the configuration in the temp to set it in the CR2 register
		Temp |= Frequency;
		I2Cx->CR2 = Temp;

		// Configure CCR register

		// 7. Disable I2C peripheral
		I2Cx->CR1 &= ~(I2C_CR1_PE);

		// Put the temp register with zero
		Temp = 0;

		// Configure the speed in the standard mode / Fast Mode
		if((I2C_Config->Clock_Speed == I2C_CLOCK_SPEED_50KHZ)||(I2C_Config->Clock_Speed == I2C_CLOCK_SPEED_100KHZ))
		{
			//Enable standard mode but its zero as default because we but zero in temp

			// Put the standard mode calculation
			/*
			 * Tclk / 2 = CCR * Tpclk1
			 * CCR = Tclk / (2 * Tpclk1)
			 * CCR = Fpclk / (2 * I2C_ClockFrequency)
			 */
			Result = (uint16_t)(Pclk1/(I2C_Config->Clock_Speed << 1));//shift left = *2

			// Move the configuration in the temp to set it in the CCR register
			Temp |= Result;
			I2Cx->CCR = Temp;

			// Configure TRISE register
			/*
			 * For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			 * If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			 * therefore the TRISE[5:0] bits must be programmed with 09h.
			 * (1000 ns / 125 ns = 8 + 1)
			 */
			I2Cx->TRISE = Frequency + 1;
		}
		// ConfigCR1register

		// Get the I2C CR1 value
		Temp = I2Cx->CR1;

		// Set All configuration to the temp register and put it in CR1
		Temp |= (uint16_t)(I2C_Config->ACK_Control | I2C_Config->General_Call | I2C_Config->I2C_Mode | I2C_Config->Stretch_Mode);
		I2Cx->CR1 = Temp;

		// Config OAR registers

		// Put the temp register with zero
		Temp = 0;

		// Check the Slave_Address type
		if(I2C_Config->Slave_Address.Enable_Dual_Address == 1)
		{
			// Enable the Dual addressing mode
			Temp = I2C_OAR2_ENDUAL;

			// Put the input Second address form the user to the register
			/*
			 * Bits 7:1 ADD2[7:1]: Interface address
			 * 		bits 7:1 of address in dual addressing mode
			 */
			Temp |= I2C_Config->Slave_Address.Slave_Second_Address << I2C_OAR2_ADD2_Pos; // Shifting with the first bit in the register

			// Set the "I2C_OAR2" register with our new value
			I2Cx->OAR2 = Temp;
		}

		// Put the temp register with zero
		Temp = 0;

		// Put the input First address form the user to the register
		Temp |= I2C_Config->Slave_Address.Slave_First_Address << 1 ;

		// Configure ADDMODE Addressing mode (slave mode)
		Temp |= I2C_Config->Slave_Address.Slave_Address_Mode ;

		// Set the "I2C_OAR1" register with Temp
		I2Cx->OAR1 = Temp;
	}

	// Interrupt mode  works in (Slave Mode)
	if(I2C_Config->Slave_CallBack != NULL) // That enable slave IRQ states mode
	{
		// Enable IRQ
		I2Cx->CR2 |= (I2C_CR2_ITERREN); // Error interrupt enable
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN); // Event interrupt enable
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN); // Buffer interrupt enable

		// Enable IRQ in NVIC
		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable();
			NVIC_IRQ32_I2C1_ER_Enable();
		}
		else if (I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable();
			NVIC_IRQ34_I2C2_ER_Enable();
		}

		// Put the status registers with zero
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}

	// Enable I2C peripheral
	I2Cx->CR1 |= I2C_CR1_PE;
}

/* ================================================================
 * @Fn 				- I2C_DeInit
 * @brief 			- Resets Selected I2C Module and disable NVIC IRQs
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- None
 */
void I2C_DeInit(I2C_t *I2Cx)
{
	if (I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable();
		NVIC_IRQ32_I2C1_ER_Disable();
		RCC_I2C1_Reset();
	}
	else if(I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_Disable();
		NVIC_IRQ34_I2C2_ER_Disable();
		RCC_I2C2_Reset();
	}
}

/* ================================================================
 * @Fn 				- I2C_GPIO_SetPins
 * @brief 			- Initializes GPIO Pins to be connected with the selected I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Supported for I2C SM MODE only
 */
void I2C_GPIO_SetPins(I2C_t *I2Cx)
{
	GPIO_Config_t Pin_Config;
	if(I2Cx == I2C1)
	{
		//PB6 SCL
		Pin_Config.GPIO_PinNumber = GPIO_PIN_6;
		Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		GPIO_Init(GPIOB, &Pin_Config);
		//PB7 SDA
		Pin_Config.GPIO_PinNumber = GPIO_PIN_7;
		Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		GPIO_Init(GPIOB, &Pin_Config);
	}
	else if(I2Cx == I2C2)
	{
		//PB10 SCL
		Pin_Config.GPIO_PinNumber = GPIO_PIN_10;
		Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		GPIO_Init(GPIOB, &Pin_Config);
		//PB11 SDA
		Pin_Config.GPIO_PinNumber = GPIO_PIN_11;
		Pin_Config.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		Pin_Config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		GPIO_Init(GPIOB, &Pin_Config);
	}
}

/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_TX
 * @brief 			- Master Send data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- Device_Address : slave address
 * @param [in] 		- pTxData : a pointer to the data which will be send
 * @param [in] 		- Data_Length : number of data bytes to be Transmitted
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void I2C_MASTER_SendData(I2C_t *I2Cx, uint16_t Device_Address, uint8_t *Data, uint8_t Data_Length, STOP_Condition Stop, START_Condition Start)
{
	int i = 0;

	// generate a start condition
	I2C_Start(I2Cx, Start, Enable);

	// Wait for EV5
	while(!(I2C_Get_FlagStatus(I2Cx, EV5)));

	/* 3. Writing DR register with Address, Send Address */
	I2C_Send_Address(I2Cx, Device_Address, Transmitter);

	// Wait for EV6
	while(!(I2C_Get_FlagStatus(I2Cx, EV6)));

	// Wait for EV8_1
	while(!(I2C_Get_FlagStatus(I2Cx, Master_Transmitter_Event)));

	/* Loop inside the data ready to send it */
	for (i = 0; i < Data_Length; ++i)
	{
		// Write in the DR register the data to be sent
		I2Cx->DR = Data[i];

		// Wait for EV8
		while(!(I2C_Get_FlagStatus(I2Cx, EV8)));
	}

	// Send Stop Condition
	if(Stop == With_STOP)
	{
		I2C_Stop(I2Cx, Enable);
	}
}

/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_RX
 * @brief 			- Master Receive data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- Device_Address : slave address
 * @param [in] 		- pRxData : a pointer to the data which will be send
 * @param [in] 		- Data_Length : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void I2C_MASTER_ReceiveData(I2C_t *I2Cx, uint16_t Device_Address, uint8_t *Data, uint8_t Data_Length, STOP_Condition Stop, START_Condition Start)
{
	int i = 0;

	uint8_t index = I2Cx == I2C1 ? 0 : 1;

	// Set the start bit in the I2C_CR1 register to generate a start condition from this will start as master */
	I2C_Start(I2Cx, Start, Enable);

	// Wait for EV5
	while(!(I2C_Get_FlagStatus(I2Cx, EV5)));

	// Writing DR register with Address, Send Address
	I2C_Send_Address(I2Cx, Device_Address, Receiver);

	// Wait for EV6
	while(!(I2C_Get_FlagStatus(I2Cx, EV6)));

	// Enable Automatic ACK
	I2C_ACK(I2Cx, Enable);

	if(Data_Length)
	{
		//receive the data
		for (i = Data_Length; i > 1 ; i--)
		{
			// Wait for EV7
			while(!(I2C_Get_FlagStatus(I2Cx, EV7)));

			// Read the data in the DR register
			*Data = I2Cx->DR;

			/* 10. Go to next address */
			Data++;
		}
	}

	/* Send ---- > NACK */
	I2C_ACK(I2Cx, Disable);

	// Send Stop Condition
	if(Stop == With_STOP)
	{
		I2C_Stop(I2Cx, Enable);
	}

	// Re-Enable the automatic ACK
	if(Global_I2C_Config[index].ACK_Control == I2C_ACK_CONTROL_ENABLE)
		I2C_ACK(I2Cx, Enable);
	else
		I2C_ACK(I2Cx, Disable);
}

/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_TX
 * @brief 			- Slave send data to master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- TxData : slave data to be sent to master
 * @retval 			- None
 * Note 			- Support interrupt mechanism only
 */
void I2C_Slave_SendData(I2C_t *I2Cx, uint8_t TxData)
{
	I2Cx->DR = TxData;
}

/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_RX
 * @brief 			- Slave Receive data from master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- Received data
 * Note 			- Support interrupt mechanism only
 *
 */
uint8_t I2C_Slave_ReceiveData(I2C_t *I2Cx)
{
	return (I2Cx->DR);
}


/* ================================================================ */
/* ======================== Generic APIs ========================== */
/* ================================================================ */


static I2C_Flagstatus I2C_Get_FlagStatus(I2C_t *I2Cx, Status Flag)
{
	//vuint32_t Dummy_Read = 0; // Volatile for compiler optimization
	uint32_t flag1 = 0, flag2 = 0, Last_Event;
	I2C_Flagstatus Bit_Status = RESET;

	switch (Flag)
	{
	case BUS_BUSY:
	{
		/*  Bit 1 BUSY: Bus busy
				0: No communication on the bus
				1: Communication ongoing on the bus
				– Set by hardware on detection of SDA or SCL low
				– cleared by hardware on detection of a Stop condition.
				It indicates a communication in progress on the bus. This information is still updated when the interface is disabled (PE=0).
		 */
		if((I2Cx->SR2) & (I2C_SR2_BUSY))
			Bit_Status = SET;
		else
			Bit_Status = RESET;
		break;
	}

	case EV5:
	{
		/*
		 * Bit 0 SB: Start bit (Master mode)
			0: No Start condition
			1: Start condition generated.
			  – Set when a Start condition generated.
			  – Cleared by software by reading the SR1 register followed by writing the DR register, or by hardware when PE=0
		 */
		if((I2Cx->SR1) & (I2C_SR1_SB))
			Bit_Status = SET;
		else
			Bit_Status = RESET;
		break;
	}

	case EV6:
	{
		/*
		 * 	Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
			This bit is cleared by software reading SR1 register followed reading SR2, or by hardware when PE=0.

			Address matched (Slave)
			0: Address mismatched or not received.
			1: Received address matched.
			– Set by hardware as soon as the received slave address matched with the OAR registers
			content or a general call (when enabled depending on configuration).
			Note: In slave mode, it is recommended to perform the complete clearing sequence (READ
			SR1 then READ SR2) after ADDR is set.

			Address sent (Master)
			0: No end of address transmission
			1: End of address transmission
			– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
			– For 7-bit addressing, the bit is set after the ACK of the byte.

			Note: ADDR is not set after a NACK reception
		 */
		if((I2Cx->SR1) & (I2C_SR1_ADDR))
			Bit_Status = SET;
		else
			Bit_Status = RESET;

		/* This bit is cleared by software reading SR1 register followed reading SR2, or by hardware when PE=0. */
		//Dummy_Read = I2Cx->SR2;
		break;
	}

	case EV8:
	{
		/*
		 *  Bit 7 TxE: Data register empty (transmitters)
				0: Data register not empty
				1: Data register empty
				– Set when DR is empty in transmission. TxE is not set during address phase.
				– Cleared by software writing to the DR register or by hardware after a start or a stop condition or when PE=0.
				TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
				Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
				BTF is set, as in both cases the data register is still empty.
		 */
		if((I2Cx->SR1) & (I2C_SR1_TXE))
			Bit_Status = SET;
		else
			Bit_Status = RESET;
		break;
	}

	case EV7 :
	{
		/*
		 *  Bit 6 RxNE: Data register not empty (receivers)
				0: Data register empty
				1: Data register not empty
				– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
				– Cleared by software reading or writing the DR register or by hardware when PE=0.
				RxNE is not set in case of ARLO event.
				Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.
		 */
		if((I2Cx->SR1) & (I2C_SR1_RXNE))
			Bit_Status = SET;
		else
			Bit_Status = RESET;
		break;
	}

	case Master_Transmitter_Event :
	{
		/* Check if BUSY ,TRA ,MSL W,TXE flags are all set */

		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2 << 16;
		/* Get the last event value from I2C status register */
		Last_Event = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
		/* Check whether the last event contains the I2C_EVENT */
		if ((Last_Event & Flag) == Flag)
			Bit_Status = SET ;

		else
			Bit_Status = RESET ;
	}
	}
	return Bit_Status;
}

static void I2C_Start(I2C_t *I2Cx,START_Condition Start, Functional_State State)
{
	// Check the type of start (Start or Repeated Start)
	if(Start != Repeated_START)
	{
		// Check if the bus is idle
		while(I2C_Get_FlagStatus(I2Cx, BUS_BUSY));
	}

	/* Write start condition */
	/*
	 *	Bit 8 START: Start generation
		This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
		In Master Mode:
		0: No Start generation
		1: Repeated start generation
		In Slave mode:
		0: No Start generation
		1: Start generation when the bus is free
	 */
	if(State != Disable)
	{
		// Generate a START condition
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		// Disable the START condition generation
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}

}

static void I2C_Send_Address(I2C_t *I2Cx, uint16_t Device_Address,I2C_Direction Direction)
{
	// Support 7-bit address mode only
	if(Direction == Receiver)
	{
		// Set the address bit 0 for read
		I2Cx->DR = ((Device_Address << 1) | (0x01));
	}
	else if(Direction == Transmitter)
	{
		// Reset the address bit 0 for write
		I2Cx->DR = (Device_Address << 1);
	}
}

static void I2C_Stop(I2C_t *I2Cx, Functional_State State)
{
	if(State == Enable)
	{
		// Generate a stop condition, Enable stop bit
		I2Cx->CR1 |= (I2C_CR1_STOP);
	}
	else
	{
		// Disable the stop condition generation, Disable stop bit
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}
}

static void I2C_ACK(I2C_t *I2Cx, Functional_State State)
{
	if(State == Enable)
	{
		// Enable Automatic ACK
		I2Cx->CR1 |= (I2C_CR1_ACK);
	}
	else
	{
		// Disable Automatic ACK
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}


void I2C1_EV_IRQHandler(void)
{
	volatile uint32_t dummy_read = 0 ;
	I2C_t* I2Cx = I2C1 ;
	//Interrupt handling for both master and slave mode of a device
	uint32_t temp1, temp2, temp3;

	temp1   = I2Cx->CR2 & (  I2C_CR2_ITEVTEN) ;
	temp2   = I2Cx->CR2 & ( I2C_CR2_ITBUFEN) ;
	temp3  = I2Cx->SR1 & ( I2C_SR1_STOPF);


	// Handle For interrupt generated by STOPF event
	// Note : Stop detection flag is applicable only slave mode
	if(temp1 && temp3)
	{
		//STOF flag is set
		//Clear the STOPF ( i.e 1) read SR1 2) Write to CR1 )
		I2Cx->CR1 |= 0x0000;
		Slave_States(I2Cx,I2C_EV_STOP);


	}
	//----------------------------------------------------------
	temp3  = I2Cx->SR1 & (I2C_SR1_ADDR);
	// Handle For interrupt generated by ADDR event
	//Note : When master mode : Address is sent
	//		 When Slave mode   : Address matched with own address
	if(temp1 && temp3)
	{
		// interrupt is generated because of ADDR event
		//check for device mode
		if(I2Cx->SR2 & ( I2C_SR2_MSL))
		{
			//master

		}else
		{
			//slave mode
			//clear the ADDR flag ( read SR1 , read SR2)
			dummy_read = I2Cx->SR1;
			dummy_read = I2Cx->SR2;
			Slave_States(I2Cx,I2C_EV_ADD_MATCHED);

		}
	}
	//----------------------------------------------------------

	temp3  = I2Cx->SR1 & ( I2C_SR1_TXE);
	// Handle For interrupt generated by TXE event
	if(temp1 && temp2 && temp3)
	{
		//Check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}else
		{
			//slave
			Slave_States(I2Cx,I2C_EV_DATA_REQ);
		}
	}

	//----------------------------------------------------------

	temp3  = I2Cx->SR1 & ( I2C_SR1_RXNE);
	// Handle For interrupt generated by 	SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	if(temp1 && temp2 && temp3)
	{
		//check device mode .
		if(I2Cx->SR2 & ( I2C_SR2_MSL))
		{
			//The device is master

		}else
		{
			//slave
			Slave_States(I2Cx,I2C_EV_DATA_RCV);

		}
	}
}
static void Slave_States (I2C_t* I2Cx  ,Slave_State state)
{
	uint8_t index =    I2Cx == I2C1 ? 0: 1 ;

	switch (state)
	{
	case I2C_EV_STOP:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( I2C_SR2_TRA))
		{
			//Notify APP that the Stop Condition is sent by the master
			Global_I2C_Config [index].Slave_CallBack (I2C_EV_STOP) ;
		}

		break ;
	}

	case I2C_EV_ADD_MATCHED:
	{
		//Notify APP that the Stop Condition is sent by the master
		Global_I2C_Config [index].Slave_CallBack (I2C_EV_ADD_MATCHED) ;

		break ;
	}

	case I2C_EV_DATA_REQ:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( I2C_SR2_TRA))
		{
			//the APP layer should send the data (MCAL_I2C_SlaveSendData ) in this state
			Global_I2C_Config [index].Slave_CallBack (I2C_EV_DATA_REQ) ;
		}

		break ;
	}
	case I2C_EV_DATA_RCV:
	{
		//make sure that the slave is really in receiver mode
		if(!(I2Cx->SR2 & ( I2C_SR2_TRA)))
		{
			//the APP layer should read the data (MCAL_I2C_SlaveReceiveData ) in this state
			Global_I2C_Config [index].Slave_CallBack (I2C_EV_DATA_RCV) ;
		}

		break ;
	}
	}
}
void I2C1_ER_IRQHandler(void)
{

}

