#ifndef ALARM_H_
#define ALARM_H_
#include"GPIO.h"
typedef enum {
	ALARM_INIT,
    ALARM_ON,
	ALARM_OFF
} ALARM_STATE;

ALARM_STATE Alarm_Init(void);

ALARM_STATE Alarm_Control(uint8 port,uint8 pin,uint8 logic);


#endif //ALARM_H_
