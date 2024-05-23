#include "DC.h"
static int DC_speed=0;

void(*DC_state)();
void DC_init()
{
    printf("DC_init \n");
}
void DC_Motor_Set(int speed)
{
    DC_speed=speed;
    DC_state=STATE(DC_start);
    printf("CA --------Speed=%d--------> DC \n",DC_speed);
}
STATE_DEFINE(DC_start)
{
    DC_state_ID=DC_start;
    printf("DC_start State: Speed = %d \n",DC_speed);
}
STATE_DEFINE(DC_stop)
{
    DC_state_ID=DC_stop;
    printf("DC_start State: Speed = %d \n",DC_speed);
    DC_state=STATE(DC_start);
}
