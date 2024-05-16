//startup.c
//ismail

#include <stdint.h>
void Reset_handler();
extern int main(void);
extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text ;
void Default_handler()
{
	Reset_handler();
}

void NMI_handler()__attribute__((weak,alias("Default_handler")));;
void HARD_FAULT_handler()__attribute__((weak,alias("Default_handler")));;
// booking 1024 byte in the .bss section through unintialized array of 256 element
static unsigned long Stack_top[256];

void (* const g_o_fn_vector[])() __attribute__((section(".vectors"))) ={
	// define the stack pointer as the address of the last element in the array
	(void(*)())	 ((unsigned long)Stack_top + sizeof(Stack_top)),
	&Reset_handler,
	&NMI_handler,
	&HARD_FAULT_handler
};
Reset_handler()
{
	int i;
	//copy data from ROM to RAM
	unsigned int data_size = (unsigned char *)&_E_data - (unsigned char *)&_S_data;
	unsigned char *ptr_src = ((unsigned char *)&_E_text);
	unsigned char *ptr_dst = ((unsigned char *)&_S_data);
	for(i=0;i<data_size;i++)
	{
		*ptr_dst++=*ptr_src++;
	}
	//initialize .bss with zero
	unsigned int bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss;
	unsigned char *bss_dst = ((unsigned char *)&_S_bss);
	for(i=0;i<bss_size;i++)
	{
		*bss_dst++=(unsigned char)0;
	}
	//jump to main
	main();
}
