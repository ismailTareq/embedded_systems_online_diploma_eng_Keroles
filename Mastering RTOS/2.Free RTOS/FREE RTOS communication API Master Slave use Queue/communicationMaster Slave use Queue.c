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

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "FreeRTOS.h"
#include "GPIO.h"
#include  "task.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "queue.h"

QueueHandle_t queue = NULL ;
TaskHandle_t TaskMaster = NULL ;
TaskHandle_t TaskSlave = NULL ;


void vTaskMasterHandle(void *Parms)
{
	uint8_t OnCommand = 0;
	uint8_t OffCommand = 1;

	while(1)
	{
		xQueueSend(queue,&OffCommand,(TickType_t)5);
		vTaskDelay(10);
		xQueueSend(queue,&OnCommand,(TickType_t)5);
		vTaskDelay(10);


	}
}

void vTaskSlaveHandle(void *Parms)
{
	uint8_t Command_Receive = 0;
	while(1)
	{
		xQueueReceive(queue, &Command_Receive, (TickType_t)5);
		if(Command_Receive == 0)
		{
				GPIO_WRITE_Pin(GPIOA, GPIO_PIN_13, GPIO_LOW);
		}
		else
		{
				GPIO_WRITE_Pin(GPIOA, GPIO_PIN_13, GPIO_HIGH);
		}
		vTaskDelay(10);


	}
}

void Hw_Init(void)
{
	GPIO_Config_t LED;
	LED.GPIO_PinNumber = GPIO_PIN_13;
	LED.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	LED.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	GPIO_Init(GPIOA, &LED);
}

int main(void)
{
	RCC_GPIOA_CLK_EN();

	Hw_Init();

	xTaskCreate(vTaskMasterHandle, "Master", 128, NULL, 1, TaskMaster);
	xTaskCreate(vTaskSlaveHandle, "Slave", 128, NULL, 2, TaskSlave);

	queue = xQueueCreate(10,sizeof(uint8_t));

	vTaskStartScheduler();

	/* Loop forever */
	for(;;);
}