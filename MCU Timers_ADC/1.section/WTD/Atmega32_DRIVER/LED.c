/*
 * LED.c
 *
 * Created: 3/19/2024 3:07:10 PM
 *  Author: ismail
 */ 
#include "LED.h"
ReturnType led_initialize(const led_t *led){
    ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        Pin_Config pin_obj = { .port = led->port_name, .pin = led->pin, 
                                 .direction = DIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_intialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
ReturnType led_turn_on(const led_t *led){
    ReturnType ret = E_OK;
     if(NULL == led){
         ret = E_NOT_OK;
     }
     else{
         Pin_Config pin_obj = { .port = led->port_name, .pin = led->pin, 
                                  .direction = DIO_DIRECTION_OUTPUT,.logic = led->led_status };
         gpio_pin_write_logic(&pin_obj, DIO_HIGH);
     }
    return ret;
}

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
ReturnType led_turn_off(const led_t *led){
    ReturnType ret = E_OK;
     if(NULL == led){
         ret = E_NOT_OK;
     }
     else{
         Pin_Config pin_obj = { .port = led->port_name, .pin = led->pin, 
                                  .direction = DIO_DIRECTION_OUTPUT,.logic = led->led_status };
         gpio_pin_write_logic(&pin_obj, DIO_LOW);
     }
    return ret;
}

ReturnType led_toggle(const led_t *led){
    ReturnType ret = E_OK;
     if(NULL == led){
         ret = E_NOT_OK;
     }
     else{
         Pin_Config pin_obj = { .port = led->port_name, .pin = led->pin, 
                                  .direction = DIO_DIRECTION_OUTPUT,.logic = led->led_status };
         gpio_pin_toggle_logic(&pin_obj);
     }
    return ret;
}
