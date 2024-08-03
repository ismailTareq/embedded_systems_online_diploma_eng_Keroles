/*
 * External_Interrupt.h
 *
 * Created: 7/31/2024 3:13:18 PM
 *  Author: ismail
 */ 


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_
#include "ATMEGA32_REGISTERS.h"
#include "Macros.h"
#include "Global_Interrupt.h"

typedef enum {
	EXTI_0,
	EXTI_1,
	EXTI_2
}EXTIPIN;

typedef enum {
	EXTI_LOW_LEVEL,
	EXTI_LOGICAL_CHANGE,
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE
} EXTI_Trigger;


void EXTI_Init(EXTIPIN Interrupt, EXTI_Trigger ExtIntMode, void (*ExtIntCallback)(void));
void EXTI_Enable(EXTIPIN Interrupt);
void EXTI_Disable(EXTIPIN Interrupt);


#endif /* EXTERNAL_INTERRUPT_H_ */