#remove all comments for makefile + execute

NASM=nasm
CC=i686-elf-gcc
#QEMU=qemu-system-i386

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINKER_FLAGS=-ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

#run: linker
	#$(QEMU) -cdrom myos.iso

linker: linker.ld kernel
	$(CC) -T linker.ld -o myos.bin $(LINKER_FLAGS)

kernel: kernel.c boot
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

boot: boot.asm kernel
	$(NASM) -felf32 boot.asm -o boot.o
