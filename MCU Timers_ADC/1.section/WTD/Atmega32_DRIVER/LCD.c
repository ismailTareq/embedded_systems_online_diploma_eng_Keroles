/*
 * LCD.c
 *
 * Created: 7/9/2024 11:43:48 AM
 *  Author: ismail
 */ 
#include "LCD.h"
static void lcd_send_4bits(LCD_4bit_t *LCD,unsigned char command);
static void lcd_send_EnableSignal(LCD_4bit_t *LCD);
static void lcd_send_8bitEnableSignal(LCD_8bit_t *LCD);
static void lcd_4bit_set_cursor(LCD_4bit_t *LCD,unsigned char row,unsigned char column);
static void lcd_8bit_set_cursor(LCD_8bit_t *LCD,unsigned char row,unsigned char column);
/**================================================================
 * @Fn			-LCD_8bit_Init
 * @brief 		-init the pins required to make LCD work with 8bits
 * @param [in] 	-LCD: used to config the pins
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_8bit_Init(LCD_8bit_t *LCD)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_intialize(&(LCD->RS));
		ret = gpio_pin_intialize(&(LCD->EN));
		for (int i = 0 ; i<8 ;i++)
		{
			ret = gpio_pin_intialize(&(LCD->DATA[i]));
		}
		_delay_ms(20);
		ret = LCD_8bit_SendCommand(LCD,LCD_8BIT_MODE_2_LINE);
		_delay_ms(5);
		ret = LCD_8bit_SendCommand(LCD,LCD_8BIT_MODE_2_LINE);
		_delay_ms(150);
		ret = LCD_8bit_SendCommand(LCD,LCD_8BIT_MODE_2_LINE);
		
		ret = LCD_8bit_SendCommand(LCD,LCD_CLEAR);
		ret = LCD_8bit_SendCommand(LCD,LCD_RETURN_HOME);
		ret = LCD_8bit_SendCommand(LCD,LCD_ENTRY_MODE_INC_SHIFT_OFF);
		ret = LCD_8bit_SendCommand(LCD,LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF);
		ret = LCD_8bit_SendCommand(LCD,LCD_8BIT_MODE_2_LINE);
		ret = LCD_8bit_SendCommand(LCD,LCD_DDRAM_START);
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_8bit_SendCommand
 * @brief 		-send the command to the lcd to convert it as the user want
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-command: command used to give the lcd @ref LCD_COMMAND
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_8bit_SendCommand(LCD_8bit_t *LCD,unsigned char command)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	}
	else
	{
		// R/W Pin connected to the GND -> Logic (0) "Hard Wired"
		// Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"
		ret = gpio_pin_write_logic(&(LCD->RS), DIO_LOW);
		
		for (int i = 0 ; i<8 ; i++)
		{
			gpio_pin_write_logic(&(LCD->DATA[i]),(command >> i)&(unsigned char)0x01);
		}
		lcd_send_8bitEnableSignal(LCD);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_8bit_SendData
 * @brief 		-send the data to the lcd to be displayed
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-data: data i want to be showen on lcd
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_8bit_SendData(LCD_8bit_t *LCD,unsigned char data)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	}
	else
	{
		// R/W Pin connected to the GND -> Logic (0) "Hard Wired"
		// Write Logic (1) to the "Register Select" Pin to select the "Data Register"
		ret = gpio_pin_write_logic(&(LCD->RS), DIO_HIGH);
		
		for (int i = 0 ; i<8 ; i++)
		{
			gpio_pin_write_logic(&(LCD->DATA[i]),(data >> i)&(unsigned char)0x01);
		}
		lcd_send_8bitEnableSignal(LCD);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_8bit_SendData_Position
 * @brief 		-send the data to the lcd in a specific position user want
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-data: data i want to be showen on lcd
 * @param [in] 	-row: which row
 * @param [in] 	-column: which column
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_8bit_SendData_Position(LCD_8bit_t *LCD,unsigned char data,unsigned char row,unsigned char column)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	}
	else
	{
		lcd_8bit_set_cursor(LCD,row,column);
		LCD_8bit_SendData(LCD,data);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_8bit_SendString
 * @brief 		-send a string to be diplayed instead of character by character
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-string: string i want to be showen on lcd
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_8bit_SendString(LCD_8bit_t *LCD,unsigned char *string)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == LCD)||(NULL == string))
	{
		ret = E_NOT_OK;
	}
	else
	{
		while (*string)
		{
			LCD_8bit_SendData(LCD,*string++);
		}
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_8bit_SendString_Position
 * @brief 		-send the string to the lcd in a specific position user want
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-string: string i want to be showen on lcd
 * @param [in] 	-row: which row
 * @param [in] 	-column: which column
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_8bit_SendString_Position(LCD_8bit_t *LCD,unsigned char *string,unsigned char row,unsigned char column)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == LCD)||(NULL == string))
	{
		ret = E_NOT_OK;
	}
	else
	{
		lcd_8bit_set_cursor(LCD,row,column);
		LCD_8bit_SendString(LCD,string);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_8bit_SendCustom_Char
 * @brief 		-give it the custom character and save it in CGRAM 
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-chr: the custom character
 * @param [in] 	-row: which row
 * @param [in] 	-column: which column
 * @param [in] 	-mem_pos: save it in memory
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-CGRAM has only 8bytes so it can save upto only 8characters
================================================================**/
ReturnType LCD_8bit_SendCustom_Char(LCD_8bit_t *LCD,unsigned char chr[],unsigned char row,unsigned char column,unsigned char mem_pos)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == LCD)||(NULL == chr))
	{
		ret = E_NOT_OK;
	}
	else
	{
		LCD_8bit_SendCommand(LCD,(LCD_CGRAM_START + (mem_pos*8)));
		for (int i = 0; i<8 ; i++)
		{
			LCD_8bit_SendData(LCD,chr[i]);
		}
		LCD_8bit_SendData_Position(LCD,mem_pos,row,column);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_4bit_Init
 * @brief 		-init the pins required to make LCD work with 4bits
 * @param [in] 	-LCD: used to config the pins
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_4bit_Init(LCD_4bit_t *LCD)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	} 
	else
	{
		ret = gpio_pin_intialize(&(LCD->RS));
		ret = gpio_pin_intialize(&(LCD->EN));
		for (int i = 0 ; i<4 ;i++)
		{
			ret = gpio_pin_intialize(&(LCD->DATA[i]));
		}
		_delay_ms(20);
		ret = LCD_4bit_SendCommand(LCD,LCD_8BIT_MODE_2_LINE);
		_delay_ms(5);
		ret = LCD_4bit_SendCommand(LCD,LCD_8BIT_MODE_2_LINE);
		_delay_ms(150);
		ret = LCD_4bit_SendCommand(LCD,LCD_8BIT_MODE_2_LINE);
		
		ret = LCD_4bit_SendCommand(LCD,LCD_CLEAR);
		ret = LCD_4bit_SendCommand(LCD,LCD_RETURN_HOME);
		ret = LCD_4bit_SendCommand(LCD,LCD_ENTRY_MODE_INC_SHIFT_OFF);
		ret = LCD_4bit_SendCommand(LCD,LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF);
		ret = LCD_4bit_SendCommand(LCD,LCD_4BIT_MODE_2_LINE);
		ret = LCD_4bit_SendCommand(LCD,LCD_DDRAM_START);
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_4bit_SendCommand
 * @brief 		-send the command to the lcd to convert it as the user want
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-command: command used to give the lcd @ref LCD_COMMAND
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_4bit_SendCommand(LCD_4bit_t *LCD,unsigned char command)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	}
	else
	{
		 // R/W Pin connected to the GND -> Logic (0) "Hard Wired"
		 // Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  
		 ret = gpio_pin_write_logic(&(LCD->RS), DIO_LOW);
		 
		 //send first high nibbles
		 lcd_send_4bits(LCD,command >> 4);
		 //send enable signal
		 lcd_send_EnableSignal(LCD);
		 //send first high nibbles
		 lcd_send_4bits(LCD,command);
		 //send enable signal
		 lcd_send_EnableSignal(LCD);
		 ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_4bit_SendData
 * @brief 		-send the data to the lcd to be displayed
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-data: data i want to be showen on lcd
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_4bit_SendData(LCD_4bit_t *LCD,unsigned char data)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	}
	else
	{
		// R/W Pin connected to the GND -> Logic (0) "Hard Wired"
		// Write Logic (1) to the "Register Select" Pin to select the "Data Register"
		ret = gpio_pin_write_logic(&(LCD->RS), DIO_HIGH);
		
		//send first high nibbles
		lcd_send_4bits(LCD,data >> 4);
		//send enable signal
		lcd_send_EnableSignal(LCD);
		//send first high nibbles
		lcd_send_4bits(LCD,data);
		//send enable signal
		lcd_send_EnableSignal(LCD);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_4bit_SendData_Position
 * @brief 		-send the data to the lcd in a specific position user want
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-data: data i want to be showen on lcd
 * @param [in] 	-row: which row
 * @param [in] 	-column: which column
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_4bit_SendData_Position(LCD_4bit_t *LCD,unsigned char data,unsigned char row,unsigned char column)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == LCD)
	{
		ret = E_NOT_OK;
	}
	else
	{
		lcd_4bit_set_cursor(LCD,row,column);
		LCD_4bit_SendData(LCD,data);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_4bit_SendString
 * @brief 		-send a string to be diplayed instead of character by character
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-string: string i want to be showen on lcd
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_4bit_SendString(LCD_4bit_t *LCD,unsigned char *string)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == LCD)||(NULL == string))
	{
		ret = E_NOT_OK;
	}
	else
	{
		while (*string)
		{
			LCD_4bit_SendData(LCD,*string++);
		}
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_4bit_SendString_Position
 * @brief 		-send the string to the lcd in a specific position user want
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-string: string i want to be showen on lcd
 * @param [in] 	-row: which row
 * @param [in] 	-column: which column
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-none
================================================================**/
ReturnType LCD_4bit_SendString_Position(LCD_4bit_t *LCD,unsigned char *string,unsigned char row,unsigned char column)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == LCD)||(NULL == string))
	{
		ret = E_NOT_OK;
	}
	else
	{
		lcd_4bit_set_cursor(LCD,row,column);
		LCD_4bit_SendString(LCD,string);
	}
	return ret;
}
/**================================================================
 * @Fn			-LCD_4bit_SendCustom_Char
 * @brief 		-give it the custom character and save it in CGRAM 
 * @param [in] 	-LCD: used to config the pins
 * @param [in] 	-chr: the custom character
 * @param [in] 	-row: which row
 * @param [in] 	-column: which column
 * @param [in] 	-mem_pos: save it in memory
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-CGRAM has only 8bytes so it can save upto only 8characters
================================================================**/
ReturnType LCD_4bit_SendCustom_Char(LCD_4bit_t *LCD,unsigned char chr[],unsigned char row,unsigned char column,unsigned char mem_pos)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == LCD)||(NULL == chr))
	{
		ret = E_NOT_OK;
	}
	else
	{
		LCD_4bit_SendCommand(LCD,(LCD_CGRAM_START + (mem_pos*8)));
		for (int i = 0; i<8 ; i++)
		{
			LCD_4bit_SendData(LCD,chr[i]);
		}
		LCD_4bit_SendData_Position(LCD,mem_pos,row,column);
		ret = E_OK;
	}
	return ret;
}

