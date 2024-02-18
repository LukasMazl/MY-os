#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

#define LOG_ALL     0
#define LOG_DEBUG   1
#define LOG_ERROR   2
#define LOG_WARN    3
#define LOG_INFO    4


#define INIT_TERMINAL_ADDR 0xB8000

void printc(const char* str, int color);
void print(const char* str);
void println(const char* str);
void eprint(const char* message);
void terminal_initialize();

void putchar(char c);
void printe(int e);

#endif