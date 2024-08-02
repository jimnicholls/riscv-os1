#include <stdio.h>
#include "uart.h"
#undef stdin
#undef stdout
#undef stderr


static int kernel_stdio_putc(char, FILE*);
static int kernel_stdio_getc(FILE*);


static FILE console_file = FDEV_SETUP_STREAM(kernel_stdio_putc, kernel_stdio_getc, NULL, _FDEV_SETUP_RW);
FILE* const stdin = &console_file;
[[gnu::alias("stdin")]] extern typeof(stdin) stdout;
[[gnu::alias("stdin")]] extern typeof(stdin) stderr;


int kernel_stdio_putc(const char c, FILE*) {
    kernel_uart_transmit(c);
    return c;
}


int kernel_stdio_getc(FILE *) {
    char b;
    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    while (kernel_uart_receive(&b) <= 0);
    return b;
}
