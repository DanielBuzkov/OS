#include "keyboard.h"

char toChar(int scanCode)
{
    return scanCodeToAscii[scanCode];
}

void commandHandler(char *command)
{
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
    }
    if(strcmp(command, "exit") == 0)
    {
        exit();
    }
}

int isExit()
{
    return exit_flag;
}

void exit()
{
    exit_flag = 1;
}

int pressed_enter()
{
    return ENTER;
}
