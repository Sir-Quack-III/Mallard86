#pragma once

#include <stdint.h>
#include <stddef.h>

size_t str_len(const char *str);

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);