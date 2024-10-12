#include "sbi.h"

void console_init() {
    return;
}

void console_putc(char c) {
    sbi_console_putchar(c);
}