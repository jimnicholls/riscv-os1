#include <stdint.h>
#include "lib/call_status_value.h"
#include "console_io.h"
#include "system_control_block.h"
#include "uart.h"


CallStatusValue kernel_console_input(uint8_t* byte) {
    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    while (kernel_uart_receive(byte) <= 0);
    kernel_console_output(*byte);
    return CSV_OK;
}


CallStatusValue kernel_console_output(const uint8_t byte) {
    kernel_uart_transmit(byte);
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
