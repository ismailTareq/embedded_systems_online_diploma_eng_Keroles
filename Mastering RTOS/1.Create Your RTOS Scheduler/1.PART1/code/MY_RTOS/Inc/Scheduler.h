/*
 * Scheduler.h
 *
 *  Created on: Aug 24, 2024
 *      Author: ismail
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "CortexMX_OS_porting.h"

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
typedef enum{
	NoError,
	Ready_Queue_Init_error,
	Task_Exceeded_Stack_size,


}IsmailRTOS_errorID;

typedef enum{
	Suspend,
	Running,
	Waiting,
	Ready
}Task_state_t;

typedef struct
{
	uint32_t stacksize;
	uint8_t priority;
	void(*TaskEntry)();
	uint32_t S_PSP_Task;
	uint32_t E_PSP_Task;
	uint32_t* Current_PSP;
	char Task_Name[30];
	Task_state_t Task_state;
	struct
	{
		enum
		{
			Enable,
			Disable
		}Blocking;
		uint32_t Waiting_Ticks;
	}TimingWaiting;

}task_Typedef;
//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//APIS
//-*-*-*-*-*-*-*-*-*-*-*

IsmailRTOS_errorID IsmailRTOS_Init(void);

IsmailRTOS_errorID IsmailRTOS_CreateTask(task_Typedef* task);

#endif /* SCHEDULER_H_ */
