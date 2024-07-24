#include "kernel/kernel.h"

static void write_prompt(void);

void ccp_main(void) {
    write_prompt();
    for (;;) {
        uint8_t b;
        int r = uart_receive(&b);
        if (r > 0) {
            uart_transmit(b);
        }
    }
}


void write_prompt(void) {
    uart_transmit('\n');
    uart_transmit('A');
    uart_transmit('>');
    uart_transmit(' ');
}
