/*
 * ATMEGA32_REGISTERS.h
 *
 * Created: 7/4/2024 4:03:35 PM
 *  Author: ismail
 */ 


#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_
//Includes
#include <stdio.h>
#include <stdint.h>
//---------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
/* PORTA */
#define DDRA   *(volatile unsigned int *)(0x3A)
#define PORTA  *(volatile unsigned int *)(0x3B)
#define PINA   *(volatile unsigned int *)(0x39)
/* PORTB */
#define DDRB   *(volatile unsigned int *)(0x37)
#define PORTB  *(volatile unsigned int *)(0x38)
#define PINB   *(volatile unsigned int *)(0x36)
/* PORTC */
#define DDRC   *(volatile unsigned int *)(0x34)
#define PORTC  *(volatile unsigned int *)(0x35)
#define PINC   *(volatile unsigned int *)(0x33)
/* PORTD */
#define DDRD   *(volatile unsigned int *)(0x31)
#define PORTD  *(volatile unsigned int *)(0x32)
#define PIND   *(volatile unsigned int *)(0x30)

//---------------------------------------

#endif /* ATMEGA32_REGISTERS_H_ */