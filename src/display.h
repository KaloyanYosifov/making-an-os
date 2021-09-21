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

struct Display create_display();

void clear_screen(struct Display *display);

void terminal_new_line(struct Display *display);

void print(struct Display *display, const char* statement);

void println(struct Display *display, const char* statement);

#endif
