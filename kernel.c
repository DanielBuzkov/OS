#include "common.h"
#include "descriptor_tables.h"
#include "screen.h"

//#include "keyboard.h"


#include "isr.h"

//Called from boot.asm
void kernel_main(void) 
{

	init_descriptor_tables(); //descriptor_table.c
	register_interrupt_handler(33, keyboard_interrupt_handler);


	init_descriptor_tables();
	register_interrupt_handler(33, keyboard_interrupt_handler);
	

	/* Initialize terminal interface */
	terminal_initialize();
	asm volatile ("sti");  
 	asm volatile ("int $0x3");
	terminal_writestring("Welcome to O5\n");
	while(!isExit())
	{
		asm volatile ("hlt");
	}
}