#include "kernel.h"
#include <stddef.h>
#include <stdint.h>

int current_terminal_x = 0;
int current_terminal_y = 0;
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

void clear_screen() {
    uint16_t* video_mem = (uint16_t*)(VIDEO_MEMORY_ADDRESS);

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            video_mem[(y * VGA_HEIGHT) + x] = terminal_char(' ', 0);
        }
    }
}

void terminal_new_line() {
    current_terminal_x = 0;
    current_terminal_y += 1;
}

void print(const char* statement) {
    uint16_t* video_mem = (uint16_t*)(VIDEO_MEMORY_ADDRESS);

    for (int i = 0; i < strlen(statement); i++) {
        if (statement[i] == '\n') {
            terminal_new_line();

            continue;
        }

        if (current_terminal_x >= VGA_WIDTH) {
            terminal_new_line();
        }

        video_mem[(current_terminal_y * VGA_WIDTH) + current_terminal_x] = terminal_char(statement[i], 15);
        current_terminal_x += 1;
    }
}

void println(const char* statement) {
    print(statement);
    print("\n");
}

void kernel_start() {
    clear_screen();

    println("Welcome to the hood!");

    println("Welcome to me!");
}
