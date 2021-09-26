#include "idt.h"
#include "../config.h"
#include "../display.h"
#include "../memory/memory.h"
#include "../io/io.h"

struct idt_desc idt_descriptors[OS_MAXIMUM_INTERRUPTS];
struct idtr_descr idtr_descriptors;

extern void int21h();
extern void no_interrupt();
extern void idt_load(struct idtr_descr* ptr);

void int21_handler() {
    println("Naughty boy!");
    outb(0x20, 0x20);
}

void no_interrupt_handler() {
    outb(0x20, 0x20);
}

void idt_zero() {
    println("Divide by zero error!");
}

void idt_set(int interrupt_number, void* address) {
    struct idt_desc* description = &idt_descriptors[interrupt_number];

    description->offset_1 = (uint32_t) address & 0x0000ffff;
    description->selector = OS_CODE_SEG;
    description->zero = 0x00;
    description->type_attr = 0xEE;
    description->offset_2 = (uint32_t) address >> 16;
}

void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));

    idtr_descriptors.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptors.base = (uint32_t) idt_descriptors;

    for (uint16_t i = 0; i < OS_MAXIMUM_INTERRUPTS; i++) {
        idt_set(i, no_interrupt);
    }

    idt_set(0, idt_zero);
    idt_set(0x21, int21h);

    idt_load(&idtr_descriptors);
}
