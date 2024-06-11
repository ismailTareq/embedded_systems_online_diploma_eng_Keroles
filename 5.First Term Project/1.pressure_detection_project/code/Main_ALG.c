#include"Main_ALG.h"
vuint8 Pvalue =0;
APP_STATE App_Initialization(void)
{
	if(GPIO_Initialization() == GPIO_INIT)
	{
		if(Psensor_Initialization() == P_SENSOR_INIT)
		{
			if(Alarm_Init() == ALARM_INIT)
			{
				return APP_INIT;
			}
		}
	}
	return APP_ERROR;
}

APP_STATE High_PressureDetect(void)
{
	if(GetPressureVal(&Pvalue) == P_SENSOR_READING)
	{
		if(Pvalue > THRESHOLD)
		{
			return APP_HIGH_PRESSURE_DETECT;
		}
		else
		{
			return APP_PRESSURE_DETECT;
		}
	}
	return APP_ERROR;
}
APP_STATE Alarm_Monitor(void)
{
	if(High_PressureDetect() == APP_PRESSURE_DETECT)
	{
		Alarm_Control('A', 13 , GPIO_LOW);
		return APP_STOP_ALARM;
	}
	else if(High_PressureDetect() == APP_HIGH_PRESSURE_DETECT)
	{
		Alarm_Control('A', 13 , GPIO_HIGH);
		Delay(6000);
		Alarm_Control('A', 13 , GPIO_LOW);
		return APP_START_ALARM;
	}
	return APP_ERROR;
}
uint8 Start_App(void)
{
	if (Alarm_Monitor() == APP_START_ALARM)
    {
        return 1;
    }
    else if (Alarm_Monitor() == APP_STOP_ALARM)
    {
        return 1;
    }
	return 0;
}