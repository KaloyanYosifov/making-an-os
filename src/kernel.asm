[BITS 32]
global _start
extern kernel_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10
PIC_INTERRUPT_START_POINT equ 0x20

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ; Enable A20 line
    in al, 0x92
    or al, 2
    out 0x92, al
    ;

    ; Remap master PIC
    mov al, 00010001b
    out PIC_INTERRUPT_START_POINT, al

    mov al, PIC_INTERRUPT_START_POINT
    out 0x21, al

    mov al, 00000001b
    out 0x21, al
    ; PIC remapped

    sti

    call kernel_start
    jmp $

times 512-($ - $$) db 0
