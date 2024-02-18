#include "stdio.h"
#include "stdlib.h"
#include "myos.h"

int main(int argc, char** argv)
{
    printf("Hello how are you??\n");
    print(itoa(1343));
    putchar('a');
    while(1)
    {
        if(getkey() != 0)
        {
            print("Key was pressed!");
        }
    }
    return 0;
}