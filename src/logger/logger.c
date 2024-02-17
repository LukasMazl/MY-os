#include "logger.h"
#include "string/string.h"
#include "kernel.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;
uint8_t current_logger_level = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}
void terminal_initialize()
{
    video_mem = (uint16_t*)(INIT_TERMINAL_ADDR);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}

void printc(const char* str, int color)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], color);
    }
}

void print(const char* str)
{
    printc(str, 15);   
}

void println(const char* message)
{
    print(message);
    print("\n");
}

void eprint(const char* message)
{
    if(current_logger_level < LOG_ERROR)
    {
        print("[ ");
        printc("ERROR", 8);
        print("] ");
        println(message);
    }
}

void printe(int e)
{
    print("Error status: ");
    print(int_to_char(e*-1));
    print("\n");
    panic("ERROR!!!!!");
}