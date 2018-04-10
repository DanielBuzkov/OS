#ifndef iSR_H
#define iSR_H

#include "common.h"

typedef struct registers
{
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

//isr function pointer
typedef void (*isr_t)(registers_t*);

//array of isr functions
isr_t interrupt_handlers[256];

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs);
// send reset to pic
void send_reset(uint32_t n);
//register isr functions
void register_interrupt_handler(uint8_t n, isr_t handler);

//keyboard isr
void keyboard_interrupt_handler(registers_t* regs);

void print_handle(registers_t* regs);

#endif //iSR_H
