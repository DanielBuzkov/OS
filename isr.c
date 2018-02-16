#include "common.h"
#include "isr.h"
#include "screen.h"
#include "keyboard.h"

char *command = "";

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
    
    terminal_writestring("recieved interrupt: ");
    char num[3] = {regs->int_no/10 + '0',regs->int_no%10+'0', 0};
    terminal_writestring(num);
    terminal_writestring("\n");

    //Put next code when keyboard interupt is called
    if (regs->int_no == pressed_enter())
    {
        terminal_read(command); //This function will put into 'command' whatever is written on the screen
        commandHandler(command);
    }
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
    char num[4] = {c/100 + '0',(c/10)%10+'0',c%10+'0', 0};
    terminal_writestring(num);
    terminal_writestring("\n");
}
