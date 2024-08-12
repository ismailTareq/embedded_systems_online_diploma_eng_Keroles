/*
 * PWM0.h
 *
 * Created: 8/12/2024 8:28:49 PM
 *  Author: ismail
 */ 


#ifndef PWM0_H_
#define PWM0_H_
#include "Global_Interrupt.h"
#include "ATMEGA32_REGISTERS.h"

typedef void(*Timer0callback)(void);

typedef enum{
	Fast_PWM=0x40,
	Phase_Correct_PWM=0x08
}PWM_Modes_t;

typedef enum
{
	TOIE_DISABLE = 0x00,
	TOIE_ENABLE = 0x01
}TOIE_t;

typedef enum
{
	OCIE_DISABLE = 0x00,
	OCIE_ENABLE = 0x02
}OCIE_t;

typedef enum
{
	TMR0NO_CLK_SRC,
	TMR0NO_PRESCALING,
	TMR0PRESCALING_CLK8,
	TMR0PRESCALING_CLK64,
	TMR0PRESCALING_CLK256,
	TMR0PRESCALING_CLK1024,
	TMR0EXT_CLK_FALLING,
	TMR0EXT_CLK_RISING
}Timer0_Clock_t;

typedef enum
{
	PWM_INVERTING = 0x30,
	PWM_Non_INVERTING = 0x10
}PWM_INV_t;

typedef struct{
	PWM_Modes_t Mode;
	TOIE_t Overflow;
	OCIE_t Compare;
	Timer0_Clock_t CLK;
	PWM_INV_t Inverting;
}PWM_t;

void PWM0_Init(PWM_t* config);
void PWM0_Stop();

void PWM0_GetCompare(unsigned char* TicksNumber);
void PWM0_SetCompare(uint8_t TicksNumber);

void PWM0_GetCounter(unsigned char* TicksNumber);
void PWM0_SetCounter(uint8_t TicksNumber);

void PWM0_GetOverflow(unsigned char* TicksNumber);
void PWM0_SetOverflow(uint8_t TicksNumber);

void PWM0_CALLBACK_Overflow_INTERRUPT(Timer0callback callback);
void PWM0_CALLBACK_CompareMatch_INTERRUPT(Timer0callback callback);

#endif /* PWM0_H_ */