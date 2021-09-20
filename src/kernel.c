#include "kernel.h"
#include <stddef.h>
#include <stdint.h>

const int VIDEO_MEMORY_ADDRESS = 0xB8000;

size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        len++;
    }

    return len;
}

uint16_t terminal_char(char character, char colour) {
    return (colour << 8) | character;
}

void print(const char* statement) {
    uint16_t* video_mem = (uint16_t*)(VIDEO_MEMORY_ADDRESS);

    for (int i = 0; i < strlen(statement); i++) {
        video_mem[i] = terminal_char(statement[i], 3);
    }
}

void kernel_start() {
    print("Hello there!");
}
