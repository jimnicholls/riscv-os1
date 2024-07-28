#include "kernel/kernel.h"
#include "lib/lib.h"

static void write_prompt(void);

void ccp_main(void) {
    write_prompt();
    for (;;) {
        char c;
        console_input(&c);
    }
}


void write_prompt(void) {
    uart_transmit('\n');
    uart_transmit('A');
    uart_transmit('>');
    uart_transmit(' ');
}
