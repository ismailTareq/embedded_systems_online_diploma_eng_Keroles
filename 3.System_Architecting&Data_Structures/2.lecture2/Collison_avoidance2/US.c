#include "US.h"

static int US_distance =0;


void(*US_state)();

void US_init()
{
    printf("US_init \n");
}


STATE_DEFINE(US_busy)
{
    US_state_ID=US_busy;

    US_distance =GETdistancerandom(45,55,1);

    printf("US_waiting state: distance = %d \n",US_distance);

    US_Get_Distance(US_distance);

    US_state= STATE(US_busy);
}
int GETdistancerandom(int l,int r, int counter)
{
    int i;
	for(i=0; i<counter; ++i){
		int rand_num = (rand() % (r - l + 1)) + l;
		return rand_num;
	}
}
