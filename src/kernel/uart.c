#include <stdint.h>
#include "kernel/uart.h"


#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "Only little-endian targets are supported"
#endif

#pragma GCC diagnostic ignored "-Wunused-const-variable"


/* 16550 registers */

static       volatile uint8_t* const g_uart_base    = (uint8_t*) 0x10000000;
static const volatile uint8_t* const g_uart_rbr     = g_uart_base + 0;              // Receiver buffer (ro)
static       volatile uint8_t* const g_uart_thr     = g_uart_base + 0;              // Transmitter holding (wo)
static       volatile uint8_t* const g_uart_ier     = g_uart_base + 1;              // Interrupt enable
static const volatile uint8_t* const g_uart_iir     = g_uart_base + 2;              // Interrupt identity (ro)
static       volatile uint8_t* const g_uart_fcr     = g_uart_base + 2;              // FIFO control (wo)
static       volatile uint8_t* const g_uart_lcr     = g_uart_base + 3;              // Line control
static       volatile uint8_t* const g_uart_mcr     = g_uart_base + 4;              // Modem control
static       volatile uint8_t* const g_uart_lsr     = g_uart_base + 5;              // Line status
static       volatile uint8_t* const g_uart_msr     = g_uart_base + 6;              // Modem status
static       volatile uint8_t* const g_uart_scratch = g_uart_base + 7;              // Unusued

/* When DLAB (LCR[7]) is 1 */
static volatile uint16_t* const g_divisor_latch = (uint16_t*) g_uart_base + 0;      // Little endian


void kernel_uart_init(void) {
    *g_uart_ier = 0b00000000;                   // Disable UART interrupts
    *g_uart_fcr = 0b00000111;                   // Enabled and reset the TX and RX FIFOs
    *g_uart_lcr = 0b00000011;                   // 8 bits, 1 stop bit, no parity
    *g_uart_mcr = 0b00000001;                   // Set data terminal ready (DTR)
}


void kernel_uart_transmit(uint8_t b) {
    while ((*g_uart_msr & 0b00110000) != 0b00110000) {
        /* Wait for DSR and CTS */
    }
    *g_uart_thr = b;
}


int kernel_uart_receive(uint8_t* b) {
    if ((*g_uart_msr & 0b10100000) != 0b10100000) {
        /* Read error because no DSR and CDC */
        return -1;
    }
    if (!(*g_uart_lsr & 1)) {
        /* No DR */
        return 0;
    }
    *b = *g_uart_rbr;
    return 1;
}
