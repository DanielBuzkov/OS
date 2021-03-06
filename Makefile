OBJECTS = kernel.o descriptor_tables.o dt.o boot.o common.o interupts.o screen.o keyboard.o isr.o initrd.o fs.o power_off.o
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS = -ffreestanding -O2 -nostdlib -lgcc
CC = i686-elf-gcc
NASM = nasm -felf32
TARGET = myos.bin
LD = linker.ld

.PHONY: all clean
        
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -T $(LD) -o $(TARGET) $(LFLAGS) $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

%.o : %.asm
	$(NASM) $<

clean:
	rm *.o
	rm $(TARGET)
