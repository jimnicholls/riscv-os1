#include <string.h>
#include "system_control_block.h"
#include "trap.h"
#include "typeahead.h"
#include "uart.h"


static constexpr auto TYPEAHEAD_BUFFER_LENGTH = sizeof(g_scb.typeahead_buffer) / sizeof(g_scb.typeahead_buffer[0]);

_Static_assert(
    __builtin_popcount(TYPEAHEAD_BUFFER_LENGTH) == 1,
    "The size of typeahead_buffer in SystemControlBlock must be a power of 2"
);


[[gnu::always_inline, gnu::const]]
static inline uint8_t add1modn(const uint8_t i) {
    return (i + 1) & (TYPEAHEAD_BUFFER_LENGTH - 1);
}


void kernel_typeahead_reset(void) {
    char b;
    while (kernel_uart_receive(&b) > 0) {}
    g_scb.typeahaed_buffer_tail = g_scb.typeahead_buffer_head = 0;
    memset(g_scb.typeahead_buffer, 0, TYPEAHEAD_BUFFER_LENGTH);
}


void kernel_typeahead_on_uart_interrupt(void) {
    char c;
    const CallStatusValue csv = kernel_uart_receive(&c);
    if (csv > 0) {
        if (!kernel_typeahead_putchar(c)) {
            kernel_uart_transmit('\x07');
        }
    }
}


bool kernel_typeahead_is_empty(void) {
    return g_scb.typeahead_buffer_head == g_scb.typeahaed_buffer_tail;
}


bool kernel_typeahead_is_full(void) {
    return add1modn(g_scb.typeahead_buffer_head) == g_scb.typeahaed_buffer_tail;
}


bool kernel_typeahead_has(char c) {
    if (kernel_typeahead_is_empty()) {
        return false;
    }
    for (auto i = g_scb.typeahaed_buffer_tail; i != g_scb.typeahead_buffer_head; i = add1modn(i)) {
        if (g_scb.typeahead_buffer[i] == c) {
            return true;
        }
    }
    return false;
}


bool kernel_typeahead_getchar(char* c) {
    while (kernel_typeahead_is_empty()) {
        kernel_trap_wait_for_interrupt();
        if (g_scb.timer_has_alarmed) {
            return false;
        }
    }
    return kernel_typeahead_immediate_getchar(c);
}


bool kernel_typeahead_immediate_getchar(char* c) {
    if (kernel_typeahead_is_empty()) {
        return false;
    }
    *c = g_scb.typeahead_buffer[g_scb.typeahaed_buffer_tail];
    g_scb.typeahaed_buffer_tail = add1modn(g_scb.typeahaed_buffer_tail);
    return true;
}


bool kernel_typeahead_putchar(const char c) {
    if (kernel_typeahead_is_full()) {
        return false;
    }
    g_scb.typeahead_buffer[g_scb.typeahead_buffer_head] = c;
    g_scb.typeahead_buffer_head = add1modn(g_scb.typeahead_buffer_head);
    return true;
}
