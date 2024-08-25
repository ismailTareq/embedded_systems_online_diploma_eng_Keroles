/*
 * CortexMX_OS_porting.c
 *
 *  Created on: Aug 24, 2024
 *      Author: ismail
 */
#include "CortexMX_OS_porting.h"

unsigned char systickled;
void HW_init()
{
	//intialize clock tree (RCC -> SysTick Timer & CPU) 8 MHZ
	//init HW
	//Clock Tree
	//RCC Default values makes CPU Clock & SysTick Timer clock = 8 MHZ

	// 8 MHZ
	// 1 count -> 0.125 us
	// X count -> 1 ms
	// X = 8000 count

	//decrease PendSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	__NVIC_SetPriority(PendSV_IRQn, 15) ;//make it 15 instead of 14
}


void HardFault_Handler (void)
{
	while(1) ;
}
void MemManage_Handler (void)
{
	while(1) ;
}
void BusFault_Handler(void)
{
	while(1) ;
}
void UsageFault_Handler(void)
{
	while(1) ;
}

__attribute((naked)) void SVC_Handler()
{
	__asm("tst lr,#4 \n\t"
			"ITE EQ \n\t"
			"mrseq r0,MSP \n\t"
			"mrsne r0,PSP \n\t"
			"B Os_SVC_Services");
}

void Trigger_OS_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void Start_ticker()
{
	//	This clock tree should be defined in HW_init()
		//	8 MHZ
		//	1 count -> 0.125 us
		//	X count -> 1 ms
		//	X = 8000 Count

		 SysTick_Config(8000);
}

void SysTick_Handler(void)
{
	systickled^=1;

	MYRTOS_Update_TasksWaitingTime();
	//Determine current and next
	Decide_WhatNext();
	//Switch Context and restore
	Trigger_OS_PendSV();

}
