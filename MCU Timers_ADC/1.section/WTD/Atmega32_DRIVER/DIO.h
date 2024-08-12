/*
 * DIO.h
 *
 * Created: 7/4/2024 3:50:37 PM
 *  Author: ismail
 */ 


#ifndef DIO_H_
#define DIO_H_
//Includes
#include "ATMEGA32_REGISTERS.h"
#include "Macros.h"
#define F_CPU 1000000UL
#include "util/delay.h"
#define PORT_PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER      4
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
//@ref GPIO_PIN_STATE
typedef enum {
	DIO_LOW,
	DIO_HIGH
}Logic;
//@ref GPIO_PIN_MODE_STATE
typedef enum {
	DIO_DIRECTION_OUTPUT,
	DIO_DIRECTION_INPUT
}Direction;
//@ref GPIO_PIN_DEFINE
typedef enum{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}Pin_Index;
//@ref GPIO_PORT_STATE
typedef enum{
	PORTA_INDEX,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX,
}Port_Index;

typedef struct{
	unsigned char port		  :3;
	unsigned char pin		  :3;
	unsigned char direction   :1;
	unsigned char logic		  :1;
}Pin_Config;

//---------------------------------------
//API
//Initialize and DeInitialize GPIO
ReturnType gpio_pin_direction_intialize(const Pin_Config *pin_config);
ReturnType gpio_pin_get_direction_status(const Pin_Config *pin_config, Direction *direction_status);
ReturnType gpio_port_direction_intialize(Port_Index port, unsigned char direction);
ReturnType gpio_port_get_direction_status(Port_Index port, unsigned char *direction_status);
//WRITE PIN or PORT
ReturnType gpio_pin_write_logic(const Pin_Config *pin_config, Logic logic);
ReturnType gpio_port_write_logic(Port_Index port, unsigned char logic);
//READ PIN or PORT
ReturnType gpio_pin_read_logic(const Pin_Config *pin_config, Logic *logic);
ReturnType gpio_port_read_logic(Port_Index port, unsigned char *logic);
//TOGGLE PIN or PORT
ReturnType gpio_pin_toggle_logic(const Pin_Config *pin_config);
ReturnType gpio_port_toggle_logic(Port_Index port);
//Initialize and WRITE on pin
ReturnType gpio_pin_intialize(const Pin_Config *pin_config);





#endif /* DIO_H_ */