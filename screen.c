#include <stddef.h>
#include <stdint.h>
#include "common.h"
#include "screen.h"
 
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize() 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) 
	{
		for (size_t x = 0; x < VGA_WIDTH; x++) 
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
	move_cursor();
}

void scroll_down()
{
	//move everything up
	for(int i = 0; i < VGA_WIDTH*(VGA_HEIGHT-1); i++)
	{
		terminal_buffer[i] = terminal_buffer[i+VGA_WIDTH];
	}
	//clean the last line
	for(int i = 0; i < VGA_WIDTH; i++)
	{
		terminal_putentryat(' ', terminal_color, i, VGA_HEIGHT - 1);
	}
}
 
void terminal_putchar(char c) 
{
	if(c == '\n')
	{
		terminal_column = 0;
		if(++terminal_row == VGA_HEIGHT)
		{
			terminal_row--;
			scroll_down();
		}
		
	}
	else
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) 
		{
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
			{
				terminal_row--;
				scroll_down();
			}
		}
		
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
 
void terminal_read(void)
{
	return;
}

// Updates the hardware cursor.
void move_cursor()
{
   // The screen is 80 characters wide...
   uint16_t cursorLocation = terminal_row * 80 + terminal_column+1;
   outb(0x3D4, 14);                  // setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

void print_decimal(int num)
{
    
    if (num < 0)
    {
        putchar('-');
        num *= -1;
    }
    else if (num == 0)
        terminal_putchar('0');

    int mod = 1;

    while (mod < num)
        mod *= 10;

    mod /= 10;

    while (mod)
    {
        terminal_putchar('0' + num / mod);
        num = num % mod;
        mod /= 10;
    }
}
