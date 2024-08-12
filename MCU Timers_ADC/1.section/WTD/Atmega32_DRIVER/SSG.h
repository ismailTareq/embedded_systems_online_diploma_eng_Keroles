/*
 * SSG.h
 *
 * Created: 3/25/2024 2:07:53 PM
 *  Author: ismail
 */ 


#ifndef SSG_H_
#define SSG_H_
#include "DIO.h"

typedef enum 
{
	COMMON_ANODE,
	COMMON_CATHODE	
}segment_type_t;

typedef struct
{
	Pin_Config segment_pins[4];
	segment_type_t segment_type;
}segment_config;

ReturnType SSG_intialize(const segment_config *segment);
ReturnType SSG_Write_Number(const segment_config *segment,unsigned char number);
#endif /* SSG_H_ */