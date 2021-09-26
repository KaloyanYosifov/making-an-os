section .asm

global outb
global outw
global insb
global insw

outb:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp + 8]
    mov eax, [ebp + 12]
    out dx, al

    pop ebp
    ret

outw:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp + 8]
    mov eax, [ebp + 12]
    out dx, ax

    pop ebp
    ret

insb:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp + 8]
    in al, dx

    pop ebp
    ret

insw:
    push ebp
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp + 8]
    in ax, dx

    pop ebp
    ret
