/*
 * LED.h
 *
 * Created: 3/19/2024 3:07:19 PM
 *  Author: ismail
 */ 


#ifndef LED_H_
#define LED_H_
#include "DIO.h"
typedef enum{
	LED_OFF,
	LED_ON
}led_status_t;

typedef struct{
	unsigned char port_name : 3;
	unsigned char pin : 3;
	unsigned char led_status : 1;
}led_t;

ReturnType led_initialize(const led_t *led);
ReturnType led_turn_on(const led_t *led);
ReturnType led_turn_off(const led_t *led);
ReturnType led_toggle(const led_t *led);


#endif /* LED_H_ */