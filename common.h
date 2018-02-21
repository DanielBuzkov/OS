
#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);
void memset(uint8_t *dest, uint8_t val, uint32_t len);
int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strlen(const char* str);
char* get_command(char* str);
char* get_param(char* str);
size_t strlen(const char* str);
void trimwhitespace(char *str);

#endif // COMMON_H
