#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel.h"
#include "utils.h"
#include "serial.h"
#include "terminal.h"
#include "gdt.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
    #error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
    #error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

// size_t str_len(const char* str) {
//     size_t len = 0;
//     while (str[len])
//         len++;
//     return len;
// }

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void term_init(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void ksetcolor(uint8_t color) {
    terminal_color = color;
}

void kmcputchar(char c, uint8_t color, size_t x, size_t y) { // move, color, put    
    if (c == '\n') {
        terminal_row++;
        terminal_column = -1;
        return;
    }
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void kputchar(char c) {
    kmcputchar(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void kwrite(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        kputchar(data[i]);
}

void kprint(const char* data) {
    kwrite(data, str_len(data));
}

void kerror(const char* data) {
    ksetcolor(VGA_COLOR_LIGHT_GREY);
    kprint("ERR: ");
    ksetcolor(VGA_COLOR_LIGHT_RED);
    kprint(data);
    ksetcolor(VGA_COLOR_LIGHT_GREY);
}

void kernel_main(void) {
    // bool serial = true;

    term_init();
    kprint("Kernel loaded\n");
    kprint("Terminal initialized\n");

    gdt_install();
    reload_segments();
    kprint("GDT initialized\n");
    
    ser_init();
    kprint("Serial initialized\n");
    kprint("Printing to Serial...\n");

    // terminal_row = 0;
    // terminal_column = 0;

    // // Terminal
    // char* m86logo = 
    //             "   __     __)                        ___     __ \n"
    //             "  (, /|  /|       /) /)          /) (   )  /    \n"
    //             "    / | / |  _   // // _   __  _(/  .--'  /__   \n"
    //             " ) /  |/  |_(_(_(/_(/_(_(_/ (_(_(_ (___) (__ )  \n"
    //             "(_/   '     ";

    // ksetcolor(VGA_COLOR_LIGHT_CYAN);
    // kprint(m86logo);
    // ksetcolor(VGA_COLOR_WHITE);
    // kprint("The operating system of no use!\n\n");
    // ksetcolor(VGA_COLOR_LIGHT_GREY);
    // kprint("Serial mode is enabled. I, the screen, will not display anything.\nCheck the serial port!\n\n)");

    terminal();

    // if (serial)
}
