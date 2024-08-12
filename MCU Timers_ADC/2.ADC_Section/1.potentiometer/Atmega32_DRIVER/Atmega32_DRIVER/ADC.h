/*
 * ADC.h
 *
 * Created: 8/12/2024 10:03:02 PM
 *  Author: ismail
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "ATMEGA32_REGISTERS.h"
#include "Global_Interrupt.h"

typedef enum
{
	ADC_CHANNEL0,   /* ADC channel 0 */
	ADC_CHANNEL1,   /* ADC channel 1 */
	ADC_CHANNEL2,   /* ADC channel 2 */
	ADC_CHANNEL3,   /* ADC channel 3 */
	ADC_CHANNEL4,   /* ADC channel 4 */
	ADC_CHANNEL5,   /* ADC channel 5 */
	ADC_CHANNEL6,   /* ADC channel 6 */
	ADC_CHANNEL7    /* ADC channel 7 */
}ADC_Index;

typedef enum
{
	ADC_CLK2_,         /* Clock / 2 */
	ADC_CLK2,          /* Clock / 2 */
	ADC_CLK4,          /* Clock / 4 */
	ADC_CLK8,          /* Clock / 8 */
	ADC_CLK16,         /* Clock / 16 */
	ADC_CLK32,         /* Clock / 32 */
	ADC_CLK64,         /* Clock / 64 */
	ADC_CLK128         /* Clock / 128 */
}ADC_Prescaller;

typedef enum
{
	Right_Adjusted, /* Right-adjusted result */
	Left_Adjusted   /* Left-adjusted result */
}ADC_ResultAdjust;

typedef enum
{
	ADCInterruptDisabled,  /* Interrupt disabled */
	ADCInterruptEnabled    /* Interrupt enabled */
}ADC_Interrupt;

typedef enum
{
	External_AREF,      /* External AREF voltage reference */
	External_AVCC,      /* External AVCC voltage reference */
	Internal_VREF = 3   /* Internal VREF voltage reference */
}ADC_VoltageReference;

//ADC Multiplixer options
typedef struct
{
	uint8_t MUX_bits  :5;
	uint8_t ADLAR_bit :1;
	uint8_t REFS_bits :2;
}ADMUX_t;

//ADC ADCSRA options
typedef struct
{
	uint8_t ADPS_bits :3;
	uint8_t ADIE_bit  :1;
	uint8_t ADIF_bit  :1;
	uint8_t ADATE_bit :1;
	uint8_t ADSC_bit  :1;
	uint8_t ADEN_bit  :1;
}ADCSRA_t;

typedef struct
{
	ADC_ResultAdjust      ResultAdjust;        /* ADC result adjustment */
	ADC_Prescaller        Prescaler;          /* ADC prescaler */
	ADC_VoltageReference  VoltageReference;    /* ADC voltage reference */
	ADC_Interrupt         InturruptMode;       /* ADC interrupt mode */
	ADCSRA_t              ADCSRA_Bits;         /* ADC ADCSRA Bits */
	ADMUX_t               ADMUX_Bits;          /* ADC multiplixer Bits */
}ADC_Config_t;

/* Initialize ADC module */
ReturnType ADC_Init(ADC_Config_t *ADC_Num);

/* Read from ADC module */
ReturnType ADC_Read(ADC_Index ADC_CH, uint16_t *ADC_Result);

#endif /* ADC_H_ */