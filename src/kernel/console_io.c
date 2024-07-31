#include <stdint.h>
#include "lib/call_status_value.h"
#include "console_io.h"
#include "system_control_block.h"
#include "uart.h"


void warm_boot(void);   // Provided by main.c


CallStatusValue kernel_console_reset() {
    // CSI!p: soft reset
    kernel_console_print_string("\x1b[!p");
    return CSV_OK;
}


CallStatusValue kernel_console_input(uint8_t* byte) {
    uint8_t b;
    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    while (kernel_uart_receive(&b) <= 0);
    if (b == '\x7f') {
        // Echo the ⌫ key as ^H (BS)
        kernel_console_output('\x08');
    } else if (b < ' ') {
        switch (b) {
            case '\x09':    // ^I HT
            case '\x0a':    // ^J LF
            case '\x0d':    // ^M CR
                kernel_console_output(b);
                break;
            case '\x03':    // ^C
                if (!g_scb.console_mode.disable_ctrl_c_termination) {
                    kernel_console_print_string("\x07^C\n");
                    warm_boot();
                }
            default:
                // Don't echo
                break;
        }
    } else {
        kernel_console_output(b);
    }
    *byte = b;
    return CSV_OK;
}


CallStatusValue kernel_console_output(const uint8_t byte) {
    kernel_uart_transmit(byte);
    return CSV_OK;
}


CallStatusValue kernel_console_print_string(const char* str) {
    uint8_t b;
    while ((b = *str++)) {
        kernel_console_output(b);
    }
    return CSV_OK;
}


CallStatusValue kernel_console_print_string1(const char* str, const char output_delimiter) {
    uint8_t b;
    while ((b = *str++) != output_delimiter) {
        kernel_console_output(b);
    }
    return CSV_OK;
}


CallStatusValue kernel_get_console_mode(ConsoleMode* mode) {
    *mode = g_scb.console_mode;
    return CSV_OK;
}


CallStatusValue kernel_set_console_mode(const ConsoleMode mode) {
    g_scb.console_mode = mode;
    return CSV_OK;
}


CallStatusValue kernel_get_output_delimiter(char* byte) {
    *byte = g_scb.output_delimiter;
    return CSV_OK;
}


CallStatusValue kernel_set_output_delimiter(const char byte) {
    g_scb.output_delimiter = byte;
    return CSV_OK;
}
