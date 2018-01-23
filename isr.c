#include "common.h"
#include "isr.h"
#include "kernel.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs)
{
   terminal_writestring("recieved interrupt: ");
   char num[2] = {(*regs).int_no + '0', 0};
   terminal_writestring(num);
   terminal_writestring("\n");
}