#include "common.h"
#include "descriptor_tables.h"
#include "screen.h"



void kernel_main(void) 
{
	init_descriptor_tables();
	
	/* Initialize terminal interface */
	terminal_initialize();
 	asm volatile ("int $0x3");
	asm volatile ("int $0x5");
	terminal_writestring("best os eveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeer\nabc");
}