NASM=nasm
CC=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINKER_FLAGS=-ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

linker: linker.ld kernel
	$(CC) -T linker.ld -o myos.bin $(LINKER_FLAGS)

kernel: kernel.c boot
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

boot: boot.asm kernel
	$(NASM) -felf32 boot.asm -o boot.o
