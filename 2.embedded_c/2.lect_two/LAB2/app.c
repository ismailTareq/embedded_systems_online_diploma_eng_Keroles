#include "uart.h"
unsigned char string_buffer[100] = "learn-in-depth:ismail";
void main(void)
{
	UART_SEND_STRING(string_buffer);
}