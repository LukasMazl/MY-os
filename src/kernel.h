#ifndef KERNEL_H
#define KERNEL_H

void kernel_main();
void panic(const char* message);
void kernel_page();
void kernel_registers();


#define ERROR(value) (void*)(value)
#define ERROR_I(value) (int)(value)
#define ISERR(value) ((int)value) < 0
#endif