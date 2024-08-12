/*
 * SSG.c
 *
 * Created: 3/25/2024 2:07:44 PM
 *  Author: ismail
 */ 
#include "SSG.h"
ReturnType SSG_intialize(const segment_config *segment)
{
	ReturnType ret = E_OK;
	unsigned char SSG_counter =0;
	if(NULL == segment)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_intialize(&(segment->segment_pins[0]));
		ret = gpio_pin_intialize(&(segment->segment_pins[1]));
		ret = gpio_pin_intialize(&(segment->segment_pins[2]));
		ret = gpio_pin_intialize(&(segment->segment_pins[3]));
	}
	return ret;
}
ReturnType SSG_Write_Number(const segment_config *segment,unsigned char number)
{
	ReturnType ret = E_OK;
	if((NULL == segment)&&(number>9))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(segment->segment_pins[0]), number & 0x01);
		ret = gpio_pin_write_logic(&(segment->segment_pins[1]), (number>>1) & 0x01);
		ret = gpio_pin_write_logic(&(segment->segment_pins[2]), (number>>2) & 0x01);
		ret = gpio_pin_write_logic(&(segment->segment_pins[3]), (number>>3) & 0x01);

	}
	return ret;
}
