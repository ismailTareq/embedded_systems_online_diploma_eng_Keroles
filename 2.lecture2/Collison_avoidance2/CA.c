#include "CA.h"

static int CA_speed = 0;
static int CA_distance = 0;
static int CA_threshold = 50;

void(*CA_state)();

void US_Get_Distance(int distance)
{
	CA_distance = distance;
	if(CA_distance <= CA_threshold){
		CA_state = STATE(CA_waiting);
	}
	else{
		CA_state = STATE(CA_driving);
	}
	printf("US --------distance=%d--------> CA \n",CA_distance);
}

STATE_DEFINE(CA_waiting)
{
    //states
    CA_state_ID = CA_waiting;

    //state action
    CA_speed=0;
    printf("CA_waiting State: Distance = %d  Speed = %d \n",CA_distance , CA_speed);

    //DC_motor(CA_speed);

    //event
    DC_Motor_Set(CA_speed);
}
STATE_DEFINE(CA_driving)
{
    //states
    CA_state_ID = CA_driving;

    //state action
    CA_speed=30;

    printf("CA_waiting State: Distance = %d  Speed = %d \n",CA_distance , CA_speed);

    //DC_motor(CA_speed);

    //event
    DC_Motor_Set(CA_speed);
}
