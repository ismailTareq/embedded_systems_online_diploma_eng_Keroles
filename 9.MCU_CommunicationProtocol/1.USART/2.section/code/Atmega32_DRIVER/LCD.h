/*
 * LCD.h
 *
 * Created: 7/9/2024 11:43:57 AM
 *  Author: ismail
 */ 


#ifndef LCD_H_
#define LCD_H_
//Includes
#include "DIO.h"
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//macros
//-*-*-*-*-*-*-*-*-*-*-*
//@ref LCD_COMMAND
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

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	Pin_Config RS;
	Pin_Config EN;
	Pin_Config DATA[4];
}LCD_4bit_t;

typedef struct
{
	Pin_Config RS;
	Pin_Config EN;
	Pin_Config DATA[8];
}LCD_8bit_t;
//---------------------------------------
//API

//-*-*-*-*-*-*-*-*-*-*-*-
//LCD 4BITS
//-*-*-*-*-*-*-*-*-*-*-*
//---------------------------------------
//Initialize LCD
ReturnType LCD_4bit_Init(LCD_4bit_t *LCD);
//Send commands to the LCD
ReturnType LCD_4bit_SendCommand(LCD_4bit_t *LCD,unsigned char command);
//Send Data to the LCD
ReturnType LCD_4bit_SendData(LCD_4bit_t *LCD,unsigned char data);
//choose the position to display data
ReturnType LCD_4bit_SendData_Position(LCD_4bit_t *LCD,unsigned char data,unsigned char row,unsigned char column);
//send string
ReturnType LCD_4bit_SendString(LCD_4bit_t *LCD,unsigned char *string);
//choose the position to display string
ReturnType LCD_4bit_SendString_Position(LCD_4bit_t *LCD,unsigned char *string,unsigned char row,unsigned char column);
//Custom character 
ReturnType LCD_4bit_SendCustom_Char(LCD_4bit_t *LCD,unsigned char chr[],unsigned char row,unsigned char column,unsigned char mem_pos);
//---------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//LCD 8BITS
//-*-*-*-*-*-*-*-*-*-*-*
//---------------------------------------
//Initialize LCD
ReturnType LCD_8bit_Init(LCD_8bit_t *LCD);
//Send commands to the LCD
ReturnType LCD_8bit_SendCommand(LCD_8bit_t *LCD,unsigned char command);
//Send Data to the LCD
ReturnType LCD_8bit_SendData(LCD_8bit_t *LCD,unsigned char data);
//choose the position to display data
ReturnType LCD_8bit_SendData_Position(LCD_8bit_t *LCD,unsigned char data,unsigned char row,unsigned char column);
//send string
ReturnType LCD_8bit_SendString(LCD_8bit_t *LCD,unsigned char *string);
//choose the position to display string
ReturnType LCD_8bit_SendString_Position(LCD_8bit_t *LCD,unsigned char *string,unsigned char row,unsigned char column);
//Custom character
ReturnType LCD_8bit_SendCustom_Char(LCD_8bit_t *LCD,unsigned char chr[],unsigned char row,unsigned char column,unsigned char mem_pos);
//---------------------------------------

ReturnType From_Char_To_String(unsigned char data,unsigned char *string);
ReturnType From_Short_To_String(unsigned short data,unsigned char *string);
ReturnType From_Long_To_String(unsigned long data,unsigned char *string);
#endif /* LCD_H_ */