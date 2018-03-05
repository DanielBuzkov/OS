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

	/* Initialize terminal interface */
	terminal_initialize();

	
	if(mboot_ptr->mods_count > 0)
	{
   		uint32_t initrd_location = *((uint32_t*)mboot_ptr->mods_addr);

		// Initialise the initial ramdisk, and set it as the filesystem root.
   		fs_root = initialise_initrd(initrd_location);
		   
		uint32_t i = 0;
		struct dirent *node = 0;
		while ( (node = readdir_fs(fs_root, i)) != 0)
		{
			terminal_writestring("Found file ");
			terminal_writestring(node->name);
			fs_node_t *fsnode = finddir_fs(fs_root, node->name);

			terminal_writestring("\n contents: \"");
			char buf[256];
			uint32_t sz = read_fs(fsnode, 0, 256, buf);
			int j;
			for (j = 0; j < sz; j++)
			{
				terminal_putchar(buf[j]);
			}

			terminal_writestring("\"\n");
			
			i++;
		}

	}
	else
	{
		terminal_writestring("error loading initrd\n");
	}

	//turn on interrupts
	asm volatile ("sti");  

	//terminal_writestring("Welcome to O5\n");


	while(!isExit())
	{
		asm volatile ("hlt");
	}
}