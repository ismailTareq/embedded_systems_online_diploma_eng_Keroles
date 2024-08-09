/*
 * External_Interrupt.c
 *
 * Created: 7/31/2024 3:13:26 PM
 *  Author: ismail
 */ 
#include "External_Interrupt.h"

void (*EXTI0_CallBack)(void);
void (*EXTI1_CallBack)(void);
void (*EXTI2_CallBack)(void);

void EXTI_Init(EXTIPIN Interrupt, EXTI_Trigger interruptTriggerEdge, void (*ExtIntCallback)(void))
{
	switch(Interrupt)
	{
		case EXTI_0:
		if(EXTI_RISING_EDGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
		}
		else if(EXTI_FALLING_EDGE == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
		}
		else if(EXTI_LOW_LEVEL == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
		}
		else if(EXTI_LOGICAL_CHANGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,0);
			CLR_BIT(MCUCR,1);
		}
		EXTI0_CallBack = ExtIntCallback;
		break;
		case EXTI_1:
		if(EXTI_RISING_EDGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(EXTI_FALLING_EDGE == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,2);
			SET_BIT(MCUCR,3);
		}
		else if(EXTI_LOW_LEVEL == interruptTriggerEdge)
		{
			CLR_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		else if(EXTI_LOGICAL_CHANGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCR,2);
			CLR_BIT(MCUCR,3);
		}
		EXTI1_CallBack = ExtIntCallback;
		break;
		
		case EXTI_2:
		if(EXTI_RISING_EDGE == interruptTriggerEdge)
		{
			SET_BIT(MCUCSR,6);
		}
		else if(EXTI_FALLING_EDGE == interruptTriggerEdge)
		{
			CLR_BIT(MCUCSR,6);
		}
		EXTI2_CallBack = ExtIntCallback;
		break;
	}
}

void EXTI_Enable(EXTIPIN Interrupt)
{
	switch(Interrupt)
	{
		case EXTI_0:
		SET_BIT(GICR,6);
		break;
		case EXTI_1:
		SET_BIT(GICR,7);
		break;
		case EXTI_2:
		SET_BIT(GICR,5);
		break;
	}
	Enable_GI();
}
void EXTI_Disable(EXTIPIN Interrupt)
{
	switch(Interrupt)
	{
		case EXTI_0:
		CLR_BIT(GICR,6);
		break;
		case EXTI_1:
		CLR_BIT(GICR,7);
		break;
		case EXTI_2:
		CLR_BIT(GICR,5);
		break;
	}
}

// Interrupt service routine for INT0
ISR (INT0_vect)
{
	if (EXTI0_CallBack != NULL)
	{
		EXTI0_CallBack();
	}
}
// Interrupt service routine for INT1
ISR (INT1_vect)
{
	if (EXTI1_CallBack != NULL)
	{
		EXTI1_CallBack();
	}
}

// Interrupt service routine for INT2
ISR (INT2_vect)
{
	if (EXTI2_CallBack != NULL)
	{
		EXTI2_CallBack();
	}
}