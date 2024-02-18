[BITS 32]

global print:function
global getkey:function
global myos_malloc:function
global myos_free:function
global myos_putchar:function

;void print(const char* filename)
print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax, 1
    int 0x80
    add esp, 4
    pop ebp
    ret

;int getkey()
getkey
    push ebp
    mov ebp, esp
    mov eax, 2
    int 0x80
    pop ebp
    ret

; void* myos_malloc(size_t size)
myos_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

myos_free:
    push ebp
    mov ebp, esp
    mov eax, 5
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret

myos_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3
    push dword[ebp+8] ; Variable 'C'
    int 0x80
    add esp, 4
    pop ebp
    ret
    