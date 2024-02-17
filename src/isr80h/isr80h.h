#ifndef ISR80H_H
#define ISR80H_H

enum SystemCommands
{
    SYSTEM_COMMAND0_SUM,
    SYSTEM_COMMNAD1_PRINT
};

void isr80_register_commands();

#endif