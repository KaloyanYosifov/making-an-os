#include "kernel.h"
#include "display.h"

void kernel_start() {
    struct Display display = create_display();

    clear_screen(&display);

    println(&display, "Welcome to the hood!");

    println(&display, "Welcome to me!");
}
