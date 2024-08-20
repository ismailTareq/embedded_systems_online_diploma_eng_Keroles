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

#define OS_Stack_Size			512
#define TaskA_Stack_Size		100
#define TaskB_Stack_Size		100

extern unsigned int _estack;

//boundary of Main Stack Pointer (MSP)
unsigned int _S_MSP = (unsigned int)&_estack;
unsigned int _E_MSP;

//boundary of Process Stack Pointer of TaskA (PSP_TA)
unsigned int _S_PSP_TaskA;
unsigned int _E_PSP_TaskA;


//boundary of Process Stack Pointer of TaskB (PSP_TB)
unsigned int _S_PSP_TaskB;
unsigned int _E_PSP_TaskB;



void Clock_Init()
{
	//open clock of AFIO
	RCC_AFIO_CLK_EN();

	//open clock of GPIOA
	RCC_GPIOA_CLK_EN();

	//open clock of GPIOB
	RCC_GPIOB_CLK_EN();
}

uint8_t IRQ_Flag = 0;
uint8_t TaskA_Flag = 0;
uint8_t TaskB_Flag = 0;

#define Os_Set_PSP_VAL(address)  			__asm volatile("MOV r0,%[IN] \n\t MSR PSP,r0" : :[IN]"r" (address))

#define OS_SwitchTo_PSP 					__asm volatile("MRS r0,CONTROL \n\t MOV r1,#0x02 \n\t ORR r0,r0,r1 \n\t MSR CONTROL,r0")

#define OS_SwitchTo_MSP 					__asm volatile("MRS r0,CONTROL \n\t MOV r1,#0x05 \n\t AND r0,r0,r1 \n\t MSR CONTROL,r0")

#define OS_Generate_Exception_Inerrupt		__asm("SVC #0x3")

typedef enum
{
	privileged,
	unprivileged
}CPU_AccessLevel_t;

void switch_CPU_AccessLevel(CPU_AccessLevel_t CPU_AccessLevel)
{
	switch(CPU_AccessLevel)
	{
	case privileged:
		__asm(" mrs r3,CONTROL \n\t "
				" lsr r3,r3,#0x1 \n\t "
				" Lsl r3,r3,#0x1 \n\t "
				" msr CONTROL,r3 ");

		break;

	case unprivileged:

		__asm(" mrs r3,CONTROL \n\t "
				" orr r3,r3,#0x1 \n\t "
				" msr CONTROL,r3 ");
		break;
	}
}

void EXTI9_callback(void)
{

	if(IRQ_Flag = 0)
	{
		TaskA_Flag = 1;
		IRQ_Flag = 1;
	}
	else if(IRQ_Flag = 1)
	{
		TaskB_Flag = 1;
		IRQ_Flag = 0;
	}

}

int TaskA(int a, int b, int c)
{
	return a+b+c;
}

int TaskB(int a, int b, int c, int d)
{
	return a+b+c+d;
}

void Main_Os(void)
{
	//Os stack
	_E_MSP = _S_MSP - OS_Stack_Size;

	//TA stack
	_S_PSP_TaskA = _E_MSP - 8;
	_E_PSP_TaskA = _S_PSP_TaskA - TaskA_Stack_Size;

	//TB stack
	_S_PSP_TaskB = _E_PSP_TaskA - 8;
	_E_PSP_TaskB = _S_PSP_TaskB - TaskB_Stack_Size;

	while(1)
	{
		__asm("NOP");

		if(TaskA_Flag == 1)
		{
			//set PSP with _S_PSP_TaskA
			Os_Set_PSP_VAL(_S_PSP_TaskA);

			//set SP -> PSP
			OS_SwitchTo_PSP;

			//switch to unprivileged
			switch_CPU_AccessLevel(unprivileged);

			TaskA_Flag = TaskA(1,2,3);

			//switch to privileged
			OS_Generate_Exception_Inerrupt;

			//set SP -> MSP
			OS_SwitchTo_MSP;
		}
		else if(TaskB_Flag == 1)
		{
			//set PSP with _S_PSP_TaskA
			Os_Set_PSP_VAL(_S_PSP_TaskB);

			//set SP -> PSP
			OS_SwitchTo_PSP;

			//switch to unprivileged
			switch_CPU_AccessLevel(unprivileged);

			TaskB_Flag = TaskB(1,2,3,4);

			//switch to privileged
			OS_Generate_Exception_Inerrupt;

			//set SP -> MSP
			OS_SwitchTo_MSP;
		}

	}
}
void SVC_Handler(void)
{
	switch_CPU_AccessLevel(privileged);
}

int main(void)
{
	Clock_Init();



	EXTI_PINCONFIG_t EXTI_CFG;
	EXTI_CFG.EXTI_PIN = EXTI9PB9;
	EXTI_CFG.Trigger = EXTI_Trigger_RISING;
	EXTI_CFG.IRQ_EN = 1;
	EXTI_CFG.IRQ_CallBack = EXTI9_callback;
	EXTI_Init(&EXTI_CFG);

	Main_Os();

	/* Loop forever */
	while(1)
	{
		if(IRQ_Flag)
		{
			IRQ_Flag = 0;
		}

	}
}

