#include "utils.h"
#include "serial.h"

void ser_init(void) {
    outb(PORT + 1, 0x00);    // Disable all interrupts
    outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00);    //                  (hi byte)
    outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(PORT + 0, 0xAE);    // Test serial port (send byte 0xAE and check if serial returns same byte)

    if (inb(PORT + 0) != 0xAE) {
        return;
    }

    outb(PORT + 0, 0x00);    // If serial is not faulty (i.e: it returns same byte we sent), initialize
    return;
}

int ser_received() {
   return inb(PORT + 5) & 1;
}
 
char ser_read() {
   while (ser_received() == 0);
 
   return inb(PORT);
}

int ser_readstr(char* str, size_t size) {
    char cchar;
    for (size_t i = 0; i < size; i++) {
        cchar = ser_read();
        if (cchar == 13) {
            str[i] = '\0';
            return 0;
        }
        str[i] = cchar;
        ser_putchar(cchar);
    }

    return 1;
}

int ser_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}
 
void ser_putchar(char a) {
   while (ser_transmit_empty() == 0);
   outb(PORT, a);
}

void ser_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        ser_putchar(data[i]);
}

void ser_print(const char* data) {
    ser_write(data, str_len(data));
}

void ser_clear() {
    ser_print("\033[H");
}
