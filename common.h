
#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);
void memset(uint8_t *dest, uint8_t val, uint32_t len);
uint32_t strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
void get_command(char* str, char* command);
void get_param(char* str, char* param);
size_t strlen(const char* str);
void trimwhitespace(char *str);

#endif // COMMON_H
