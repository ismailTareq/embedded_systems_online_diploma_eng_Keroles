#ifndef MAIN_ALG_H_
#define MAIN_ALG_H_
#include"Psensor.h"
#include"ALARM.h"
#define THRESHOLD 20

typedef enum{
    APP_ERROR,               
    APP_INIT,                
    APP_PRESSURE_DETECT,     
    APP_HIGH_PRESSURE_DETECT,
    APP_START_ALARM,         
    APP_STOP_ALARM           
} APP_STATE;

APP_STATE App_Initialization(void);
uint8 Start_App(void);
APP_STATE High_PressureDetect(void);
APP_STATE Alarm_Monitor(void);

#endif //MAIN_ALG_H_