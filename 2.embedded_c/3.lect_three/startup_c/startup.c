//startup.c
//ismail

#include <stdint.h>
void Reset_handler();
extern int main(void);
void Default_handler()
{
	Reset_handler();
}

void NMI_handler()__attribute__((weak,alias("Default_handler")));;
void HARD_FAULT_handler()__attribute__((weak,alias("Default_handler")));;
void MM_handler()__attribute__((weak,alias("Default_handler")));;
void BUS_handler()__attribute__((weak,alias("Default_handler")));;
void USAGE_FAULT_handler()__attribute__((weak,alias("Default_handler")));;

uint32_t vectors[] __attribute__((section(".vectors"))) = {

	(uint32_t)0x20001000,
	(uint32_t)&Reset_handler,
	(uint32_t)&NMI_handler,
	(uint32_t)&HARD_FAULT_handler,
	(uint32_t)&MM_handler,
	(uint32_t)&BUS_handler,
	(uint32_t)&USAGE_FAULT_handler
};
extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text ;
extern unsigned int _STACK_SP ;
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
