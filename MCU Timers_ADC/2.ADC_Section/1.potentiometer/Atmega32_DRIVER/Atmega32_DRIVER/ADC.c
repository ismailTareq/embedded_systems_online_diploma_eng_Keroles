/*
 * ADC.c
 *
 * Created: 8/12/2024 10:03:11 PM
 *  Author: ismail
 */ 
#include "ADC.h"

static ReturnType ADMUX_Config(ADC_Config_t *ADC_Config);
static ReturnType ADCSRA_Config(ADC_Config_t *ADC_Config);


ReturnType ADC_Init(ADC_Config_t *ADC_Config)
{
	ReturnType ret = E_NOT_OK;
	if (NULL == ADC_Config)
	{
		ret = E_NOT_OK;
	} 
	else
	{
		//Configure ADMUX register
		ret = ADMUX_Config(ADC_Config);
	
		//Configure ADCSRA register
		ret = ADCSRA_Config(ADC_Config);
		
		
		ret = E_OK;
	}
	return ret;
}

ReturnType ADC_Read(ADC_Index ADC_CH, uint16_t *ADC_Result)
{
	ReturnType ret = E_NOT_OK;
	if ((ADC_CH < ADC_CHANNEL0) || (ADC_CH > ADC_CHANNEL7) || (NULL == ADC_Result))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ADMUX |= ADC_CH;
		
		//Start ADC conversion
		SET_BIT(ADCSRA,6);
		
		//if interrupt is Disable use polling
		if(!(ADCSRA & (1<<3)))
		{
			while(!(ADCSRA & (1<<4)));//Wait for conversion to complete
			
			//clear ADIF
			SET_BIT(ADCSRA,4);
		}
		//read ADC
		*ADC_Result = ADCL | ADCH << 8;
		
		ret = E_OK;
	}
	return ret;
}

static ReturnType ADMUX_Config(ADC_Config_t *ADC_Config)
{
	ReturnType ret = E_NOT_OK;
	if (NULL == ADC_Config)
	{
		ret = E_NOT_OK;
	}
	else
	{
		//Set the REFS bits to select the desired voltage reference
		ADC_Config->ADMUX_Bits.REFS_bits = ADC_Config->VoltageReference;
		
		//Set the ADLAR bit to control the result adjustment
		ADC_Config->ADMUX_Bits.ADLAR_bit = ADC_Config->ResultAdjust;
		
		//Set the MUX bits to select the desired ADC channel
		ADC_Config->ADMUX_Bits.MUX_bits = ADC_CHANNEL0;
		
		ADMUX = *(uint8_t*)&ADC_Config->ADMUX_Bits;
		ret = E_OK;
	}
	return ret;
}
static ReturnType ADCSRA_Config(ADC_Config_t *ADC_Config)
{
	ReturnType ret = E_NOT_OK;
	if (NULL == ADC_Config)
	{
		ret = E_NOT_OK;
	}
	else
	{
		//Set the ADPS bits to select the desired ADC prescaler
		ADC_Config->ADCSRA_Bits.ADPS_bits = ADC_Config->Prescaler;
		
		//Set the ADIE bit to control the ADC interrupt enable
		ADC_Config->ADCSRA_Bits.ADIE_bit = ADC_Config->InturruptMode;
		
		//Clear the ADIF bit,Disable auto-trigger mode,Disable ADC conversion
		ADC_Config->ADCSRA_Bits.ADIF_bit = 0;
		ADC_Config->ADCSRA_Bits.ADATE_bit = 0;
		ADC_Config->ADCSRA_Bits.ADSC_bit = 0;
		
		//Enable ADC
		ADC_Config->ADCSRA_Bits.ADEN_bit = 1;
		
		ADCSRA = *(uint8_t*)&ADC_Config->ADCSRA_Bits;
		if(ADCSRA & (1<<3))
		{
			Enable_GI();
		}
		ret = E_OK;
	}
	return ret;
}

ISR(ADC_vect)
{
	SET_BIT(ADCSRA, 4);//clear flag
}