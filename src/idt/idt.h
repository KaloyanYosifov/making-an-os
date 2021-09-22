#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_desc {
    uint16_t offset_1; // offset bits 0-15
    uint16_t selector; // Selector that is in our General description table (GDT)
    uint8_t zero; // does nothing
    uint8_t type_attr; // Descriptor type and attributes
    uint16_t offset_2; // offset bits 16 - 31

} __attribute__((packed));

struct idtr_descr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init();

#endif
