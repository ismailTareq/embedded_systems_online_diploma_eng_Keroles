/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */

//standard id
//sending data frame
void CAN_TX(uint32_t ID ,uint8_t DLC , uint8_t* DATA ){

	uint8_t TxMailbox, free_TXMailBox=0;

	CAN_TxHeaderTypeDef pHeader;
	pHeader.DLC=DLC;
	pHeader.IDE=CAN_ID_STD;
	pHeader.RTR=CAN_RTR_DATA;
	pHeader.StdId=ID;

	//get the number of free Tx mailboxes.
	free_TXMailBox=HAL_CAN_GetTxMailboxesFreeLevel(&hcan);

	if(free_TXMailBox)
	{

		//request transmission of a new message.
		if(	HAL_CAN_AddTxMessage(&hcan, &pHeader, DATA, &TxMailbox) != HAL_OK){

			Error_Handler();
		}

		//check if a message is pending  in a Tx mailbox.
		while(HAL_CAN_IsTxMessagePending(&hcan, TxMailbox));

	}
}

void CAN_RX_Filter(uint16_t STD_FILTER_ID,uint16_t STD_FILTER_MASK)
{
	CAN_FilterTypeDef FilterConfig;

	FilterConfig.FilterActivation=CAN_FILTER_ENABLE;
	FilterConfig.FilterBank=0;
	FilterConfig.FilterFIFOAssignment=CAN_FILTER_FIFO0;
	FilterConfig.FilterIdHigh=  STD_FILTER_ID << 5;
	FilterConfig.FilterIdLow=0x0000;
	FilterConfig.FilterMaskIdHigh= STD_FILTER_MASK << 5;
	FilterConfig.FilterMaskIdLow=0x0000;
	FilterConfig.FilterMode= CAN_FILTERMODE_IDMASK ;
	FilterConfig.FilterScale=CAN_FILTERSCALE_32BIT;

	if(HAL_CAN_ConfigFilter(&hcan, &FilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

}
void CAN_RX(uint32_t* ID ,uint8_t* DLC , uint8_t* DATA)
{
	CAN_RxHeaderTypeDef Header;

	while(HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_FILTER_FIFO0)==0);

	if(HAL_CAN_GetRxMessage(&hcan, CAN_FILTER_FIFO0, &Header, DATA) != HAL_OK)
	{
		Error_Handler();
		*ID=Header.StdId;
		*DLC=Header.DLC;
	}
}

int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CAN_Init();
	CAN_RX_Filter(0x3FF,0x7FF);
	//start CAN
	if(HAL_CAN_Start(&hcan) != HAL_OK )
	{
		Error_Handler();
	}

	uint8_t DATA_TX[8]={ 'C','A','N',' ','N','O',':',' '};
	uint8_t Frame_no=0;
	uint8_t DATA_RX[8];
	uint16_t RX_ID,RX_DLC;
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		DATA_TX[7]=Frame_no++;
		CAN_TX(0x3FF, 8, DATA_TX);
		CAN_RX(&RX_ID, &RX_DLC, DATA_RX);
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief CAN Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN_Init(void)
{

	/* USER CODE BEGIN CAN_Init 0 */

	/* USER CODE END CAN_Init 0 */

	/* USER CODE BEGIN CAN_Init 1 */

	/* USER CODE END CAN_Init 1 */
	hcan.Instance = CAN1;
	hcan.Init.Prescaler = 1;
	hcan.Init.Mode = CAN_MODE_LOOPBACK;
	hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
	hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan.Init.TimeTriggeredMode = DISABLE;
	hcan.Init.AutoBusOff = DISABLE;
	hcan.Init.AutoWakeUp = DISABLE;
	hcan.Init.AutoRetransmission = ENABLE;
	hcan.Init.ReceiveFifoLocked = DISABLE;
	hcan.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN CAN_Init 2 */

	/* USER CODE END CAN_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
