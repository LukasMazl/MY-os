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
#include "fs/file.h"
#include "task/tss.h"
#include "gdt/gdt.h"
#include "config.h"
#include "memory/memory.h"

void panic(const char* message)
{
    println(message);
    while(1) {}
}

struct tss tss;

struct gdt gdt_real[MYOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[MYOS_TOTAL_GDT_SEGMENTS] = 
{
    {.base = 0x00, .limit = 0x00, .type = 0x00}, // NULL segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a}, // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92}, // Kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8}, // User code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},  // User data segment
    {.base = (uint32_t)&tss, .limit=sizeof(tss), .type= 0xE9} //TSS segment
};

static struct paging_4gb_chunk* kernel_chunk = 0;
void kernel_main()
{
    terminal_initialize();
    println("Hello world!");

    // GDT
    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, MYOS_TOTAL_GDT_SEGMENTS);
    gdt_load(gdt_real, sizeof(gdt_real));


    // Initialize the heap
    kheap_init();
    
    //Init filesystem
    fs_init();

    // Init disk
    disk_search_and_init();
    
    // Initialize the interrupt descriptor table
    idt_init();

    // Setup TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // Load tss
    tss_load(0x28);

    // Setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // Switch to kernel paging chunk
    paging_switch(kernel_chunk);

    // Enable paging
    enable_paging();

    // Enable the system interrupts
    enable_interrupts();

    int fd = fopen("0:/hello.txt", "r");
    if(fd)
    {
        struct file_stat s;
        fstat(fd, &s);
        println(int_to_char(s.filesize));
    }
    while (1) { }
    
}