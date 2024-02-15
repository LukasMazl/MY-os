#include "string.h"
#include "memory/heap/kheap.h"
#include "logger/logger.h"

char tolower(char s1)
{
    if(s1 >= 65 && s1 <= 90)
    {
        return s1 += 32;
    }

    return s1;
}

int strlen(const char* ptr)
{
    int len = 0;
    while(*ptr != 0)
    {
        len++;
        ptr++;
    }
    return len;
}

int strnlen(const char* ptr, int max)
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        if(ptr[i] == 0)
        {
            break;
        }
    }
    return i;
}

bool isdigit(char c)
{
    return c >= 48 && c <= 57;
}

int tonumericdigit(char c)
{
    return c - 48;
}

int strnlen_terminator(const char* str, int max, char terminator)
{
    int i = 0;
    for(i = 0; i < max; i++)
    {
        if(str[i] == '\0' ||str[i] == terminator)
        break;
    }
    return i;
}

int istrncmp(const char* str1, const char* str2, int n)
{
    unsigned char u1, u2;
    while (n-- > 0)
    {
        u1 = (unsigned char) *str1++;
        u2 = (unsigned char) *str2++;
        if(u1 != u2 && tolower(u1) != tolower(u2))
            return u1 - u2;
        if(u1 == '\0' || u2 == '\0')
            return 0;
    }
    return 0;
}

char* int_to_char(int number)
{
    int len = 1;
    int tmp_number = number;
    while (tmp_number / 10)
    {
        len++;
        tmp_number /=  10;
    }
    
    char* str = kmalloc(len + 1);
    
    if(number == 0)
    {
        str[0] = '0';
    }
    
    for(int i = 0; number > 0; i++)
    {
        str[len - i - 1] = 48 + number % 10;
        number /= 10;
    }
    str[len] = 0x00;
    return str;
}

int strcmp(const char* str1, const char* str2, int n)
{
    unsigned char u1, u2;
    while (n-- > 0)
    {
        u1 = (unsigned char) *str1++;
        u2 = (unsigned char) *str2++;
        if(u1 != u2)
            return u1 - u2;
        if(u1 == '\0' || u2 == '\0')
            return 0;
    }
    return 0;
}

char* strcpy(char* dest, char* src)
{
    char* res = dest;
    while(*src != 0)
    {
        *dest = *src;
        src += 1;
        dest += 1;
    }

    *dest = 0x00;

    return res;
}