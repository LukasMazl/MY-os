#include "kernel.h"
#include "logger/logger.h"
#include "string/string.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "keyboard/keyboard.h"
#include "isr80h/isr80h.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "fs/file.h"
#include "task/tss.h"
#include "gdt/gdt.h"
#include "task/task.h"
#include "task/process.h"
#include "config.h"
#include "memory/memory.h"
#include "status.h"

static struct paging_4gb_chunk* kernel_chunk = 0;
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

void panic(const char* message)
{
    println(message);
    while(1) {}
}

void kernel_page()
{
    kernel_registers();
    paging_switch(kernel_chunk);   
}

void pic_timer_callback()
{
    println("Timer actived");
}

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
    println("Heap init");
    
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
    println("enabled paging");

    isr80_register_commands();

    keyboard_init();

    //idt_register_interrupt_callback(0x20, pic_timer_callback);

    struct process* process = 0;
    int res = process_load_switch("0:/shell.elf", &process);
    if(res != MYOS_ALL_OK)
    {
       // printe(res);
        panic("Failed to load blank.elf");
    }

    struct command_argument argument;
    argument.next = 0x00;
    strcpy(argument.argument, "Testing!");
    
    process_inject_arguments(process, &argument);

    task_run_first_ever_first_task();
    println("Kernel init done");
    while (1) { }
    
}