#include "utils.h"

size_t str_len(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0"
                : "=a"(ret)
                : "Nd"(port));
    return ret;
}