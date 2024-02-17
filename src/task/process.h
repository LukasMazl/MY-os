#ifndef PROCESS_H
#define PROCESS_H
#include <stdint.h>
#include "config.h"
#include "task.h"

struct process
{
    uint16_t id;

    char filename[MYOS_MAX_PATH];

    // Main process task
    struct task* task;

    // The memory (malloc) allocation of the process
    void* allocations[MYOS_MAX_PROGRAM_ALLOCATIONS];

    // The physical pointer to the process memory
    void* ptr;

    // The physical pointer to the stack memory
    void* stack;

    // The size of the data pointed to by "ptr"
    uint32_t size;
};
int process_load(const char* filename,struct process** process);
int process_load_for_slot(const char* filename, struct process** process, int process_slot);
#endif