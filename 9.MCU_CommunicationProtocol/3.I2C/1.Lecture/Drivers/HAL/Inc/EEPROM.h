/*
 * EEPROM.h
 *
 *  Created on: Aug 8, 2024
 *      Author: ismail
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_
#include "I2C.h"
/*
 * EEPROM is an I2C Slave
 *
 * Idle Mode ================> The device is in high-Impedane state and waits for data.
 * Master Transmitter Mode ==> The device transmits data to a slave receiver.
 * Master Receiver Mode =====> The device receives data form a slave transmitter.
 */

#define EEPROM_Slave_Address 		0x2A


void EEPROM_Init(void);

uint8_t EEPROM_Write_NBytes(uint32_t Memory_Address, uint8_t *Byte, uint32_t Data_Length);
uint8_t EEPROM_Read_NBytes(uint32_t Memory_Address, uint8_t *Byte, uint32_t Data_Length);
#endif /* INC_EEPROM_H_ */
