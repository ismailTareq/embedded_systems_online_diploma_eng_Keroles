/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "STM32F103X6.h"
#include "GPIO.h"
#include "LCD.h"
#include "EXTI.h"
#include "Scheduler.h"

task_Typedef TaskA , TaskB , TaskC;

void Task_A(void)
{
	while(1);
}

void Task_B(void)
{
	while(1);
}

void Task_C(void)
{
	while(1);
}

int main(void)
{
	IsmailRTOS_errorID errorID = Suspend;
	HW_init();

	if(IsmailRTOS_Init() != NoError)
	{
		while(1);
	}

	TaskA.stacksize = 1024;
	TaskA.priority = 8;
	TaskA.TaskEntry = Task_A;
	strcpy(TaskA.Task_Name , "Task_A");

	TaskB.stacksize = 1024;
	TaskB.priority = 8;
	TaskB.TaskEntry = Task_B;
	strcpy(TaskB.Task_Name , "Task_B");

	TaskC.stacksize = 1024;
	TaskC.priority = 8;
	TaskC.TaskEntry = Task_C;
	strcpy(TaskC.Task_Name , "Task_C");

	errorID += IsmailRTOS_CreateTask(&TaskA);
	errorID += IsmailRTOS_CreateTask(&TaskB);
	errorID += IsmailRTOS_CreateTask(&TaskC);

	while(1)
	{


	}
}

