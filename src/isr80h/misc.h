#ifndef MISC_H
#define MISC_H
#include "idt/idt.h"

void* isr80h_command0_sum(struct interrupt_frame* frame);
#endif