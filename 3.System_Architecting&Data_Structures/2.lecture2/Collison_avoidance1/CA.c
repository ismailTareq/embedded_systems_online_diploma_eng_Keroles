#include "CA.h"

static int CA_speed = 0;
static int CA_distance = 0;
static int CA_threshold = 50;

void(*CA_state)();


STATE_DEFINE(CA_waiting)
{
    //states
    CA_state_ID = CA_waiting;

    //state action
    CA_speed=0;
    //DC_motor(CA_speed);

    //event
    CA_distance = GETdistancerandom(45,55,1);
    (CA_distance<=CA_threshold)?(CA_state=STATE(CA_waiting)):(CA_state=STATE(CA_driving));
    printf("CA_waiting State: Distance = %d  Speed = %d \n",CA_distance , CA_speed);
}
STATE_DEFINE(CA_driving)
{
    //states
    CA_state_ID = CA_waiting;

    //state action
    CA_speed=30;
    //DC_motor(CA_speed);

    //event
    CA_distance = GETdistancerandom(45,55,1);
    (CA_distance<=CA_threshold)?(CA_state=STATE(CA_waiting)):(CA_state=STATE(CA_driving));
    printf("CA_waiting State: Distance = %d  Speed = %d \n",CA_distance , CA_speed);
}
int GETdistancerandom(int l,int r, int counter)
{
    int i;
	for(i=0; i<counter; ++i){
		int rand_num = (rand() % (r - l + 1)) + l;
		return rand_num;
	}
}
