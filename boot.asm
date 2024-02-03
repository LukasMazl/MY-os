ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0:step2

step2:
    cli ; Clear interrupts
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    sti ; Enables Interrupts
    
.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32

;GDT
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0
gdt_code:
    dw 0xffff   ; segment limit 0-15bit
    dw 0        ; base 0-15bit
    db 0        ; Base 16-23
    db 0x9a     ; Acces bytes
    db 11001111b; high 4b flags and low 4 bit flags
    db 0

gdt_data:       ;Ds, SS, ES, FS, GS
    dw 0xffff   ; segment limit 0-15bit
    dw 0        ; base 0-15bit
    db 0        ; Base 16-23
    db 0x92     ; Acces bytes
    db 11001111b; high 4b flags and low 4 bit flags
    db 0
    
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
load32:
    jmp $

message: db 'Hello World!', 0
times 510 - ($ - $$) db 0
dw 0xAA55

buffer: