#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

#include "common.h"
#include <stddef.h>
#include <stdint.h>

void init_descriptor_tables();



struct gdt_entry_struct
{
    uint16_t limit_low;           // The lower 16 bits of the limit.
    uint16_t base_low;            // The lower 16 bits of the base.
    uint8_t  base_middle;         // The next 8 bits of the base.
    uint8_t  access;              // Access flags, determine what ring this segment can be used in.
    uint8_t  granularity;
    uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

// This struct describes a GDT pointer
struct gdt_ptr_struct
{
    uint16_t limit;               
    uint32_t base;               
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

// A struct describing an interrupt gate
struct idt_entry_struct
{
    uint16_t base_lo;             // The lower 16 bits of the address of the interrupt
    uint16_t sel;                 // Kernel segment selector
    uint8_t  always0;             // always zero
    uint8_t  flags;               
    uint16_t base_hi;             // The upper 16 bits of the interrupt
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers
struct idt_ptr_struct
{
    uint16_t limit;
    uint32_t base;                
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

// extern ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif //DESCRIPTOR_TABLES_H

