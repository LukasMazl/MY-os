#ifndef PROCESS_H
#define PROCESS_H
#include <stdint.h>
#include <stddef.h>
#include "config.h"
#include "task.h"

#define PROCESS_FILE_TYPE_ELF 0
#define PROCESS_FILE_TYPE_BINARY 1

typedef unsigned char PROCESS_TYPE;

struct process_allocation
{
    void* ptr;
    size_t size;
};

struct command_argument
{
    char argument[512];
    struct command_argument* next;
};

struct process_argument
{
    int argc;
    char** argv;
};

struct process
{
    uint16_t id;

    char filename[MYOS_MAX_PATH];

    // Main process task
    struct task* task;

    PROCESS_TYPE filetype;

    // The memory (malloc) allocation of the process
    struct process_allocation allocations[MYOS_MAX_PROGRAM_ALLOCATIONS];

    // The physical pointer to the process memory
    union
    {
        void* ptr;
        struct elf_file* elf_file;
    };
    
    // The physical pointer to the stack memory
    void* stack;

    // The size of the data pointed to by "ptr"
    uint32_t size;

    struct keyboard_buffer
    {
        char buffer[MYOS_KEYBOARD_BUFFER_SIZE];
        int tail;
        int head;
    } keyboard;

    struct process_argument arguments;
};
int process_load(const char* filename,struct process** process);
struct process* process_current();
int process_switch(struct process* process);
int process_load_switch(const char* filename, struct process** process);
int process_load_for_slot(const char* filename, struct process** process, int process_slot);
void* process_malloc(struct process* process, size_t size);
void process_free(struct process* process, void* ptr_to_free);
void process_get_arguments(struct process* process, int* argc, char*** argv);
int process_inject_arguments(struct process* process, struct command_argument* root_argument);
int process_terminate(struct process* process);

#endif