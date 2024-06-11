#ifndef GPIO_H_
#define GPIO_H_
#include "Macros.h"
#include "Platform_Types.h"
#include <stdint.h>
typedef enum {
    GPIO_ENABLE_CLOCK,
    GPIO_INIT, 
    GPIO_ERROR,
	GPIO_WRITTEN
} GPIO_STATE;

// Base addresses for GPIO and RCC (Reset and Clock Control)
#define GPIO_PORTA   0x40010800
#define BASE_RCC     0x40021000

// Register addresses for GPIO configuration
#define APB2ENR      *(volatile uint32_t *)(BASE_RCC + 0x18)
#define GPIOA_CRL    *(volatile uint32_t *)(GPIO_PORTA + 0x00)
#define GPIOA_CRH    *(volatile uint32_t *)(GPIO_PORTA + 0x04)
#define GPIOA_IDR    *(volatile uint32_t *)(GPIO_PORTA + 0x08)
#define GPIOA_ODR    *(volatile uint32_t *)(GPIO_PORTA + 0x0C)

//APIS

GPIO_STATE Enable_clock(void);

GPIO_STATE GPIO_Initialization(void);

GPIO_STATE GPIO_Write_Pin(uint8 Port,uint8 Pin,uint8 Logic);
#endif // GPIO_H_