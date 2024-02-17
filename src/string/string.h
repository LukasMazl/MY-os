#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

char tolower(char s1);
int strlen(const char* ptr);
int strnlen(const char* ptr, int max);
bool isdigit(char c);
int tonumericdigit(char c);
int strnlen_terminator(const char* str, int max, char terminator);
int istrncmp(const char* str1, const char* str2, int n);
int strcmp(const char* str1, const char* str2, int n);
char* int_to_char(int number);
char* strcpy(char* dest, char* src);
void strncpy(char* dest, const char* src, int size);

#endif