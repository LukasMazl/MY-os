#include "io.h"
#include "task/task.h"
#include "logger/logger.h"
#include "keyboard/keyboard.h"

void* isr80h_command1_print(struct interrupt_frame* frame)
{
    void* user_space_msg_buffer = task_get_stack_item(task_current(), 0);
    char buf[1024];
    copy_string_from_task(task_current(), user_space_msg_buffer, buf, sizeof(buf));
    struct task* task = task_current();
    print("[");
    print(task->process->filename);
    print("] ");
    print(buf);
    return 0;
}


void* isr80h_command2_getkey(struct interrupt_frame* frame)
{
    char c = keyboard_pop();
    return (void*) ((int)c);
}

void* isr80h_command3_putchar(struct interrupt_frame* frame)
{
    char c = (char)(int)task_get_stack_item(task_current(), 0);
    putchar(c);
    return 0;
}