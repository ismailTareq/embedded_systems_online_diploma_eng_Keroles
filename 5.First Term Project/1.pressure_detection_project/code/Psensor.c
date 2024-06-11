#include"Psensor.h"

P_SENSOR_STATE Psensor_Initialization(void)
{
	GPIOA_CRL &= 0xFF0FFFFF;
	GPIOA_CRL |= 0x00000000;
	return P_SENSOR_INIT;
}
void Delay(vuint32 period)
{
	vuint32 timer = 0;
	for(timer = 0; timer <= period; timer++);
}

P_SENSOR_STATE GetPressureVal(vuint8 *Pval)
{
	*Pval = GPIOA_IDR&0xFF;
	if(*Pval)
	{
		return P_SENSOR_READING;
	}
	Delay(100);
	return P_SENSOR_WAITING;
	
}