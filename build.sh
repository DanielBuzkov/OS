#!/bin/bash
nasm -felf32 boot.asm -o boot.o
nasm -felf32 dt.asm -o dt.o
i686-elf-gcc -c descriptor_tables.c -o descriptor_tables.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c common.c -o common.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o common.o descriptor_tables.o dt.o -lgcc
mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir