/*
 * KeyPad.c
 *
 * Created: 7/4/2024 6:16:36 PM
 *  Author: ismail
 */ 
#include "KeyPad.h"
static const unsigned char pressed_value[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'#', '0', '=', '+'}
};
/**================================================================
 * @Fn			-KeyPad_Init
 * @brief 		-init the pins of keypad 
 * @param [in] 	-keypad: used to keypad configurations
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-make the rows output and column input
================================================================**/
ReturnType KeyPad_Init(keypad_t *keypad)
{
	ReturnType ret = E_NOT_OK;
	int row,column;
	if(NULL == keypad)
	{
		ret = E_NOT_OK;
	}
	else
	{
		for (row = 0 ; row < ROWS ; row++){
			gpio_pin_direction_intialize(&(keypad->row_pins[row]));//making sure it zero at first
		}	
		for (column = 0 ; column < COLUMNS ; column++){
			gpio_pin_direction_intialize(&(keypad->column_pins[column]));
		}
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-get_key_pressed
 * @brief 		-scanning the keypad in order to find the pressed Button
 * @param [in] 	-keypad: used to keypad configurations
 * @param [in] 	-value: return the pressed button by user
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType get_key_pressed(keypad_t *keypad,unsigned char *value)
{
	ReturnType ret = E_NOT_OK;
	unsigned char pressed = 0;
	
	if(NULL == keypad)
	{
		ret = E_NOT_OK;
	}
	else
	{
		for (unsigned char row = 0; row < ROWS ; row++)
		{
			for (unsigned char init = 0; init < ROWS ; init++)
			{
				ret = gpio_pin_write_logic(&(keypad->row_pins[init]),DIO_LOW);
			}
			gpio_pin_write_logic(&(keypad->row_pins[row]),DIO_HIGH);
			_delay_ms(10);
			for (unsigned char column = 0; column < COLUMNS ; column++)
			{
				gpio_pin_read_logic(&(keypad->column_pins[column]),&pressed);
				if(DIO_HIGH == pressed)
				{
					*value = pressed_value[row][column];
				}
			}
		}
	}
	return ret;
}