#include "io.h"
#include "task/task.h"
#include "logger/logger.h"

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