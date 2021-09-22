#include "idt.h"
#include "../config.h"
#include "../display.h"
#include "../memory/memory.h"

struct idt_desc idt_descriptors[OS_MAXIMUM_INTERRUPTS];
struct idtr_descr idtr_descriptors;

extern void idt_load(struct idtr_descr* ptr);

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

    idt_set(0, idt_zero);

    idt_load(&idtr_descriptors);
}
