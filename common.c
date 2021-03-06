#include "common.h"
#include <stddef.h>

// Write a byte out to the specified port.
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void outw(uint16_t port, uint16_t value)
{
    asm volatile ("outw %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// Copy len bytes from src to dest.
void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len)
{
    const uint8_t *sp = (const uint8_t *)src;
    uint8_t *dp = (uint8_t *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

// Write len copies of val into dest.
void memset(uint8_t *dest, uint8_t val, uint32_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
uint32_t strcmp(char *str1, char *str2)
{
      uint32_t i = 0;
      uint32_t failed = 0;
      while(str1[i] != '\0' && str2[i] != '\0')
      {
          if(str1[i] != str2[i])
          {
              failed = 1;
              break;
          }
          i++;
      }
      // why did the loop exit?
      if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
          failed = 1;
  
      return failed;
}

uint32_t memcmp(char *str1, char *str2, uint32_t len)
{
      uint32_t i = 0;
      uint32_t failed = 0;
      while(str1[i] != '\0' && str2[i] != '\0' && len-- > 0)
      {
          if(str1[i] != str2[i])
          {
              failed = 1;
              break;
          }
          i++;
      }
      // why did the loop exit?
      if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
          failed = 1;
  
      return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src)
{
    do
    {
      *dest++ = *src++;
    }
    while (*src != 0);
    return dest;
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src)
{
    while (*dest != 0)
    {
        *dest = *dest++;
    }

    do
    {
        *dest++ = *src++;
    }
    while (*src != 0);
    return dest;
}

size_t strlen(const char* str) 
{
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

void get_command(char* str, char* command)
{
    int i = 0;
    while (str[i] != ' ' && i < strlen(str))
    {
        command[i] = str[i];
        i++;
    }

    command[i] = '\0';
}

void get_param(char* str, char* param)
{
    int i = 0, j = 0;
    while(i < strlen(str) && str[i++] != ' ');
    
    while(i < strlen(str))
        param[j++] = str[i++];
    
    param[i] = '\0';

}

void trimwhitespace(char *str)
{
    char *end;

    // Trim leading space
    while((char)*str == ' ') str++;

    if(*str == 0)  // All spaces?
    return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && (char)*end == ' ') end--;

    // Write new null terminator
    *(end+1) = 0;
}

uint8_t to_decimal(char* str)
{
    //no negatives
    uint8_t ret = 0, i = 0;
    char* temp = str;
    
    for (i = 0; i < strlen(temp); i++)
    {
        ret *= 10;
        ret += temp[i] - '0';
    }
    
    return ret;
}
