/*
 * KPD.H
 *
 *  Created on: Jul 5, 2024
 *      Author: ismail
 */

#ifndef KEYPAD_DRIVER_KPD_H_
#define KEYPAD_DRIVER_KPD_H_
//Includes
#include "STM32F103X6.h"
#include "GPIO.h"
#define KEYPAD_PORT GPIOB

//@ref:keypad_PINS
#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

//initailize the keypad
void Keypad_Init();
//get the pressed button
unsigned char get_pressed_key();
#endif /* KEYPAD_DRIVER_KPD_H_ */
