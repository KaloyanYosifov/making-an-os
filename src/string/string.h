#ifndef STRING_H
#define STRING_H

#include <stddef.h>

char* itoa(int value);
size_t strlen(const char* str);

void reverse(char* str);
void reverse_with_length(char* str, size_t length);

#endif
