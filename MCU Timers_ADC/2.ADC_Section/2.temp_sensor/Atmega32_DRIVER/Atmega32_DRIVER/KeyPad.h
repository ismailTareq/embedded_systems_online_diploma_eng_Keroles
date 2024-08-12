/*
 * KeyPad.h
 *
 * Created: 7/4/2024 6:16:29 PM
 *  Author: ismail
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
//Includes
#include "DIO.h"

#define  ROWS		4
#define  COLUMNS	4
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	Pin_Config row_pins[ROWS];
	Pin_Config column_pins[COLUMNS];
}keypad_t;

//---------------------------------------
//API

//Initialize keypad
ReturnType KeyPad_Init(keypad_t *keypad);
//read the pressed value
ReturnType get_key_pressed(keypad_t *keypad,unsigned char *value);


#endif /* KEYPAD_H_ */