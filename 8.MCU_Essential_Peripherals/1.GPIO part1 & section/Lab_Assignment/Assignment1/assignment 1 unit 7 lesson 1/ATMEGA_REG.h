/*
 * ATMEGA_REG.h
 *
 * Created: 7/1/2024 7:29:09 PM
 *  Author: ismail
 */ 


#ifndef ATMEGA_REG_H_
#define ATMEGA_REG_H_
//Define macros for accessing PORTD, DDRD, and PIND registers

#define PORTD	*((volatile unsigned char *)0x32)
#define DDRD	*((volatile unsigned char *)0x31)
#define PIND	*((volatile unsigned char *)0x30)

#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7
#endif /* ATMEGA_REG_H_ */