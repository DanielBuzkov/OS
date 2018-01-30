#include "common.h"
#include "isr.h"
#include "screen.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs)
{
    terminal_writestring("recieved interrupt: ");
    char num[2] = {regs->int_no + '0', 0};
    terminal_writestring(num);
    terminal_writestring("\n");
    if(regs->int_no >= 40)
    {
        // Send reset signal to slave
        outb(0xA0, 0x20);
    }
    if(regs->int_no >= 40)
    {
        // Send reset signal to master
        outb(0x20, 0x20);
    }
}