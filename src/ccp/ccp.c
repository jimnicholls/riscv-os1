#include "kernel/kernel.h"

static void write_prompt(void);

void ccp_main(void) {
    write_prompt();
}


void write_prompt(void) {
    uart_transmit('\n');
    uart_transmit('A');
    uart_transmit('>');
    uart_transmit(' ');
}
