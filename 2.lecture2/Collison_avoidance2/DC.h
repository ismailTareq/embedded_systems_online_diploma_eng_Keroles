#ifndef DC_H_
#define DC_H_
#include <stdio.h>
#include <stdlib.h>
#include "state.h"

enum{
    DC_start,
    DC_stop
}DC_state_ID;

STATE_DEFINE(DC_start);
STATE_DEFINE(DC_stop);
void DC_init();

extern void(*DC_state)();

#endif // US_H_
