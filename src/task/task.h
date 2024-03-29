#ifndef TASK_H
#define TASK_H

#include "config.h"
#include "process.h"
#include <stdint.h>
#include "memory/paging/paging.h"

struct interrupt_frame;
struct registers
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t ip;
    uint32_t cs;
    uint32_t flags;
    uint32_t esp;
    uint32_t ss;
} __attribute__((packed));

struct process;

struct task
{
    /**
     * The page directory of the task
     */
    struct paging_4gb_chunk* page_directory;

    // The registers of the task when the task is not running
    struct registers registers;

    // The process of the task
    struct process* process;

    // The next task in the linked list
    struct task* next;

    // Previous task in the linked list
    struct task* prev;
};

struct task* task_new();
int task_init(struct task* task, struct process* process);
int task_free(struct task* task);
struct task* task_get_next();
struct task* task_current();
int task_switch(struct task* task);
int task_page();

void task_run_first_ever_first_task();
void task_return(struct registers* regs);
void restore_general_purpose_registers(struct registers* regs);
void user_registers();
void task_save_state(struct task* task, struct interrupt_frame* frame);
void task_current_save_state(struct interrupt_frame* frame);
int copy_string_from_task(struct task* task, void* virtual, void* phys, int max);
void* task_get_stack_item(struct task* task, int index);
void* task_virtual_address_to_physical(struct task* task, void* virtual_address);
void task_next();

#endif