#include"ALARM.h"
ALARM_STATE Alarm_Init(void)
{
	GPIOA_CRH &= 0xFF0FFFFF;
    GPIOA_CRH |= 0x00200000;
    return ALARM_INIT;
}

ALARM_STATE Alarm_Control(uint8 port,uint8 pin,uint8 logic)
{
	if(GPIO_Write_Pin(port,pin,logic) == GPIO_WRITTEN)
	{
		if(logic == GPIO_HIGH)
		{
			return ALARM_ON;
		}
		else if(logic == GPIO_LOW)
		{
			return ALARM_OFF;
		}
	}
}

