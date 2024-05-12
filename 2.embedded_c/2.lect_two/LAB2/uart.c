#include "uart.h"

#define UART0DR *((volatile unsigned int* )((unsigned int*)0x101f1000))

void UART_SEND_STRING(unsigned char* ptr_TX_string)
{
	while(*ptr_TX_string != '\0')
	{
		UART0DR = (unsigned int)(*ptr_TX_string);
		ptr_TX_string++;
	}
		
}