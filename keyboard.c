#include "keyboard.h"

char toChar(uint8_t scanCode)
{
    if(scanCode < SCTA_LEN)
        return scanCodeToAscii[scanCode];
    if(scanCode == 28)
        return '\n';
    return 0;
}

void commandHandler(char *str)
{
    char command[32] = {0}; 
    get_command(str, command);
    char param [48] = {0};
    get_param(str, param);

    if(strcmp(command, "help") == 0)
    {
        terminal_writestring("O5 bush, version 1.0 - release (x86-pc-linux)\n");
        terminal_writestring("Enter a file's name to execute it.\n");
        terminal_writestring("Enter 'help' for help\n");
        terminal_writestring("Enter 'ls' to list  information  about  the FILEs (the current directory by default). \n");
        terminal_writestring("Enter 'exit' to exit\n");
    }
    if(strcmp(command, "ls") == 0)
    {
        //DO IT L8ER
        terminal_writestring(" am in ls\n");
    }
    if(strcmp(command, "exit") == 0)
    {
        terminal_writestring("am in exit\n");
        exit();
    }
}

uint8_t isExit()
{
    return exit_flag;
}

void exit()
{
    exit_flag = 1;
}

uint8_t pressed_enter()
{
    return ENTER;
}