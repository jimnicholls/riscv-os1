#include <stdbool.h>
#include <stdint.h>
#include "ecall.h"
#include "uart.h"


void* trap_handler(uint64_t cause, uint64_t tval, void* const pc, uint64_t a_regs[8]) {
    /* Context has already been saved, and will be restored when trap_handler exists. See trap_handler_0 in traps.S */
    bool is_interrupt;
    asm (
        "bexti %[is_interrupt], %[cause], 63\n\t"
        "bclri %[cause], %[cause], 63"
        : [is_interrupt] "=r" (is_interrupt),
          [cause] "+r" (cause)
    );
    if (is_interrupt) {
        /* For interrupts, pc is the instruction that the CPU will execute after returning from the trap handler. */
        kernel_uart_transmit('\n');
        kernel_uart_transmit('!');
        kernel_uart_transmit('I');
        kernel_uart_transmit('A' + cause);
        for (;;);
    } else {
        /* For exceptions, pc is the instruction that caused the instruction. */
        if (cause == 11) {
            kernel_ecall(a_regs);
            return pc + 4;  // Resume _after_ the ecall instruction, which is 4 bytes
        } else {
            kernel_uart_transmit('\n');
            kernel_uart_transmit('!');
            kernel_uart_transmit('E');
            kernel_uart_transmit('A' + cause);
            for (;;);
        }
    }
}
