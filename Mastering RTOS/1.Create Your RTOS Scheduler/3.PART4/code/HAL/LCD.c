/*
 * LCD.c
 *
 *  Created on: Jul 10, 2024
 *      Author: ismail
 */
#include "LCD.h"
GPIO_Config_t LCD ;
static void LCD_ENABLE_SIGNAL(void);
static void _delay_ms(unsigned long time);
//***************************Delay Function***********************************




//***************************LCD INIT FUNCTION***********************************

void LCD_GPIO_init(void)
{
	LCD.GPIO_PinNumber = RS;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);

	LCD.GPIO_PinNumber = RW;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);

	LCD.GPIO_PinNumber = EN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);


	//Setting Pin 0->7 to be output with 10Mhz speed for LCD DATA D0->D7
	LCD.GPIO_PinNumber = LCD_D0_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);

	LCD.GPIO_PinNumber =	LCD_D1_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);


	LCD.GPIO_PinNumber = LCD_D2_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);


	LCD.GPIO_PinNumber = LCD_D3_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);


	LCD.GPIO_PinNumber = LCD_D4_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);


	LCD.GPIO_PinNumber = LCD_D5_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);


	LCD.GPIO_PinNumber = LCD_D6_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);


	LCD.GPIO_PinNumber = LCD_D7_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);

	//RS->0 instruction register
	GPIO_WRITE_Pin(LCD_PORT, RS, GPIO_LOW);
	//RW->0 Write
	GPIO_WRITE_Pin(LCD_PORT, RW, GPIO_LOW);
	//EN->0
	GPIO_WRITE_Pin(LCD_PORT, EN, GPIO_LOW);

}
void LCD_INIT(void)
{
	LCD_GPIO_init();
	_delay_ms(20);
	LCD_WRITE_COMMAND(LCD_8BIT_MODE_2_LINE);
	_delay_ms(5);
	LCD_WRITE_COMMAND(LCD_8BIT_MODE_2_LINE);
	_delay_ms(150);
	LCD_WRITE_COMMAND(LCD_8BIT_MODE_2_LINE);

	LCD_WRITE_COMMAND(LCD_CLEAR);
	LCD_WRITE_COMMAND(LCD_RETURN_HOME);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE_INC_SHIFT_OFF);
	LCD_WRITE_COMMAND(LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON);
	LCD_WRITE_COMMAND(LCD_8BIT_MODE_2_LINE);
	LCD_WRITE_COMMAND(LCD_DDRAM_START);

}

//***************************LCD CLEAR FUNCTION***********************************

void LCD_clearscreen(void)
{
	LCD_WRITE_COMMAND(LCD_CLEAR);
}



//***************************COMMAND FUNCTION***********************************

void LCD_WRITE_COMMAND(unsigned char command){

	LCDisbusy();

	//RS == 0 (instruction register)
	GPIO_WRITE_Pin(LCD_PORT, RS, GPIO_LOW);
	//RW == 0 (Write mode)
	GPIO_WRITE_Pin(LCD_PORT, RW, GPIO_LOW);

	GPIO_WRITE_Pin(LCD_PORT, LCD_D0_PIN, READ_BIT(command,0)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D1_PIN, READ_BIT(command,1)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D2_PIN, READ_BIT(command,2)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D3_PIN, READ_BIT(command,3)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D4_PIN, READ_BIT(command,4)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D5_PIN, READ_BIT(command,5)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D6_PIN, READ_BIT(command,6)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D7_PIN, READ_BIT(command,7)  );

	_delay_ms(5);
	LCD_ENABLE_SIGNAL();
}

//******************************CHARACTER FUNCTION********************************


void LCD_WRITE_DATA(unsigned char data){


	LCDisbusy();

	//RS == 1 (DATA register)
	GPIO_WRITE_Pin(LCD_PORT, RS, GPIO_HIGH);
	//RW == 0 (Write mode)
	GPIO_WRITE_Pin(LCD_PORT, RW, GPIO_LOW);

	GPIO_WRITE_Pin(LCD_PORT, LCD_D0_PIN, READ_BIT(data,0)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D1_PIN, READ_BIT(data,1)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D2_PIN, READ_BIT(data,2)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D3_PIN, READ_BIT(data,3)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D4_PIN, READ_BIT(data,4)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D5_PIN, READ_BIT(data,5)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D6_PIN, READ_BIT(data,6)  );
	GPIO_WRITE_Pin(LCD_PORT, LCD_D7_PIN, READ_BIT(data,7)  );

	_delay_ms(5);

	LCD_ENABLE_SIGNAL();

}

//*************************STRING FUNCTION*************************************



void LCD_WRITE_STRING(char* string){

	int counter  = 0;
	while(*string){
		LCD_WRITE_DATA(*string++);
		counter++;

		if(counter == 16){

			LCD_GOTO_XY(2,0);


		}

		else if(counter == 32){
			LCD_clearscreen();
			LCD_GOTO_XY(1,0);
			counter = 0;
		}



	}


}

//****************************BUSY FUNCTION**********************************

void LCDisbusy(void)
{
	LCD.GPIO_PinNumber = LCD_D7_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
	GPIO_Init(LCD_PORT, &LCD);

	//RW == 1 (READ MODE)
	GPIO_WRITE_Pin(LCD_PORT, RW, GPIO_HIGH);
	//RS == 0 (Command Mode)
	GPIO_WRITE_Pin(LCD_PORT, RS, GPIO_LOW);

	while(GPIO_READ_Pin(LCD_PORT, LCD_D7_PIN) & 1);//checking on pin D7 if it's busy or not

	LCD_ENABLE_SIGNAL();

	//set D7 to to be output
	LCD.GPIO_PinNumber = LCD_D7_PIN;
	LCD.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LCD.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(LCD_PORT, &LCD);

	//RW == 0 (Write Mode)
	GPIO_WRITE_Pin(LCD_PORT, RW, GPIO_LOW);


}

//*****************************POSITION FUNCTION*********************************

void LCD_GOTO_XY(unsigned char row, unsigned char column){

	if(row == 1){

		if(column < 16 &&  column >=0)
		{
			LCD_WRITE_COMMAND(0x80 + column);
		}
	}
	else if(row == 2){

		if(column < 32  && column >=0)
		{
			LCD_WRITE_COMMAND(0xC0 + column);
		}
	}
}
void LCD_ENABLE_SIGNAL(void){

	GPIO_WRITE_Pin(LCD_PORT, EN, GPIO_HIGH);
	_delay_ms(10);
	GPIO_WRITE_Pin(LCD_PORT, EN, GPIO_LOW);
}
void _delay_ms(unsigned long time){
	unsigned long i,j;
	for(i=0 ;i<time;i++){
		for(j=0;j<255;j++);
	}
}
