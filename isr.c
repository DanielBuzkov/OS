#include "common.h"
#include "isr.h"
#include "screen.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs)
{
     if(regs->int_no >= 40)
    {
        // Send reset signal to slave
        outb(0xA0, 0x20);
    }
    if(regs->int_no >= 32)
    {
        // Send reset signal to master
        outb(0x20, 0x20);
    }
    if(regs->int_no == 32)
    {
        return;
    }
    if(regs->int_no == 33)
    {
        uint8_t c = inb(0x60);
        char num[4] = {c/100 + '0',(c/10)%10+'0',c%10+'0', 0};
        terminal_writestring(num);
        terminal_writestring("\n");
    }
    terminal_writestring("recieved interrupt: ");
    char num[3] = {regs->int_no/10 + '0',regs->int_no%10+'0', 0};
    terminal_writestring(num);
    terminal_writestring("\n");
}