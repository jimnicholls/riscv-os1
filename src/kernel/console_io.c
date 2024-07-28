#include <stdint.h>
#include "lib/call_status_value.h"
#include "console_io.h"
#include "uart.h"


CallStatusValue kernel_console_input(uint8_t* byte) {
    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    while (uart_receive(byte) <= 0);
    kernel_console_output(*byte);
    return CSV_OK;
}


CallStatusValue kernel_console_output(uint8_t byte) {
    uart_transmit(byte);
    return CSV_OK;
}
