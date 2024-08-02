#include <stdint.h>
#include <stdio.h>
#include "lib/call_status_value.h"
#include "system_control_block.h"


void warm_boot(void);   // Provided by main.c


CallStatusValue kernel_console_reset() {
    // CSI!p: soft reset
    fputs("\x1b[!p", stdout);
    return CSV_OK;
}


CallStatusValue kernel_console_input(uint8_t* byte) {
    const int c = getchar();
    if (c == 0x7f) {
        // Echo the ⌫ key as ^H (BS)
        putchar('\x08');
    } else if (c < ' ') {
        switch (c) {
            case 0x09:    // ^I HT
            case 0x0a:    // ^J LF
            case 0x0d:    // ^M CR
                putchar(c);
                break;
            case 0x03:    // ^C
                if (!g_scb.console_mode.disable_ctrl_c_termination) {
                    puts("\x07^C");
                    warm_boot();
                }
            default:
                // Don't echo
                break;
        }
    } else {
        putchar(c);
    }
    *byte = c;
    return CSV_OK;
}


CallStatusValue kernel_console_output(const char byte) {
    putchar(byte);
    return CSV_OK;
}


CallStatusValue kernel_console_print_string(const char* str) {
    const char output_delimiter = g_scb.output_delimiter;
    if (output_delimiter == 0) {
        fputs(str, stdout);
    } else {
        uint8_t b;
        while ((b = *str++) != output_delimiter) {
            putchar(b);
        }
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
