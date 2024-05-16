/* linker_script cortexM4
ismail
*/


MEMORY
{
 	FLASH(RX)  : ORIGIN = 0X00000000 , LENGTH = 512M
	SRAM(RWX)  : ORIGIN = 0X20000000 , LENGTH =	512M

}

SECTIONS
{
	
	.text : 
	{
		*(.vectors*) 
		*(.text*) 
		*(.rodata)
		_E_text = .;
	}> FLASH
	.data :
	{   _S_data = .;
		*(.data*)
		. = ALIGN(4);
		_E_data = .;

	}>SRAM AT> FLASH
	.bss  :
	{   _S_bss = .;
		*(.bss*)
		_E_bss = .;
	}> SRAM

}