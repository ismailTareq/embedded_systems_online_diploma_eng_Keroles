/*
 * Atmega32_DRIVER.c
 *
 * Created: 7/4/2024 3:47:22 PM
 * Author : ismail
 */ 

#include "DIO.h"
#include "LCD.h"
#include "SPI.h"
#include "LED.h"
#include "Push_Button.h"

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7
SPI_Config_t SPI;
unsigned char ch;

unsigned char data;
void transmit_seg (uint8_t cmd, uint8_t data)
{
	PORTB &= ~(1 << SS);
	
	SPI_SendData(&SPI,cmd);
	
	SPI_SendData(&SPI,data);
	
	PORTB |= (1 << SS);
}
int main(void)
{
	uint8_t counter = 0;
	uint8_t i = 0;
	SPI.SPI_Mode = SPI_MODE_MASTER;
	SPI.SPI_DataOrder = FRAME_FORMAT_MSB_FIRST;
	SPI.SPI_Prescaler = BAUDERATE_PRESCALER_16;
	SPI.SPI_DoupleSpeed = CLK_SPEED_LOW;
	SPI.SPI_phase = CLK_POLARITY_RISING_FALLING;
	SPI.SPI_Polarity = CLK_PHASE_SAMPLE_SETUP;
	SPI.SPI_Interrupt = IRQ_DISABLE;
	SPI_Init(&SPI);
	
	transmit_seg (0x09, 0xFF);
	
	transmit_seg (0x0A, 0xFF);
	
	transmit_seg (0x0B, 0xF7);
	
	transmit_seg (0x0C, 0x01);
	
	while(1)
	{
		for(i = 1;i<9;i++)
		{
			transmit_seg(i,counter++);
			_delay_ms(300);
		}
		for(i = 1;i<9;i++)
		{
			transmit_seg(i,0);
		}
	}
}
/*int main(void)
{
SPI.SPI_Mode = SPI_MODE_MASTER;
SPI.SPI_DataOrder = FRAME_FORMAT_MSB_FIRST;
SPI.SPI_Prescaler = BAUDERATE_PRESCALER_16;
SPI.SPI_DoupleSpeed = CLK_SPEED_LOW;
SPI.SPI_phase = CLK_POLARITY_RISING_FALLING;
SPI.SPI_Polarity = CLK_PHASE_SAMPLE_SETUP;
SPI.SPI_Interrupt = IRQ_DISABLE;
SPI_Init(&SPI);

DDRA = 0xFF;
for (ch = 0; ch <=255; ch++)
{
_delay_ms(1000);
PORTA = SPI_SendData(&SPI,data);
}
}*/

/*int main(void)
{
SPI.SPI_Mode = SPI_MODE_MASTER;
SPI.SPI_DataOrder = FRAME_FORMAT_MSB_FIRST;
SPI.SPI_Prescaler = BAUDERATE_PRESCALER_16;
SPI.SPI_DoupleSpeed = CLK_SPEED_LOW;
SPI.SPI_phase = CLK_POLARITY_RISING_FALLING;
SPI.SPI_Polarity = CLK_PHASE_SAMPLE_SETUP;
SPI.SPI_Interrupt = IRQ_DISABLE;
SPI_Init(&SPI);
DDRA = 0xFF;
for(;ch<=255;ch++)
{
	_delay_ms(1000);
SPI_SendData(&SPI,&ch);
PORTA = ch;
}
}*/
/*
button_t btn_high = {
	.button_pin.port = PORTA_INDEX,
	.button_pin.pin = DIO_PIN0,
	.button_pin.direction = DIO_DIRECTION_INPUT,
	.button_pin.logic = DIO_LOW,
	.button_connection = BUTTON_ACTIVE_HIGH,
	.button_state = BUTTON_RELEASED
};
led_t led1 = {.port_name = PORTC_INDEX, .pin = DIO_PIN0, .led_status = DIO_LOW};

SPI_Config_t SPI;
button_state_t pressed = BUTTON_RELEASED;
int main(void)
{
	button_initialize(&btn_high);
	led_initialize(&led1);
	//gpio_pin_direction_intialize(&(btn_high.button_pin));
	
	while (1)
	{
		button_read_state(&btn_high,&pressed);
		if (pressed == BUTTON_PRESSED)
		{
			SPI_SendData(&SPI,BUTTON_PRESSED);
		}
		else
		{
			SPI_SendData(&SPI,BUTTON_RELEASED);
		}
	}
}
*/
/*
void SPI_MasterInit(void)
{
	SPI_DDR |= (1<<MOSI)|(1<<SCK)|(1<<SS);
	SPI_DDR &= ~(1<<MISO);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
uint8_t SPI_MasterTransmit(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return data;
}
int main(void)
{
	
	SPI_MasterInit();
	uint8_t ch = 0;
	DDRA = 0xFF;
	for(;ch<=255;ch++)
	{
		_delay_ms(1000);
		PORTA = SPI_MasterTransmit(ch);
	}
}*/
/*int main(void)
{
button_initialize(&btn_high);
//led_initialize(&led1);
SPI.SPI_Mode = SPI_MODE_MASTER;
SPI.SPI_DataOrder = FRAME_FORMAT_MSB_FIRST;
SPI.SPI_Prescaler = BAUDERATE_PRESCALER_16;
SPI.SPI_DoupleSpeed = CLK_SPEED_LOW;
SPI.SPI_phase = CLK_POLARITY_RISING_FALLING;
SPI.SPI_Polarity = CLK_PHASE_SAMPLE_SETUP;
SPI.SPI_Interrupt = IRQ_DISABLE;
SPI_Init(&SPI);

while (1)
{
button_read_state(&btn_high,&pressed);
if (pressed == BUTTON_PRESSED)
{
SPI_SendData(&SPI,BUTTON_PRESSED);
}
else
{
SPI_SendData(&SPI,BUTTON_RELEASED);
}
}
}*/