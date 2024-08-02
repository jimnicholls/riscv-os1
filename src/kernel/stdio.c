#include <stdatomic.h>
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


/*
 * FILE in tinystdio has an unget field.
 * It is c + 1 (<== NOTE!!) if ungetc has been called on the stream.
 * On the next read, the unget field becomes zero and the old value is returned as the character that was "read".
 */

/*
 * CLion will complain a LOT about this code!
 * That's because CLion is using the host's C library and compiler headers
 * and not the ones from picolibc and the cross compiler.
 */

static inline _Atomic __ungetc_t* ungetp(FILE* stream) { return (_Atomic __ungetc_t*) &stream->unget; }

int kernel_stdio_regetch(FILE* stream) {
    const __ungetc_t unget = atomic_exchange_explicit(ungetp(stream), 0, memory_order_relaxed);
    return unget - 1;
}

bool kernel_stdio_has_ungetch(FILE* stream) {
    return atomic_load(ungetp(stream)) == 0;
}
