/*
 * CortexMX_OS_porting.h
 *
 *  Created on: Aug 24, 2024
 *      Author: ismail
 */

#ifndef CORTEXMX_OS_PORTING_H_
#define CORTEXMX_OS_PORTING_H_

#include "core_cm3.h"

extern int _estack;
extern int _eheap;

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*

#define MainStackSize         3072//3 * 1024

#define OS_SET_PSP(address)              __asm volatile("mov r0,%0 \n\t msr PSP,r0" : : "r" (address))
#define OS_GET_PSP(address)              __asm volatile("mrs r0,PSP \n\t mov %0,r0"   : "=r" (address))

#define OS_SWITCH_SP_to_PSP          	 __asm volatile("mrs r0, CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0")
#define OS_SWITCH_SP_to_MSP          	 __asm volatile("mrs r0, CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0")

#define OS_SWITCH_to_privileged   		__asm volatile(" mrs r3, CONTROL  \n\t" \
										" lsr r3,r3,#0x1   \n\t"       \
										" lsl r3,r3,#0x1   \n\t"	   \
										" msr CONTROL, r3");

#define OS_SWITCH_to_unprivileged		__asm volatile(" mrs r3, CONTROL  \n\t" \
											  " orr r3,r3,#0x1   \n\t" \
											  " msr CONTROL, r3 ")

void HW_init();
void Trigger_OS_PendSV();
void Start_ticker();
#endif /* CORTEXMX_OS_PORTING_H_ */
