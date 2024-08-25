/*
 * LCD.h
 *
 *  Created on: Jul 10, 2024
 *      Author: ismail
 */

#ifndef LCD_DRIVER_LCD_H_
#define LCD_DRIVER_LCD_H_
//Includes
#include "STM32F103X6.h"
#include "GPIO.h"
#define LCD_PORT	GPIOA

//---------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//macros:
//-*-*-*-*-*-*-*-*-*-*-*
//LCD Commands
#define LCD_CLEAR								0X01
#define LCD_RETURN_HOME							0x02
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF			0x04
#define LCD_ENTRY_MODE_DEC_SHIFT_ON				0x05
#define LCD_ENTRY_MODE_INC_SHIFT_OFF			0x06
#define LCD_ENTRY_MODE_INC_SHIFT_ON				0x07
#define LCD_CURSOR_MOVE_SHIFT_LEFT				0x10
#define LCD_CURSOR_MOVE_SHIFT_RIGHT				0x14
#define LCD_DISPLAY_SHIFT_LEFT					0x18
#define LCD_DISPLAY_SHIFT_RIGHT					0x1C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define LCD_8BIT_MODE_2_LINE					0x38
#define LCD_4BIT_MODE_2_LINE					0x28

#define LCD_CGRAM_START                0x40
#define LCD_DDRAM_START                0x80

//DATA Pins
#define LCD_D0_PIN	GPIO_PIN_0
#define LCD_D1_PIN	GPIO_PIN_1
#define LCD_D2_PIN	GPIO_PIN_2
#define LCD_D3_PIN	GPIO_PIN_3
#define LCD_D4_PIN	GPIO_PIN_4
#define LCD_D5_PIN	GPIO_PIN_5
#define LCD_D6_PIN	GPIO_PIN_6
#define LCD_D7_PIN	GPIO_PIN_7
/*note: if using 4bit mode use D4->D7 only*/

//Control Pins
#define RS			GPIO_PIN_8
#define RW			GPIO_PIN_9
#define EN			GPIO_PIN_10
//R/W will be 0 so we connect it to the GND if only u don't need to read from LCD

//---------------------------------------
//API
void LCD_INIT();
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_DATA(unsigned char DATA);
void LCD_WRITE_STRING(char* string);
void LCDisbusy(void);
void LCD_clearscreen();
void LCD_GOTO_XY(unsigned char row, unsigned char column);
#endif /* LCD_DRIVER_LCD_H_ */
