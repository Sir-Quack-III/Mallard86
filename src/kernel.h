#pragma once

#include <stdint.h>
#include <stddef.h>

void term_init();
void ksetcolor(uint8_t color);
void kmcputchar(char c, uint8_t color, size_t x, size_t y);
void kputchar(char c);
void kwrite(const char* data, size_t size);
void kprint(const char* data);
void kerror(const char* data);
