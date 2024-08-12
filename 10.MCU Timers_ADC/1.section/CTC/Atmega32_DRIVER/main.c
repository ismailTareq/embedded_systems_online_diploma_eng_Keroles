/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 
#define F_CPU 8000000UL
#include "Timer0.h"
#include "LED.h"

unsigned char tick ;
unsigned char count;
Timer0_Config_t timer0 = {
	.Mode = TMR0_CTC,
	.PreScaler = TMR0PRESCALING_CLK8,
	.OC0Mode_CTC = TMR0_OC0Disabled,
	.TCNT0_Value = 0
};
void display(uint8_t value)
{
	switch (value)
	{
		case 0:
		gpio_port_write_logic(PORTA_INDEX,0x7F);
		break;
		case 1:
		gpio_port_write_logic(PORTA_INDEX,0x0D);
		break;
		case 2:
		gpio_port_write_logic(PORTA_INDEX,0xB7);
		break;
		case 3:
		gpio_port_write_logic(PORTA_INDEX,0x9F);
		break;
		case 4:
		gpio_port_write_logic(PORTA_INDEX,0xCD);
		break;
		case 5:
		gpio_port_write_logic(PORTA_INDEX,0xDB);
		break;
		case 6:
		gpio_port_write_logic(PORTA_INDEX,0xFB);
		break;
		case 7:
		gpio_port_write_logic(PORTA_INDEX,0x0F);
		break;
		case 8:
		gpio_port_write_logic(PORTA_INDEX,0xFF);
		break;
		case 9:
		gpio_port_write_logic(PORTA_INDEX,0xDF);
		break;
	}
}
led_t led = {.port_name = PORTC_INDEX, .pin = DIO_PIN0, .led_status = DIO_LOW};
void CTC_callback()
{
	tick++;
	if(tick == 250)
	{
		count++;
		if(count == 10)
		{
			count =0;
		}
		display(count);
		led_toggle(&led);
		tick = 0;
	}
	
}
void Timer0_CTC(void)
{
	TIMER0SetCompareMatch(240);
	TIMER0_Init(&timer0);
	//TIMER0_Blocking(&timer0);
	TIMER0_Enable_Interrupt(&timer0,CTC_callback);
}


int main(void)
{	gpio_port_direction_intialize(PORTA_INDEX, 0xFE);
	gpio_port_write_logic(PORTA_INDEX,0x7F);
	led_initialize(&led);
	Timer0_CTC();
	while(1)
	{
		
	}
}