ReturnType From_Char_To_String(unsigned char data,unsigned char *string)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == string)
	{
		ret = E_NOT_OK;
	}
	else
	{
		memset((char *)string, '\0', 4);
		sprintf(string, "%i", data);
	}
	return ret;
}
ReturnType From_Short_To_String(unsigned short data,unsigned char *string)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == string)
	{
		ret = E_NOT_OK;
	}
	else
	{
		
	}
	return ret;
}
ReturnType From_Long_To_String(unsigned long data,unsigned char *string)
{
	ReturnType ret = E_NOT_OK;
	if(NULL == string)
	{
		ret = E_NOT_OK;
	}
	else
	{
		
	}
	return ret;
}

static void lcd_send_4bits(LCD_4bit_t *LCD,unsigned char command)
{
	for(int i =0 ; i<4 ; i++)
	{
		gpio_pin_write_logic(&(LCD->DATA[i]),(command >> i)&(unsigned char)0x01);
	}
}

static void lcd_send_EnableSignal(LCD_4bit_t *LCD)
{
	gpio_pin_write_logic(&(LCD->EN),DIO_HIGH);
	_delay_us(10);
	gpio_pin_write_logic(&(LCD->EN),DIO_LOW);
}
static void lcd_send_8bitEnableSignal(LCD_8bit_t *LCD)
{
	gpio_pin_write_logic(&(LCD->EN),DIO_HIGH);
	_delay_us(10);
	gpio_pin_write_logic(&(LCD->EN),DIO_LOW);
}

static void lcd_4bit_set_cursor(LCD_4bit_t *LCD,unsigned char row,unsigned char column)
{
	column--;//in order to be the first column
	switch(row)
	{
		case ROW1: LCD_4bit_SendCommand(LCD,(0x80+column));break;
		case ROW2: LCD_4bit_SendCommand(LCD,(0xC0+column));break;
		case ROW3: LCD_4bit_SendCommand(LCD,(0x94+column));break;
		case ROW4: LCD_4bit_SendCommand(LCD,(0xD4+column));break;
	}
}
static void lcd_8bit_set_cursor(LCD_8bit_t *LCD,unsigned char row,unsigned char column)
{
	column--;//in order to be the first column
	switch(row)
	{
		case ROW1: LCD_8bit_SendCommand(LCD,(0x80+column));break;
		case ROW2: LCD_8bit_SendCommand(LCD,(0xC0+column));break;
		case ROW3: LCD_8bit_SendCommand(LCD,(0x94+column));break;
		case ROW4: LCD_8bit_SendCommand(LCD,(0xD4+column));break;
	}
}