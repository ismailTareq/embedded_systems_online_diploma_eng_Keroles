/*
 * Push_Button.h
 *
 * Created: 3/19/2024 3:08:27 PM
 *  Author: ismail
 */ 


#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_
#include "DIO.h"

typedef enum{
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    Pin_Config button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

ReturnType button_initialize(const button_t *btn);


ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);
#endif /* PUSH_BUTTON_H_ */