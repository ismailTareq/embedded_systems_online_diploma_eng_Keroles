/*
 * Timer0.h
 *
 * Created: 8/11/2024 11:54:57 PM
 *  Author: ismail
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
#include "Global_Interrupt.h"
#include "ATMEGA32_REGISTERS.h"

typedef void(*Timer0callback)(void);

typedef enum
{
	TMR0_Normal,
	TMR0_PhaseCorrectPWM,
	TMR0_CTC,
	TMR0_FastPWM
	
}Timer0_Modes_t;

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
	TMR0_OC0Disabled,
	TMR0_OC0ToggleOnCompareMatch,
	TMR0_OC0ClearOnCompareMatch,
	TMR0_OC0SetOnCompareMatch
	
}CTC_Modes_t;

typedef enum
{
	TMR0_OC0Disabled_PWM,
	RESERVED,
	TMR0_OC0ClearOnCompareMatch_NONINVERTED,
	TMR0_OC0SetOnCompareMatch_INVERTED
	
}PWM_Modes_t;

typedef struct
{
	Timer0_Modes_t Mode;
	Timer0_Clock_t PreScaler;
	CTC_Modes_t   OC0Mode_CTC;
	PWM_Modes_t   OC0Mode_PWM;
	uint8_t TCNT0_Value;
}Timer0_Config_t;

/******************************************************************************
*									APIS				                      *
*******************************************************************************/
ReturnType TIMER0_Init(const Timer0_Config_t* timer0);
ReturnType TIMER0_Deinit();
ReturnType TIMER0_Enable_Interrupt(const Timer0_Config_t* timer0,Timer0callback CallBack);
ReturnType TIMER0_Blocking(const Timer0_Config_t* timer0);
void TIMER0SetCompareMatch(uint8_t OCR0_Value);
void TIMER0Set_PWM(uint8_t PWM_Value);

#endif /* TIMER0_H_ */