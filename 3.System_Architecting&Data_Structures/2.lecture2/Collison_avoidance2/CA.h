#ifndef CA_H_
#define CA_H_

#include <stdio.h>
#include <stdlib.h>
#include "state.h"
enum {
    CA_waiting,
    CA_driving
}CA_state_ID;

STATE_DEFINE(CA_waiting);
STATE_DEFINE(CA_driving);

int GETdistancerandom(int l,int r, int counter);

extern void(*CA_state)();

#endif /* CA_H_ */
