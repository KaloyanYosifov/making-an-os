#include "display.h"

struct Display display;
const int VIDEO_MEMORY_ADDRESS = 0xB8000;

void init_display() {
    struct Display display;
    display.current_terminal_x = 0;
    display.current_terminal_y = 0;
    display.video_mem = (uint16_t*) VIDEO_MEMORY_ADDRESS;

    set_main_display(display);
}

void set_main_display(struct Display d) {
    display = d;

    clear_screen();
}

size_t strlen(const char* statement) {
    size_t length = 0;

    while(statement[length]) {
        length++;
    }

    return length;
}

uint16_t terminal_char(char character, char colour) {
    return (colour << 8) | character;
}

void clear_screen() {

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            display.video_mem[(y * VGA_HEIGHT) + x] = terminal_char(' ', 0);
        }
    }
}

void terminal_new_line() {
    display.current_terminal_x = 0;
    display.current_terminal_y += 1;
}

void print(const char* statement) {
    for (int i = 0; i < strlen(statement); i++) {
        if (statement[i] == '\n') {
            terminal_new_line();

            continue;
        }

        if (display.current_terminal_x >= VGA_WIDTH) {
            terminal_new_line();
        }

        display.video_mem[(display.current_terminal_y * VGA_WIDTH) + display.current_terminal_x] = terminal_char(statement[i], 15);
        display.current_terminal_x += 1;
    }
}

void println(const char* statement) {
    print(statement);
    print("\n");
}
