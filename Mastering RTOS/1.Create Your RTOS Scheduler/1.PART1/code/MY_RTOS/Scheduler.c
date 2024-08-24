/*
 * Scheduler.c
 *
 *  Created on: Aug 24, 2024
 *      Author: ismail
 */
#include "Scheduler.h"
#include "Circular_FIFO.h"

typedef enum{
	OS_Suspend,
	OS_Running
}OS_state_t;

//defined here so that the user can't see it
struct
{
	task_Typedef* TaskTable[100];
	uint32_t S_MSP_Task;
	uint32_t E_MSP_Task;
	uint32_t PSP_Locator;
	uint32_t number_ActiveTasks;
	task_Typedef* CurrentTask;
	task_Typedef* NextTask;
	OS_state_t OS_state;

}OS_Control;

FIFO_Buf_t ReadyQueue;
task_Typedef* Ready_table[100];
task_Typedef Idle_task;


void IsmailRTOS_IdleTask(void){
	while(1){
		__asm("nop");
	}
}

void IsmailRTOS_Create_IdleTask(void)
{
	strcpy(Idle_task.Task_Name,"Idle_Task");
	Idle_task.priority = 255;
	Idle_task.TaskEntry = IsmailRTOS_IdleTask;
	Idle_task.stacksize = 300;
}


void IsmailRTOS_Create_MainStack(void)
{
	OS_Control.S_MSP_Task = &_estack;
	OS_Control.E_MSP_Task = OS_Control.S_MSP_Task - MainStackSize;
	OS_Control.PSP_Locator = OS_Control.E_MSP_Task - 8;
}

IsmailRTOS_errorID IsmailRTOS_Init(void)
{
	IsmailRTOS_errorID ErrorID = NoError;

	//1. OS state >> suspend
	OS_Control.OS_state = OS_Suspend;

	//2. initialize the main stack
	IsmailRTOS_Create_MainStack();
	//3. Create Ready Queue
	if(FIFO_init(&ReadyQueue, Ready_table, 100) != FIFO_NO_ERROR)
	{
		ErrorID += Ready_Queue_Init_error ;
	}
	//4. Create IDLE task
	IsmailRTOS_Create_IdleTask();

	//5. create task stack
	ErrorID += IsmailRTOS_CreateTask(&Idle_task);

	return ErrorID;
}

void IsmailRTOS_CreateTask_Stack(task_Typedef* task)
{
	//task frame
	//to prevent any kind of data loss during switch context
	/*xpsr
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *  save from r5 >> r11 manually save and store
	 */
	task->Current_PSP = task->S_PSP_Task;

	//save xPRS Tbit
	*(task->Current_PSP) = 0x01000000;
	task->Current_PSP--;

	//save PC
	*(task->Current_PSP) = (unsigned int)task->TaskEntry;
	task->Current_PSP--;

	//save LR
	*(task->Current_PSP) = 0xFFFFFFFD;

	//save values in R0 -> R12
	for(int i = 0; i<13 ; i++)
	{
		task->Current_PSP--;
		*(task->Current_PSP) = 0;
	}

}

IsmailRTOS_errorID IsmailRTOS_CreateTask(task_Typedef* task)
{
	IsmailRTOS_errorID ErrorID = NoError;

	task->S_PSP_Task = OS_Control.PSP_Locator;

	task->E_PSP_Task = task->S_PSP_Task - task->stacksize;

	if((task->E_PSP_Task)<(unsigned int)(&_eheap))
	{
		return Task_Exceeded_Stack_size;
	}
	OS_Control.PSP_Locator = task->E_PSP_Task - 8;

	IsmailRTOS_CreateTask_Stack(task);

	//	-				-
	//	- _S_PSP_Task	-
	//	-	  Task Stack	-
	//	- _E_PSP_Task	-
	//	-

	task->Task_state = Suspend;

	return ErrorID;
}








//executing specific OS service
void Os_SVC_Services(unsigned int *Stack_Pointer)
{
	unsigned char SVC_ID;
	SVC_ID = *((unsigned char *)(((unsigned char *)Stack_Pointer[6])-2));

	switch(SVC_ID)
	{
	case 1: //TaskA

		break;

	case 2: //TaskB

		break;
	}
}
void PendSV_Handler(void)
{

}
void OS_SVC_SET(int SVC_ID)
{
	switch(SVC_ID)
	{
	case 1:	//TaskA
		__asm volatile("SVC #0x01");
		break;

	case 2:	//TaskB
		__asm volatile("SVC #0x02");
		break;
	}
}
