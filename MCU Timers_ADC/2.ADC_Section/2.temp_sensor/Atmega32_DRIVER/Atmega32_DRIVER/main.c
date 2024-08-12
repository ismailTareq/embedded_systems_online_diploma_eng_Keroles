/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 
#define F_CPU 8000000UL
#include "ADC.h"
#include "LCD.h"
LCD_8bit_t LCD1 = {
	.RS.port = PORTD_INDEX,
	.RS.pin = DIO_PIN4,
	.RS.direction = DIO_DIRECTION_OUTPUT,
	.RS.logic = DIO_LOW,
	.EN.port = PORTD_INDEX,
	.EN.pin = DIO_PIN5,
	.EN.direction = DIO_DIRECTION_OUTPUT,
	.EN.logic = DIO_LOW,
	.DATA[0].port = PORTC_INDEX,
	.DATA[0].pin = DIO_PIN0,
	.DATA[0].direction = DIO_DIRECTION_OUTPUT,
	.DATA[0].logic = DIO_LOW,
	.DATA[1].port = PORTC_INDEX,
	.DATA[1].pin = DIO_PIN1,
	.DATA[1].direction = DIO_DIRECTION_OUTPUT,
	.DATA[1].logic = DIO_LOW,
	.DATA[2].port = PORTC_INDEX,
	.DATA[2].pin = DIO_PIN2,
	.DATA[2].direction = DIO_DIRECTION_OUTPUT,
	.DATA[2].logic = DIO_LOW,
	.DATA[3].port = PORTC_INDEX,
	.DATA[3].pin = DIO_PIN3,
	.DATA[3].direction = DIO_DIRECTION_OUTPUT,
	.DATA[3].logic = DIO_LOW,
	.DATA[3].logic = DIO_LOW,
	.DATA[4].port = PORTC_INDEX,
	.DATA[4].pin = DIO_PIN4,
	.DATA[4].direction = DIO_DIRECTION_OUTPUT,
	.DATA[4].logic = DIO_LOW,
	.DATA[5].port = PORTC_INDEX,
	.DATA[5].pin = DIO_PIN5,
	.DATA[5].direction = DIO_DIRECTION_OUTPUT,
	.DATA[5].logic = DIO_LOW,
	.DATA[6].port = PORTC_INDEX,
	.DATA[6].pin = DIO_PIN6,
	.DATA[6].direction = DIO_DIRECTION_OUTPUT,
	.DATA[6].logic = DIO_LOW,
	.DATA[7].port = PORTC_INDEX,
	.DATA[7].pin = DIO_PIN7,
	.DATA[7].direction = DIO_DIRECTION_OUTPUT,
	.DATA[7].logic = DIO_LOW,
};
uint8_t LM35_getTemperature(void)
{
	uint8_t temp_value = 0;

	uint16_t adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	ADC_Read(ADC_CHANNEL2,&adc_value);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8_t)(((uint32_t)adc_value*150*5)/(1023*1.5));

	return temp_value;
}
ADC_Config_t ADC1;
uint16_t res_value;
uint8_t buff[16];
int main(void)
{	
	
	
	ADC1.VoltageReference = External_AVCC;
	ADC1.InturruptMode = ADCInterruptEnabled;
	ADC1.Prescaler = ADC_CLK8;
	ADC1.ResultAdjust = Right_Adjusted;
	
	ADC_Init(&ADC1);
	LCD_8bit_Init(&LCD1);
	LCD_8bit_SendString(&LCD1,"temperature = ");
	while(1)
	{
		res_value = LM35_getTemperature();
		if(res_value>=100)
		{
			 
			From_Short_To_String(res_value,buff);
			LCD_8bit_SendString_Position(&LCD1,buff,2,1);
			
		}
		else
		{
			From_Short_To_String(res_value,buff);
			LCD_8bit_SendString_Position(&LCD1,buff,2,1);
		}
	}
}