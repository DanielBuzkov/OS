; Declare constants for the multiboot header.
MBALIGN  equ  1<<0              ; align loaded modules on page boundaries
MEMINFO  equ  1<<1              ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot
 
; Declare a multiboot header that marks the program as a kernel (magic
; values that are documented in the multiboot standard)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
; Allocates room for a small stack 

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .data
gdtr DW 0 ; For limit storage
     DD 0 ; For base storage

gdt  DD 0,0,0,0,0,0

; _start is specified as the entry point to the kernel. The bootloader will jump to this position once the kernel has been loaded. 
; Declare _start as a function symbol with the given symbol size.
section .text
global _start:function (_start.end - _start)
_start:
 
	; Stack set up
	mov esp, stack_top
 
	; Calling the high-level kernel
	extern kernel_main
	call kernel_main
 
	; Disablung interrupts
	cli
.end:
