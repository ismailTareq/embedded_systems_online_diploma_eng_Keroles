/*
 * Global_Interrupt.h
 *
 * Created: 7/31/2024 3:12:54 PM
 *  Author: ismail
 */ 


#ifndef GLOBAL_INTERRUPT_H_
#define GLOBAL_INTERRUPT_H_
#include "ATMEGA32_REGISTERS.h"
#include "Macros.h"
#include <avr/interrupt.h>

void Enable_GI(void);
void Disable_GI(void);

#endif /* GLOBAL_INTERRUPT_H_ */