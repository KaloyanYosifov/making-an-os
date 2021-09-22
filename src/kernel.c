#include "kernel.h"
#include "display.h"

void kernel_start() {
    init_display();

    println("Welcome to the hood!");

    println("Welcome to me!");
}
