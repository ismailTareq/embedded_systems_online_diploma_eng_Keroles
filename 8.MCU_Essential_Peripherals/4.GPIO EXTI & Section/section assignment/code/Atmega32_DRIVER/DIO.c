/*
 * DIO.c
 *
 * Created: 7/4/2024 3:50:23 PM
 *  Author: ismail
 */ 
#include "DIO.h"

volatile unsigned char *DDRX_Register[]  = {&DDRA, &DDRB, &DDRC, &DDRD};//THE DIRECTION OF PIN I/O
volatile unsigned char *PINX_Register[]  = {&PINA, &PINB, &PINC, &PIND};//READ FROM THE PIN
volatile unsigned char *PORTX_Register[] = {&PORTA, &PORTB, &PORTC, &PORTD};//WRITE ON THE PIN
	
/**================================================================
 * @Fn			-gpio_pin_direction_intialize
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the Pin_Config
 * @param [in] 	-pin_config: where x can be (A..D depending on device used) to select the GPIO Instant and it's controlled with @ref GPIO_PIN_MODE_STATE
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_pin_direction_intialize(const Pin_Config *pin_config)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch (pin_config->direction)
		{
			//to make the pin output write on register DDRX 1 and for input write 0
		case DIO_DIRECTION_OUTPUT:
			SET_BIT(*DDRX_Register[pin_config->port],pin_config->pin);
			break;
		case DIO_DIRECTION_INPUT:
			CLR_BIT(*DDRX_Register[pin_config->port],pin_config->pin);
			break;
		}
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_pin_get_direction_status
 * @brief 		-Read from the specific pin u want to know it's direction
 * @param [in] 	-pin_config: where x can be (A..D depending on device used) to select the GPIO Instant
 * @param [in] 	-direction_status: where u will return ur value in it
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_pin_get_direction_status(const Pin_Config *pin_config, Direction *direction_status)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUMBER-1)||(NULL == direction_status))
	{
		ret = E_NOT_OK;
	}
	else
	{
		//return status in variable direction_status to see if it's I/O
		*direction_status = READ_BIT(*DDRX_Register[pin_config->port],pin_config->pin);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_port_direction_intialize
 * @brief 		-Read from the specific pin u want to know it's direction
 * @param [in] 	-port: where it can be (A..D depending on device used) to select the GPIO Instant
 * @param [in] 	-direction: what direction do u want the whole port to be
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_port_direction_intialize(Port_Index port, unsigned char direction)
{
	ReturnType ret = E_NOT_OK;
	if(port > PORT_MAX_NUMBER-1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*DDRX_Register[port] = direction;
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_port_get_direction_status
 * @brief 		-Read from the specific port u want to know it's direction
 * @param [in] 	-port: where it can be (A..D depending on device used) to select the GPIO Instant
 * @param [in] 	-direction_status: where u will return ur value in it
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_port_get_direction_status(Port_Index port, unsigned char *direction_status)
{
	ReturnType ret = E_NOT_OK;
	if(port > PORT_MAX_NUMBER-1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*direction_status = *DDRX_Register[port];
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_pin_write_logic
 * @brief 		-write logix on specific pin u want either 1->5V and  0->0V
 * @param [in] 	-pin_config: where it can be (A..D depending on device used) to select the GPIO Instant
 * @param [in] 	-logic: where u want to write 5V or 0V @ref GPIO_PIN_STATE
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_pin_write_logic(const Pin_Config *pin_config, Logic logic)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(logic)
		{
			case DIO_LOW:
				CLR_BIT(*PORTX_Register[pin_config->port],pin_config->pin);
			break;
			case DIO_HIGH:
				SET_BIT(*PORTX_Register[pin_config->port],pin_config->pin);
			break;
		}
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_port_write_logic
 * @brief 		-write logic on specific port u want either 1->5V and  0->0V
 * @param [in] 	-port: where it can be (A..D depending on device used) to select the GPIO Instant
 * @param [in] 	-logic: where u want to write 5V or 0V 
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_port_write_logic(Port_Index port, unsigned char logic)
{
	ReturnType ret = E_NOT_OK;
	if(port > PORT_MAX_NUMBER-1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*PORTX_Register[port] = logic;
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_pin_read_logic
 * @brief 		-read logic on specific pin u want either 1->5V and  0->0V
 * @param [in] 	-pin_config: where it can be (A..D depending on device used) to select the GPIO Instant
 * @param [in] 	-logic: return 0 for 0V and 1 for 5V
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_pin_read_logic(const Pin_Config *pin_config, Logic *logic)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUMBER-1)||(NULL == logic))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*logic = READ_BIT(*PINX_Register[pin_config->port],pin_config->pin);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_port_read_logic
 * @brief 		-read logic on specific pin u want either 1->5V and  0->0V
 * @param [in] 	-port: where it can be (A..D depending on device used) to select the GPIO Instant
 * @param [in] 	-logic: return 0 for 0V and 1 for 5V
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_port_read_logic(Port_Index port, unsigned char *logic)
{
	ReturnType ret = E_NOT_OK;
	if((port > PORT_MAX_NUMBER-1)||(NULL == logic))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*logic = *PINX_Register[port];
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_pin_toggle_logic
 * @brief 		-toggle logic on specific pin u want 
 * @param [in] 	-Pin_Config: where it can be (A..D depending on device used) to select the GPIO Instant
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_pin_toggle_logic(const Pin_Config *pin_config)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		TOG_BIT(*PORTX_Register[pin_config->port],pin_config->pin);
		ret = E_OK;
	}
	return ret;
}
/**================================================================
 * @Fn			-gpio_port_toggle_logic
 * @brief 		-toggle logic on specific pin u want 
 * @param [in] 	-port: where it can be (A..D depending on device used) to select the GPIO Instant
 * @retval 		-return if the function goes smooth and finished it's task
 * Note			-
================================================================**/
ReturnType gpio_port_toggle_logic(Port_Index port)
{
	ReturnType ret = E_NOT_OK;
	if(port > PORT_MAX_NUMBER-1)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*PORTX_Register[port] ^= 0xFF;
		ret = E_OK;
	}
	return ret;
}
ReturnType gpio_pin_intialize(const Pin_Config *pin_config)
{
	ReturnType ret = E_NOT_OK;
	if((NULL == pin_config)||(pin_config->pin > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_direction_intialize(pin_config);
		ret = gpio_pin_write_logic(pin_config,pin_config->logic);
	}
	return ret;
}