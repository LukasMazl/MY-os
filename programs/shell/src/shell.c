#include "shell.h"
#include "stdio.h"
#include "myos.h"
#include <stdbool.h>

int main(int argc, char** argv)
{
    printf("MyOs v1.0.0");
    while (1)
    {
        printf("\n>> ");
        char buf[1024];
        myos_terminal_readline(buf, sizeof(buf), true);
        myos_process_load_start(buf);
    }
    
    return 0;
}