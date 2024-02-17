#ifndef CONFIG_H
#define CONFIG_H


#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10


#define MYOS_TOTAL_INTERRUPTS 512

// 100MB heap size
#define MYOS_HEAP_SIZE_BYTES 104857600
#define MYOS_HEAP_BLOCK_SIZE 4096
#define MYOS_HEAP_ADDRESS 0x01000000 
#define MYOS_HEAP_TABLE_ADDRESS 0x00007E00

#define MYOS_SECTOR_SIZE 512

#define MYOS_MAX_FILESYSTEMS 12
#define MYOS_MAX_FILE_DESCRIPTORS 512

#define MYOS_MAX_PATH 108

#define MYOS_TOTAL_GDT_SEGMENTS 6

#define MYOS_PROGRAM_VIRTUAL_ADDRESS 0x400000
#define MYOS_USER_PROGRAM_STACK_SIZE 1024 * 16
#define MYOS_PROGRAM_VIRTUAL_STACK_ADDRESS_START 0x3FF000
#define MYOS_PROGRAM_VIRTUAL_STACK_ADDRESS_END MYOS_PROGRAM_VIRTUAL_STACK_ADDRESS_START - MYOS_USER_PROGRAM_STACK_SIZE

#define MYOS_MAX_PROGRAM_ALLOCATIONS 1024
#define MYOS_MAX_PROCESSES 12

#define MYOS_TOTAL_ISR80H_COMMANDS 1024

#define USER_DATA_SEGMENT 0x23
#define USER_CODE_SEGMENT 0x1b
#endif