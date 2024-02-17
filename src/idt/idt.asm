section .asm

extern int21h_handler
extern no_interrupt_handler
extern isr80h_handler

global int21h
global idt_load
global no_interrupt
global enable_interrupts
global disable_interrupts
global isr80h_wrapper

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret


idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]
    pop ebp    
    ret


int21h:
    pushad
    call int21h_handler
    popad
    iret

no_interrupt:
    pushad
    call no_interrupt_handler
    popad
    iret

isr80h_wrapper:
    ; Interrupt FRAME START
    ; ALREADZ PUSHED TO US BY THE PROCESSOR UPON ENTRY TO THIS EINTERRUPT
    ; Push the general purpose registers to the stack
    pushad
    
    ; Push the stack pointer so that we are pointing to the interrupet frame
    push esp

    ; Command which kernel should execute
    push eax
    call isr80h_handler
    mov dword[tmp_res], eax
    add esp, 8

    ; Restore GP registers
    popad
    mov eax, [tmp_res]
    iretd

section .data
; Inside here is stored the return result from isr80h handler
tmp_res: dd 0