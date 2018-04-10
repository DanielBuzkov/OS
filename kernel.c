#include "common.h"
#include "descriptor_tables.h"
#include "screen.h"
#include "multiboot.h"
#include "fs.h"
#include "initrd.h"

//#include "keyboard.h"

#include "isr.h"

//Called from boot.asm
void kernel_main(multiboot_info_t* mboot_ptr) 
{

	init_descriptor_tables(); //descriptor_table.c
	register_interrupt_handler(33, keyboard_interrupt_handler);
	register_interrupt_handler(31, print_handle);

	/* Initialize terminal interface */
	terminal_initialize();
	change_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLUE);

	
	if(mboot_ptr->mods_count > 0)
	{
   		uint32_t initrd_location = *((uint32_t*)mboot_ptr->mods_addr);

		// Initialise the initial ramdisk, and set it as the filesystem root.
   		fs_root = initialise_initrd(initrd_location);

		terminal_writestring("Welcome to O5!\n");


	}
	else
	{
		terminal_writestring("error loading initrd\n");
	}

	//turn on interrupts
	asm volatile ("sti");  

	while(is_exit())
	{
		asm volatile ("hlt");
	}

	terminal_writestring("Good Bye Sweety :) <3\n");
}
