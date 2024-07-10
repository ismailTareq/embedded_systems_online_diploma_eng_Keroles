/*
 * KPD.c
 *
 *  Created on: Jul 5, 2024
 *      Author: ismail
 */
#include "KPD.h"
int rows[] = { R0, R1, R2, R3 };
int columns[] = { C0, C1, C2, C3 };

void delay(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++)
			;
}
GPIO_Config_t keypad;
/**================================================================
 * @Fn			-Keypad_init
 * @brief 		-init the pins of keypad
 * @param [in] 	-none
 * @retval 		-none
 * Note			-make the rows output and column output and pins can be found @ref:keypad_PINS
================================================================**/
void Keypad_Init() {


	keypad.GPIO_PinNumber = R0;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	keypad.GPIO_PinNumber = R1;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	keypad.GPIO_PinNumber = R2;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	keypad.GPIO_PinNumber = R3;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	keypad.GPIO_PinNumber = C0;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	keypad.GPIO_PinNumber = C1;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	keypad.GPIO_PinNumber = C2;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	keypad.GPIO_PinNumber = C3;
	keypad.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	keypad.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(KEYPAD_PORT, &keypad);

	GPIO_WRITE_Port(KEYPAD_PORT, 0xFF);

}
/**================================================================
 * @Fn			-Keypad_getkey
 * @brief 		-get the pressed button
 * @param [in] 	-none
 * @retval 		-the pressed key
 * Note			-none
================================================================**/
unsigned char get_pressed_key() {
	int row, column , Init;
	for (column = 0; column < 4; column++)
	{
		for(Init = 0; Init < 4; Init++)
		{
			GPIO_WRITE_Pin(KEYPAD_PORT, columns[Init], GPIO_HIGH);
			delay(1);
		}
		//Turning off each column to check which button pressed
		GPIO_WRITE_Pin(KEYPAD_PORT, columns[column], GPIO_LOW);
		delay(1);
		for (row = 0; row < 4; row++) {
			if (GPIO_READ_Pin(KEYPAD_PORT, rows[row]) == 0) {
				//just to make sure it's a single Press
				while (GPIO_READ_Pin(KEYPAD_PORT, rows[row]) == 0);
				switch (column) {
				case 0:
					if(row == 0)return '7';
					else if(row == 1)return '4';
					else if(row == 2)return '1';
					else if(row == 3)return 'A';
					break;
				case 1:
					if(row == 0)return '8';
					else if(row == 1)return '5';
					else if(row == 2)return '2';
					else if(row == 3)return '0';
					break;
				case 2:
					if(row == 0)return '9';
					else if(row == 1)return '6';
					else if(row == 2)return '3';
					else if(row == 3)return '=';
					break;
				case 3:
				if(row == 0)return '/';
				else if(row == 1)return '*';
				else if(row == 2)return '-';
				else if(row == 3)return '+';
					break;
				}
			}
		}
	}
}
