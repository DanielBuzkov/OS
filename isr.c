#include "common.h"
#include "isr.h"
#include "screen.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs)
{
    // Send reset signal pic
    send_reset(regs->int_no);

    //ignore timer interupt
    if(regs->int_no == 32)
    {
        return;
    }

    //call specific interrupt handler
    if (interrupt_handlers[regs->int_no] != 0)
    {
        interrupt_handlers[regs->int_no](regs);
    }
    
    /*terminal_writestring("recieved interrupt: ");
    char num[3] = {regs->int_no/10 + '0',regs->int_no%10+'0', 0};
    terminal_writestring(num);
    terminal_writestring("\n");*/
}

void send_reset(uint32_t n)
{
     if(n >= 40)
    {
        // Send reset signal to slave
        outb(0xA0, 0x20);
    }
     if(n >= 32)
    {
        // Send reset signal to master
        outb(0x20, 0x20);        
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void keyboard_interrupt_handler(registers_t* regs)
{
    uint8_t c = inb(0x60);
    char ascii = toChar(c);

    if(c == 14) //delete
        terminal_delete();
    else if(ascii == '\n')
    {
        uint8_t* buff;
        terminal_get_line(buff);
        commandHandler(buff);
        terminal_putchar(ascii);
    }
    else if(ascii != 0)
        terminal_putchar(ascii);
        
    return;
}

void print_handle(registers_t* regs)
{
    terminal_writestring(regs->ebx);
}
