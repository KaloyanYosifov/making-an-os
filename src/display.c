#include "display.h"

const int VIDEO_MEMORY_ADDRESS = 0xB8000;

size_t strlen(const char* statement) {
    size_t length = 0;

    while(statement[length]) {
        length++;
    }

    return length;
}

struct Display create_display() {
    struct Display display = {0, 0, (uint16_t*)VIDEO_MEMORY_ADDRESS};

    return (display);
}

uint16_t terminal_char(char character, char colour) {
    return (colour << 8) | character;
}

void clear_screen(struct Display *display) {

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            display->video_mem[(y * VGA_HEIGHT) + x] = terminal_char(' ', 0);
        }
    }
}

void terminal_new_line(struct Display *display) {
    display->current_terminal_x = 0;
    display->current_terminal_y += 1;
}

void print(struct Display *display, const char* statement) {
    for (int i = 0; i < strlen(statement); i++) {
        if (statement[i] == '\n') {
            terminal_new_line(display);

            continue;
        }

        if (display->current_terminal_x >= VGA_WIDTH) {
            terminal_new_line(display);
        }

        display->video_mem[(display->current_terminal_y * VGA_WIDTH) + display->current_terminal_x] = terminal_char(statement[i], 15);
        display->current_terminal_x += 1;
    }
}

void println(struct Display *display, const char* statement) {
    print(display, statement);
    print(display, "\n");
}
