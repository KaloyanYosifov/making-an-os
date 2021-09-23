#include "kernel.h"
#include "display.h"
#include "idt/idt.h"
#include "string/string.h"

extern void problem();
extern unsigned int help();

void kernel_start() {
    idt_init();
    init_display();

    unsigned int value = help();

    char* str = itoa(value);

    println(str);
}
