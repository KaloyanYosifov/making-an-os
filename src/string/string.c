#include "string.h"

size_t strlen(const char* str) {
    size_t length = 0;

    while(str[length]) {
        length++;
    }

    return length;
}

void reverse_with_length(char* str, size_t length) {
    int start = 0;
    int end = length - 1;

    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

/* A utility function to reverse a string  */
void reverse(char* str)
{
    reverse_with_length(str, strlen(str));
}

// Implementation of itoa()
char* itoa(int num)
{
    if (num == 0)
    {
        return "0\0";
    }

    unsigned short int isNegative = 0;

    // if we have a negative number reverse it
    if (num < 0)
    {
        isNegative = 1;
        num = -num;
    }

    char* str = "12";
    int i = 0;

    // Process individual digits
    while (num != 0)
    {
        int rem = num % 10;

        str[i++] = rem + '0';

        num = num / 10;
    }

    // if we had negative add the minus sign
    if (isNegative == 1) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse_with_length(str, i);

    return str;
}
