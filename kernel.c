#include "common.h"
#include "descriptor_tables.h"
#include "screen.h"
#include "isr.h"



void kernel_main(void) 
{
	init_descriptor_tables();
	register_interrupt_handler(33, keyboard_interrupt_handler);
	
	/* Initialize terminal interface */
	terminal_initialize();
	asm volatile ("sti");
 	asm volatile ("int $0x3");
	terminal_writestring("best os eveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeer\nabc");
	while(1)
	{
		asm volatile ("hlt");
	}
}