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

typedef enum {
	SVC_Activatetask,
	SVC_terminateTask,
	SVC_TaskWaitingTime,
}SVC_ID_t;

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

//switch context here
__attribute ((naked)) void PendSV_Handler(void)
{
	//Save the Context of the Current Task

	//Get the Current Task "Current PSP from CPU register" as CPU Push XPSR,.....,R0
	OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);

	//using this Current_PSP (Pointer) to store (R4 to R11)
	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r4" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r5" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r6" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r7" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r8" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r9" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r10" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));

	OS_Control.CurrentTask->Current_PSP--;
	__asm volatile("mov %0,r11" : "=r" (*(OS_Control.CurrentTask->Current_PSP)));
	//save the current Value of PSP
	//already saved in Current_PSP

	///////////////////////////////////////////////////////////
	//Restore the Context of the Next Task
	if(OS_Control.NextTask != NULL)
	{
		OS_Control.CurrentTask = OS_Control.NextTask;
		OS_Control.NextTask = NULL;
	}

	//pop
	__asm volatile("mov r11,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile("mov r10,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile("mov r9,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile("mov r8,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile("mov r7,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile("mov r6,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile("mov r5,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	__asm volatile("mov r4,%0" : : "r" (*(OS_Control.CurrentTask->Current_PSP)));
	OS_Control.CurrentTask->Current_PSP++;

	//update PSP and exit
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	__asm volatile("BX LR");
}

unsigned char IdleTaskLed ;
void IsmailRTOS_IdleTask(void){
	while(1)
	{
		IdleTaskLed ^= 1;
		__asm("wfe");
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

	//update sch.table
	OS_Control.TaskTable[OS_Control.number_ActiveTasks] = task;
	OS_Control.number_ActiveTasks++;

	//	-				-
	//	- _S_PSP_Task	-
	//	-	  Task Stack	-
	//	- _E_PSP_Task	-
	//	-

	task->Task_state = Suspend;

	return ErrorID;
}

void bubbleSort()
{
	unsigned int i, j , n;
	task_Typedef* temp ;
	n = OS_Control.number_ActiveTasks ;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (OS_Control.TaskTable[j]->priority > OS_Control.TaskTable[j + 1]->priority)
			{
				temp = OS_Control.TaskTable[j] ;
				OS_Control.TaskTable[j] = OS_Control.TaskTable[j + 1 ] ;
				OS_Control.TaskTable[j + 1] = temp ;
			}

}


void IsmailRTOS_UpdateSchedular()
{
	task_Typedef* temp =NULL ;
	task_Typedef* task ;
	task_Typedef* nextTask ;
	int i = 0 ;

	//1.bubble sort based on priority
	bubbleSort();
	//2.free ready queue
	while(FIFO_dequeue(&ReadyQueue, &temp) != FIFO_EMPTY);
	//3.update ready queue
	while(i<OS_Control.number_ActiveTasks)
	{
		task = OS_Control.TaskTable[i];
		nextTask = OS_Control.TaskTable[i+1];

		if(task->Task_state != Suspend)
		{
			//in case we reached to the end of TaskTable
			if(nextTask->Task_state == Suspend)
			{
				FIFO_enqueue(&ReadyQueue, task);
				task->Task_state = Ready;
				break;
			}
			//in case next task priority is higher than task priority the smaller the number the higher the priority
			else if(nextTask->priority > task->priority)
			{
				FIFO_enqueue(&ReadyQueue, task);
				task->Task_state = Ready;
				break;
			}
			//in case next task priority is EQUAL than task priority
			//	push task to ready state
			//	And make the task = nexttask  and nexttask++ in the next i++
			else if(nextTask->priority == task->priority)
			{
				FIFO_enqueue(&ReadyQueue, task);
				task->Task_state = Ready;
			}

		}

		i++;
	}

}
//handler mode
void Decide_WhatNext()
{
	//if Ready Queue is empty && OS_Control->currentTask != suspend
	if((ReadyQueue.counter == 0)&&(OS_Control.CurrentTask->Task_state != Suspend))
	{
		OS_Control.CurrentTask->Task_state = Running;
		FIFO_enqueue(&ReadyQueue, OS_Control.CurrentTask);
		OS_Control.NextTask = OS_Control.CurrentTask;
	}
	else
	{
		FIFO_dequeue(&ReadyQueue, &OS_Control.NextTask);
		OS_Control.NextTask->Task_state = Running;
		//round robin
		if((OS_Control.CurrentTask->priority == OS_Control.NextTask->priority)&&(OS_Control.CurrentTask->Task_state != Suspend))
		{
			FIFO_enqueue(&ReadyQueue, OS_Control.CurrentTask);
			OS_Control.CurrentTask->Task_state = Ready;
		}
	}
}


//handler mode
void Os_SVC_Services(unsigned int *Stack_Pointer)
{
	unsigned char SVC_ID;
	SVC_ID = *((unsigned char *)(((unsigned char *)Stack_Pointer[6])-2));

	switch(SVC_ID)
	{
	case SVC_Activatetask:
	case SVC_terminateTask:
		//Update Sch Table, Ready Queue
		IsmailRTOS_UpdateSchedular();
		//if OS is in running state
		if(OS_Control.OS_state == OS_Running)
		{
			if(strcmp(OS_Control.CurrentTask->Task_Name,"Idle_Task") != 0)
			{
				//* decide what next
				Decide_WhatNext();

				//* trigger Pendsv to switch context and store
				Trigger_OS_PendSV();
			}
		}
		break;

	case SVC_TaskWaitingTime:
		IsmailRTOS_UpdateSchedular();
		break;
	}
}

void RTOS_OS_SVC_SET(SVC_ID_t SVC_ID)
{
	switch(SVC_ID)
	{
	case SVC_Activatetask:
		__asm volatile("SVC #0x00");
		break;

	case SVC_terminateTask:
		__asm volatile("SVC #0x01");
		break;

	case SVC_TaskWaitingTime:
		__asm volatile("SVC #0x02");
		break;
	}
}


void IsmailRTOS_ActivateTask(task_Typedef* task)
{
	task->Task_state = Waiting;
	RTOS_OS_SVC_SET(SVC_Activatetask);
}

void IsmailRTOS_DectivateTask (task_Typedef* task)
{
	task->Task_state = Suspend;
	RTOS_OS_SVC_SET(SVC_terminateTask);
}

void IsmailRTOS_TaskWait(unsigned int ticks,task_Typedef* task)
{
	task->TimingWaiting.Blocking = Enable;
	task->TimingWaiting.Waiting_Ticks = ticks;

	task->Task_state = Suspend;

	RTOS_OS_SVC_SET(SVC_terminateTask);
}

void MYRTOS_Update_TasksWaitingTime()
{
	for(int i = 0; i<OS_Control.number_ActiveTasks ;i++)
	{
		if(OS_Control.TaskTable[i]->Task_state == Suspend)
		{
			if(OS_Control.TaskTable[i]->TimingWaiting.Blocking == Enable)
			{
				OS_Control.TaskTable[i]->TimingWaiting.Waiting_Ticks--;
				if(OS_Control.TaskTable[i]->TimingWaiting.Waiting_Ticks == 1)
				{
					OS_Control.TaskTable[i]->TimingWaiting.Blocking = Disable;
					OS_Control.TaskTable[i]->Task_state = Waiting;
					RTOS_OS_SVC_SET(SVC_TaskWaitingTime);
				}
			}
		}
	}
}
void IsmailRTOS_STARTOS()
{
	OS_Control.OS_state = OS_Running;
	//Set Default "Current Task =Idle Task"
	OS_Control.CurrentTask = &Idle_task;
	//activate it
	IsmailRTOS_ActivateTask(&Idle_task);

	Start_ticker();

	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);

	OS_SWITCH_SP_to_PSP;

	OS_SWITCH_to_unprivileged;

	Idle_task.TaskEntry();


}

IsmailRTOS_errorID IsmailRTOS_AcquireMutex(Mutex_Typedef* mutex , task_Typedef* task)
{
	//not taken by anytask
	if(mutex->currentuser == NULL)
	{
		mutex->currentuser = task;
	}
	else
	{
		if(mutex->nextuser == NULL)
		{
			mutex->nextuser = task;
			task->Task_state = Suspend;

			RTOS_OS_SVC_SET(SVC_terminateTask);
		}
		else
		{
			return MutexisReacedToMaxNumberOfUsers;
		}
	}
	return NoError;
}

void IsmailRTOS_ReleaseMutex(Mutex_Typedef* mutex)
{
	if(mutex->currentuser != NULL)
	{
		mutex->currentuser = mutex->nextuser;
		mutex->nextuser = NULL;
		mutex->currentuser->Task_state = Waiting;
		RTOS_OS_SVC_SET(SVC_Activatetask);
	}
}




