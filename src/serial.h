#pragma once

#define PORT 0x3f8 // COM1

#include <stddef.h>

void ser_init();
int ser_received();
char ser_read();
int ser_readstr(char* str, size_t size);

int ser_transmit_empty();
void ser_putchar(char a);
void ser_write(const char* data, size_t size);
void ser_print(const char* data);

void ser_clear();