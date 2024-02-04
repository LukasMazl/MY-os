#include "idt.h"
#include "kernel.h"
#include "config.h"
#include "memory/memory.h"
#include "io/io.h"

struct idt_desc idtr_descriptors[MYOS_TOTAL_INTERUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc* ptr);
extern void int21h();
extern void no_interrupt();

void idt_zero() {
    print("Divide zero");
}

void int21h_handler()
{
    print("Keyboard pressee");
    outb(0x20, 0x20);
}

void no_interrupt_handler()
{
    outb(0x20, 0x20);
}

void idt_set(int interrupt_no, void* address)
{
    struct idt_desc* desc = &idtr_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = (uint32_t) address >> 16;
}

void idt_init()
{ 
    memset(idtr_descriptors, 0, sizeof(idtr_descriptors));
    idtr_descriptor.limit = sizeof(idtr_descriptors)-1;
    idtr_descriptor.base = (uint32_t) idtr_descriptors;

    for (int i = 0; i < MYOS_TOTAL_INTERUPTS; i++)
    {
        idt_set(i, no_interrupt);    
    }

    idt_set(0, idt_zero);

    //Load the interrupt descriptor table 
    idt_load(&idtr_descriptors);
}
