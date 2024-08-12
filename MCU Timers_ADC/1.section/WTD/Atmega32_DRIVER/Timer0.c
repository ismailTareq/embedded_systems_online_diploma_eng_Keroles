/*
 * Timer0.c
 *
 * Created: 8/11/2024 11:54:42 PM
 *  Author: ismail
 */ 
#include "Timer0.h"

Timer0callback CALLBACK_OVER_FLOW;
Timer0callback CALLBACK_COMPARE;

static inline void TIMER0_prescaler_Setup(const Timer0_Config_t* timer0);
static inline void TIMER0_MODE_Setup(const Timer0_Config_t* timer0);
static inline void TIMER0_OC0_Setup(const Timer0_Config_t* timer0);

ReturnType TIMER0_Init(const Timer0_Config_t* timer0)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == timer0)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TCNT0 = timer0->TCNT0_Value;
		TIMER0_MODE_Setup(timer0);
		TIMER0_OC0_Setup(timer0);
		TIMER0_prescaler_Setup(timer0);
		
		ret = E_OK;
	}
	return ret;
}

ReturnType TIMER0_Enable_Interrupt(const Timer0_Config_t* timer0,Timer0callback CallBack)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == timer0)
	{
		ret = E_NOT_OK;
	}
	else
	{
		Enable_GI();
		if(timer0->Mode == TMR0_Normal)
		{
			SET_BIT(TIMSK,0);//overflow
			CALLBACK_OVER_FLOW = CallBack;
		}
		if(timer0->Mode == TMR0_CTC)
		{
			SET_BIT(TIMSK,1);//CTC
			CALLBACK_COMPARE = CallBack;
		}
		ret = E_OK;
	}
	return ret;
}
ReturnType TIMER0_Blocking(const Timer0_Config_t* timer0)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == timer0)
	{
		ret = E_NOT_OK;
	}
	else 
	{
		while(!(TIFR & 1<<0));
		SET_BIT(TIFR,0);//clear bit
		ret = E_OK;
	}
	return ret;
}
void TIMER0SetCompareMatch(uint8_t OCR0_Value)
{
	OCR0 =  OCR0_Value;
}
void TIMER0Set_PWM(uint8_t PWM_Value)
{
	OCR0 = PWM_Value;
}

static inline void TIMER0_prescaler_Setup(const Timer0_Config_t* timer0)
{
	if(timer0->PreScaler == TMR0NO_CLK_SRC)
	{
		CLR_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
	}
	else if(timer0->PreScaler == TMR0NO_PRESCALING)
	{
		SET_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
	}
	else if (timer0->PreScaler == TMR0PRESCALING_CLK8)
	{
		CLR_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
	}
	else if (timer0->PreScaler == TMR0PRESCALING_CLK64)
	{
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		CLR_BIT(TCCR0,2);
	}
	else if (timer0->PreScaler == TMR0PRESCALING_CLK256)
	{
		CLR_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
	}
	else if (timer0->PreScaler == TMR0PRESCALING_CLK1024)
	{
		SET_BIT(TCCR0,0);
		CLR_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
	}
	else if (timer0->PreScaler == TMR0EXT_CLK_FALLING)
	{
		CLR_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
	}
	else if (timer0->PreScaler == TMR0EXT_CLK_RISING)
	{
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		SET_BIT(TCCR0,2);
	}
}
static inline void TIMER0_MODE_Setup(const Timer0_Config_t* timer0)
{
	if(timer0->Mode == TMR0_Normal)
	{
		SET_BIT(TCCR0,7);//for non PWM mode
		
		CLR_BIT(TCCR0,6);//Activate normal (overflow)
		CLR_BIT(TCCR0,3);
		
		CLR_BIT(TCCR0,5);//disconnect OC0
		CLR_BIT(TCCR0,4);
		
		//GIE_Enable();
		//SET_BIT(TIMSK,0);//enable interrupt
	}
	else if (timer0->Mode == TMR0_CTC)
	{
		SET_BIT(TCCR0,7);//for non PWM mode
		
		CLR_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);//Activate CTC
		
		CLR_BIT(TCCR0,5);//disconnect OC0
		CLR_BIT(TCCR0,4);
	}
	else if (timer0->Mode == TMR0_FastPWM)
	{
		CLR_BIT(TCCR0,7);//for PWM mode
		
		SET_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);//Activate PWM
		
		CLR_BIT(TCCR0,5);//disconnect OC0
		CLR_BIT(TCCR0,4);
	}
}
static inline void TIMER0_OC0_Setup(const Timer0_Config_t* timer0)
{
	if (timer0->Mode == TMR0_CTC)
	{
		if(timer0->OC0Mode_CTC == TMR0_OC0Disabled)
		{
			CLR_BIT(TCCR0,5);
			CLR_BIT(TCCR0,4);
		}
		else if (timer0->OC0Mode_CTC == TMR0_OC0ToggleOnCompareMatch)
		{
			CLR_BIT(TCCR0,5);
			SET_BIT(TCCR0,4);
		}
		else if (timer0->OC0Mode_CTC == TMR0_OC0ClearOnCompareMatch)
		{
			SET_BIT(TCCR0,5);
			CLR_BIT(TCCR0,4);
		}
		else if (timer0->OC0Mode_CTC == TMR0_OC0SetOnCompareMatch)
		{
			SET_BIT(TCCR0,5);
			SET_BIT(TCCR0,4);
		}
	}
	else if(timer0->Mode == TMR0_FastPWM)
	{
		if(timer0->OC0Mode_PWM == TMR0_OC0Disabled)
		{
			CLR_BIT(TCCR0,5);
			CLR_BIT(TCCR0,4);
		}
		else if (timer0->OC0Mode_PWM == RESERVED)
		{
			CLR_BIT(TCCR0,5);
			SET_BIT(TCCR0,4);
		}
		else if (timer0->OC0Mode_PWM == TMR0_OC0ClearOnCompareMatch_NONINVERTED)
		{
			SET_BIT(TCCR0,5);
			CLR_BIT(TCCR0,4);
		}
		else if (timer0->OC0Mode_PWM == TMR0_OC0SetOnCompareMatch_INVERTED)
		{
			SET_BIT(TCCR0,5);
			SET_BIT(TCCR0,4);
		}
	}
}
/*
ISR(TIMER0_COMP_vect)
{
	CALLBACK_COMPARE();
}

ISR(TIMER0_OVF_vect)
{
	CALLBACK_OVER_FLOW();
}*/