#ifndef PSENSOR_H_
#define PSENSOR_H_
#include"GPIO.h"
typedef enum {
	P_SENSOR_INIT,
    P_SENSOR_READING,
	P_SENSOR_WAITING,
	P_SENSOR_ERROR
} P_SENSOR_STATE;

//APIS
P_SENSOR_STATE Psensor_Initialization(void);

P_SENSOR_STATE GetPressureVal(vuint8 *Pval);

void Delay(vuint32 period);



#endif //PSENSOR_H_