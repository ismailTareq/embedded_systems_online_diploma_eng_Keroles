#include "GPIO.h"
#include "USART.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "string.h"
#include "RSA.h"

#define UART_1       1
#define UART_2       2

// RSA Variables
int p = 61;
int q = 53;
int Totient = 0;
int n = 0;
int e = 0;
int d = 0;
int Encryption_Message = 0;
int Decryption_Message = 0;

// Task Handles
TaskHandle_t Original_message_Task1 = NULL;
TaskHandle_t Encryption_Task2 = NULL;
TaskHandle_t Display_Encrypted_Task3 = NULL;

// Semaphores
SemaphoreHandle_t Semaphore_Display_Org_Msg = NULL;
SemaphoreHandle_t Semaphore_Start_Encryption = NULL;
SemaphoreHandle_t Semaphore_Display_Encrpted_Msg = NULL;

// Task Handlers
void Original_message_task1_Handler(void* params);
void EncryptionTask2_Handler(void* params);
void Display_EncryptedTask3_Handler(void* params);

//UART Variable
volatile int USART2_Receive_Org_Msg = 0;
volatile int Temp_Receive_Org_Msg = 0;
char Rec_Data_UART2;
char Rec=5;
char Buf_Print_Transmit_Org_Msg[50];
char buffer_Encryption[50];
char bufferToSendToUART1[10];
volatile char flag = 0;
char Buff_NewLine[2] = "\n";

// USART Callback Function
void USART2_callBack()
{
    UART_ReceiveData(USART2, &Rec_Data_UART2, disable);
    UART_SendData(USART2, &Rec_Data_UART2, disable);
    if(flag == 0)
    {
        Temp_Receive_Org_Msg = (Rec_Data_UART2 - '0') * 10;
        flag = 1;
    }
    else
    {
        USART2_Receive_Org_Msg = Temp_Receive_Org_Msg + (Rec_Data_UART2 - '0');
        xSemaphoreGiveFromISR(Semaphore_Display_Org_Msg, NULL);
        xSemaphoreGiveFromISR(Semaphore_Start_Encryption, NULL);
        flag = 0;
    }
}

// USART Initialization Function
void USART_Init()
{
    USART_Config_t Uartcfg1;
    Uartcfg1.DATA_LENGTH = UART_DATA_Length_8B;
    Uartcfg1.STOPBITS = UART_1StopBits;
    Uartcfg1.USART_MODE = UART_MODE_TX_RX;
    Uartcfg1.PARITY = UART_NOParity;
    Uartcfg1.IQR_ENABLE = UART_IRQ_Enable_RXNEIE;
    Uartcfg1.FLOW_CONTROL = UART_HwFlowCtl_NONE;
    Uartcfg1.USART_BAUDRATE = UART_BaudRate_115200;
    UART_Init(USART1, &Uartcfg1);
    UART_GPIO_Set_Pins(USART1);

    USART_Config_t Uartcfg2;
    Uartcfg2.DATA_LENGTH = UART_DATA_Length_8B;
    Uartcfg2.STOPBITS = UART_1StopBits;
    Uartcfg2.USART_MODE = UART_MODE_TX_RX;
    Uartcfg2.PARITY = UART_NOParity;
    Uartcfg2.IQR_ENABLE = UART_IRQ_Enable_RXNEIE;
    Uartcfg2.IRQ_CallBack = USART2_callBack;
    Uartcfg2.FLOW_CONTROL = UART_HwFlowCtl_NONE;
    Uartcfg2.USART_BAUDRATE = UART_BaudRate_115200;
    UART_Init(USART2, &Uartcfg2);
    UART_GPIO_Set_Pins(USART2);
}

// RSA Initialization Function
void RSA_Init()
{
    n = Calculate_n(p, q);
    Totient = Calculate_Totient_Function(p, q);
    e = Generate_PuplicKey(Totient);
    d = Generate_PrivateKey(Totient, e);
}

// Clock Initialization Function
void Clock_Init()
{
    RCC_GPIOA_CLK_EN();
    RCC_GPIOB_CLK_EN();
    RCC_GPIOC_CLK_EN();
    RCC_AFIO_CLK_EN();
}

int main(void)
{
    Clock_Init();
    USART_Init();
    RSA_Init();

    strcpy(Buf_Print_Transmit_Org_Msg, "Transmit The Original Msg: ");
    for (int i = 0; i < strlen(Buf_Print_Transmit_Org_Msg); ++i)
    {
        UART_SendData(USART2, &Buf_Print_Transmit_Org_Msg[i], disable);
    }

    // Create Semaphores
    Semaphore_Display_Org_Msg = xSemaphoreCreateBinary();
    Semaphore_Start_Encryption = xSemaphoreCreateBinary();
    Semaphore_Display_Encrpted_Msg = xSemaphoreCreateBinary();

    // Create Tasks
    xTaskCreate(Original_message_task1_Handler, "Original_message_task1", 128, NULL, 1, Original_message_Task1);
    xTaskCreate(EncryptionTask2_Handler, "EncryptionTask2", 128, NULL, 2, Encryption_Task2);
    xTaskCreate(Display_EncryptedTask3_Handler, "Display_EncryptedTask3", 128, NULL, 2, Display_Encrypted_Task3);

    // Start Scheduler
    vTaskStartScheduler();

    while(1) {}

    return 0;
}

// Original Message Task Handler
void Original_message_task1_Handler(void* params)
{
    char buffer[50] = "\nTransmit The Original Msg: ";
    while(1)
    {
        if(xSemaphoreTake(Semaphore_Display_Org_Msg, (TickType_t) 5) == pdTRUE)
        {
            for (int i = 0; i < strlen(buffer); ++i)
            {
                UART_SendData(USART2, &buffer[i], disable);
            }
        }
        vTaskDelay(50);
    }
}

// Encryption Task Handler
void EncryptionTask2_Handler(void* params)
{
    while(1)
    {
        if(xSemaphoreTake(Semaphore_Start_Encryption, (TickType_t) 5) == pdTRUE)
        {
            Encryption_Message = RSA_Encryption(USART2_Receive_Org_Msg, n, e);
            xSemaphoreGive(Semaphore_Display_Encrpted_Msg);
        }
        vTaskDelay(15);
    }
}

// Display Encrypted Message Task Handler
void Display_EncryptedTask3_Handler(void* params)
{
    while(1)
    {
        if(xSemaphoreTake(Semaphore_Display_Encrpted_Msg, (TickType_t) 5) == pdTRUE)
        {
            strcpy(buffer_Encryption, "Encrypted message is: ");
            for (int i = 0; i < strlen(buffer_Encryption); ++i)
            {
                UART_SendData(USART1, &buffer_Encryption[i], disable);
            }

            itoa(Encryption_Message, bufferToSendToUART1, 10);
            for (int i = 0; i < strlen(bufferToSendToUART1); ++i)
            {
                UART_SendData(USART1, &bufferToSendToUART1[i], disable);
            }

            for (int i = 0; i < strlen(Buff_NewLine); ++i)
            {
                UART_SendData(USART1, &Buff_NewLine[i], disable);
            }
        }
        vTaskDelay(30);
    }
}
