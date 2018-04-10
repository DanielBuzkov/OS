#include "keyboard.h"

char toChar(uint8_t scanCode)
{
    if(scanCode == ENTER)
        return '\n';
        
    if(scanCode < SCTA_LEN)
        return scanCodeToAscii[scanCode];
    
    return 0;
}


void commandHandler(char *str)
{
    //str = "color 1 2";
    fs_node_t *fsnode;

    char command[32] = {0}; 
    get_command(str, command);
    char param [48] = {0};
    get_param(str, param);


    if(strcmp(command, "help") == 0)
    {
        if(strcmp(param, "color") == 0)
        {
            terminal_writestring("\n--type in the following format : \n");
            terminal_writestring("--color [foreground] [background]\n");
            terminal_writestring("--BLACK = 0\n");
	        terminal_writestring("--BLUE = 1\n");
	        terminal_writestring("--GREEN = 2\n");
	        terminal_writestring("--CYAN = 3\n");
	        terminal_writestring("--RED = 4\n");
        	terminal_writestring("--MAGENTA = 5\n");
	        terminal_writestring("--BROWN = 6\n");
	        terminal_writestring("--LIGHT_GREY = 7\n");
    	    terminal_writestring("--DARK_GREY = 8\n");
	        terminal_writestring("--LIGHT_BLUE = 9\n");
	        terminal_writestring("--LIGHT_GREEN = 10\n");
	        terminal_writestring("--LIGHT_CYAN = 11\n");
	        terminal_writestring("--LIGHT_RED = 12\n");
        	terminal_writestring("--LIGHT_MAGENTA = 13\n");
	        terminal_writestring("--LIGHT_BROWN = 14\n");
	        terminal_writestring("--WHITE = 15\n");
        }
        else
        {
            terminal_writestring("\nO5 bush, version 2.1.3 \n");
            terminal_writestring("--Enter a file's name to execute it.\n");
            terminal_writestring("--Enter 'help' for help\n");
            terminal_writestring("--Enter 'print' with file name to print the content of the file\n");
            terminal_writestring("--Enter 'ls' to list  information  about  the FILEs (the current directory by default). \n");
            terminal_writestring("--Enter 'color' to change the color of text and background (type 'help color' for more)\n");
            terminal_writestring("--Enter 'clear' to clear the screen\n");
            terminal_writestring("--Enter 'exit' to exit\n");
        }
    }
    else if(strcmp(command, "ls") == 0)
    {
        terminal_writestring("\n");
        
        uint32_t i = 0;
		struct dirent *node = 0;

		while ( (node = readdir_fs(fs_root, i++)) != 0)
        {            
            terminal_writestring(node->name);
            terminal_writestring("  ");
        }
    }
    else if(strcmp(command, "echo") == 0)
    {
        terminal_writestring("\n");
        terminal_writestring(param);
    }
    else if(strcmp(command, "color") == 0)
    {
        char foreground_s[32] = {0}; 
        get_command(param, foreground_s);
        char background_s [48] = {0};
        get_param(param, background_s);

        uint8_t foreground = to_decimal(foreground_s);
        uint8_t background = to_decimal(background_s);

        if((background < 16 && background >= 0) && (foreground < 16 && foreground >= 0))
            change_color(foreground, background);
        else
        {
            terminal_writestring("\nInvalid color choice\n");
            terminal_writestring("type \"help color\" for more info\n");
        }
    }
    else if(strcmp(command, "clear") == 0)
        terminal_initialize();
    else if(strcmp(command, "print") == 0)
    {
        fsnode = finddir_fs(fs_root, param);

        if(fsnode == 0)
        {
            terminal_writestring("\nError : file \"");
            terminal_writestring(param);
            terminal_writestring("\" not found\n");
        }
        else
        {
            char buffer[256];
            uint32_t sz = read_fs(fsnode, 0, 256, buffer);

            terminal_putchar('\n');
            
            uint32_t j = 0;
            for (j = 0; j < sz; j++)
			{
				terminal_putchar(buffer[j]);
			}

            terminal_putchar('\n');
        }
    }
    else if( (fsnode = finddir_fs(fs_root, command)) != 0 )
    {
        if(fsnode->flags == FS_EXEC)
        {
            terminal_writestring("\n");
            exec_fs(fsnode);
        }
        else
        {
            terminal_writestring("\nfile not executable\n");
        }
    }
    else if(strcmp(command, "exit") == 0)
    {
        exit_flag = 0;
    }
    else
    {
        terminal_writestring("\nCommand or file '");
        terminal_writestring(command);
        terminal_writestring("' not found\n");
    }
}

uint8_t is_exit()
{
    return exit_flag;
}

uint8_t pressed_enter()
{
    return ENTER;
}