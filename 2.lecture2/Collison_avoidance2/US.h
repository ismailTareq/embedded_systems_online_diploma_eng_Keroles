#ifndef US_H_
#define US_H_

#include <stdio.h>
#include <stdlib.h>
#include "state.h"

enum{
 US_busy
}US_state_ID;

STATE_DEFINE(US_busy);
void US_init();

extern void(*US_state)();
#endif // US_H_
