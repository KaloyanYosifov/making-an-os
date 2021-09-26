section .asm

global int21h
global idt_load
global no_interrupt

extern int21_handler
extern no_interrupt_handler

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]

    pop ebp
    ret

int21h:
    cli
    pushad
    call int21_handler
    popad
    sti
    iret

no_interrupt:
    cli
    pushad
    call no_interrupt_handler
    popad
    sti
    iret
