/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 
#define F_CPU 8000000UL
#include "ADC.h"
#include "LCD.h"
#define F_CPU 8000000UL
#include "ADC.h"
#include "LCD.h"
LCD_8bit_t LCD1 = {
	.RS.port = PORTA_INDEX,
	.RS.pin = DIO_PIN1,
	.RS.direction = DIO_DIRECTION_OUTPUT,
	.RS.logic = DIO_LOW,
	.EN.port = PORTA_INDEX,
	.EN.pin = DIO_PIN2,
	.EN.direction = DIO_DIRECTION_OUTPUT,
	.EN.logic = DIO_LOW,
	.DATA[0].port = PORTA_INDEX,
	.DATA[0].pin = DIO_PIN3,
	.DATA[0].direction = DIO_DIRECTION_OUTPUT,
	.DATA[0].logic = DIO_LOW,
	.DATA[1].port = PORTA_INDEX,
	.DATA[1].pin = DIO_PIN4,
	.DATA[1].direction = DIO_DIRECTION_OUTPUT,
	.DATA[1].logic = DIO_LOW,
	.DATA[2].port = PORTA_INDEX,
	.DATA[2].pin = DIO_PIN5,
	.DATA[2].direction = DIO_DIRECTION_OUTPUT,
	.DATA[2].logic = DIO_LOW,
	.DATA[3].port = PORTA_INDEX,
	.DATA[3].pin = DIO_PIN6,
	.DATA[3].direction = DIO_DIRECTION_OUTPUT,
	.DATA[3].logic = DIO_LOW,
};
ADC_Config_t ADC1;
uint16_t res_value;
uint8_t buff[16];
int main(void)
{
	
	
	ADC1.VoltageReference = External_AVCC;
	ADC1.InturruptMode = ADCInterruptDisabled;
	ADC1.Prescaler = ADC_CLK128;
	ADC1.ResultAdjust = Right_Adjusted;
	
	ADC_Init(&ADC1);
	LCD_4bit_Init(&LCD1);
	LCD_4bit_SendString(&LCD1,"ADC Value = ");
	while(1)
	{
		ADC_Read(ADC_CHANNEL0,&res_value);
		if(res_value>=1000)
		{
			/* String to hold the ascii result */
			From_Short_To_String(res_value,buff);
			LCD_4bit_SendString_Position(&LCD1,buff,2,1);
			//From_Short_To_String(res_value,str)
		}
		else
		{
			From_Short_To_String(res_value,buff);
			LCD_4bit_SendString_Position(&LCD1,buff,2,1);
		}
	}
}