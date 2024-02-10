#include "kernel.h"
#include "logger/logger.h"
#include "string/string.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"


static struct paging_4gb_chunk* kernel_chunk = 0;
void kernel_main()
{
    terminal_initialize();
    print("Hello world!\ntest");

    // Initialize the heap
    kheap_init();
    
    // Init disk
    disk_search_and_init();
    

    // Initialize the interrupt descriptor table
    idt_init();

    // Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // Switch to kernel paging chunk
    paging_switch(kernel_chunk);


    // Enable paging
    enable_paging();

    // Enable the system interrupts
    enable_interrupts();

    struct path_root* pat = pathparser_parse("0:/bin/shell.exe", NULL);
    if(pat)
    {

    }
}