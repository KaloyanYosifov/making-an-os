#include "kernel.h"
#include "display.h"
#include "idt/idt.h"

extern void problem();

void kernel_start() {
    idt_init();
    init_display();

    println("Hello there!");
}
