/*
 * Push_Button.c
 *
 * Created: 3/19/2024 3:08:19 PM
 *  Author: ismail
 */ 
#include "Push_Button.h"
ReturnType button_initialize(const button_t *btn){
    ReturnType ret = E_OK;
    if(NULL == btn){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(btn->button_pin));
    }
    return ret;
}

ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    ReturnType ret = E_NOT_OK;
    Logic Pin_Logic_Status = DIO_LOW;
    if((NULL == btn) || (NULL == btn_state)){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn->button_pin), &Pin_Logic_Status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(DIO_HIGH == Pin_Logic_Status){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection){
            if(DIO_HIGH == Pin_Logic_Status){
                *btn_state = BUTTON_RELEASED;
            }
            else{
                *btn_state = BUTTON_PRESSED;
            }
        }
        else { /* Nothing */ }
        ret = E_OK;
    }
    return ret;
}