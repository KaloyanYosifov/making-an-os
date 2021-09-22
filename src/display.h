#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 23

struct Display {
    int current_terminal_x;
    int current_terminal_y;
    uint16_t* video_mem;
};

void init_display();

void set_main_display(struct Display d);

void clear_screen();

void terminal_new_line();

void print(const char* statement);

void println(const char* statement);

#endif
