#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lib/call_status_value.h"
#include "console_io.h"
#include "main.h"
#include "stdio.h"
#include "system_control_block.h"
#include "timer.h"
#include "typeahead.h"


CallStatusValue kernel_console_reset() {
    // CSI!p: soft reset
    fputs("\x1b[!p", stdout);
    return CSV_OK;
}


CallStatusValue kernel_console_update_scb(void) {
    char buffer[50] = { 0 };
    constexpr size_t buffer_size = sizeof(buffer) / sizeof(buffer[0]);
    size_t input_count = 0;
    int console_page_length = -1, console_width = -1;
    // Assume the last character sent to the terminal was '\n'
    g_scb.console_column = 0;
    // Cancel any unterminated escape sequence
    putchar('\x18');
    // Query the terminal width and height in characters
    puts("\x1b[18t");
    // Wait for the terminal to respond. However if it doesn't support the query it will never respond.
    // The terminal "types" CSI8;h;wt where h is the height in decimal and w is the width in decimal
    kernel_console_immediately_read_string(buffer_size, buffer, 100, &input_count);
    buffer[input_count] = 0;
    // If the terminal responded with what looks to be valid response, try to parse it.
    if (input_count > 0 && buffer[input_count - 1] == 't' && strncmp(buffer, "\x1b[8;", 4) == 0) {
        sscanf(buffer + 4, "%d;%d", &console_page_length, &console_width);
    }
    // If we have not determined the width and height, assume a classic 80x24.
    g_scb.console_width = console_width < 0 ? 80: console_width;
    g_scb.console_page_length = console_page_length < 0 ? 24 : console_page_length;

    return CSV_OK;
}


CallStatusValue kernel_console_status() {
    bool has_input;
    if (g_scb.console_mode.ctrl_c_only) {
        has_input = kernel_stdio_peek_ungetch(stdin) == '\03' || kernel_typeahead_has('\03');
    } else {
        has_input = kernel_stdio_has_ungetch(stdin) || !kernel_typeahead_is_empty();
    }
    return has_input ? 1 : 0;
}


CallStatusValue kernel_console_input(char* byte) {
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
                    kernel_main_warm_boot();  // Does not return
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


CallStatusValue kernel_console_immediately_read_string(const size_t buffer_size, char buffer[buffer_size], const uint64_t timeout_ms, size_t* input_count) {
    if (buffer_size == 0) {
        *input_count = 0;
        return CSV_OK;
    }
    const char* const buffer_end = buffer + buffer_size;
    char* buffer_ptr = buffer;
    const int unget = kernel_stdio_regetch(stdin);
    if (unget >= 0) {
        *buffer_ptr++ = unget;
    }
    // ReSharper disable once CppLocalVariableMayBeConst
    volatile bool* const timer_has_alarmed = &g_scb.timer_has_alarmed;
    kernel_timer_set(timeout_ms == 0 ? 1 : timeout_ms);
    while (buffer < buffer_end && !*timer_has_alarmed) {
        const int r = getchar();
        if (r < 0) {
            break;
        }
        *buffer_ptr++ = r;
    }
    kernel_timer_reset();
    *input_count = buffer_ptr - buffer;
    return CSV_OK;
}


CallStatusValue kernel_console_flush_input(void) {
    ungetc(0, stdin);
    kernel_typeahead_reset();
    return CSV_OK;
}


CallStatusValue kernel_console_get_mode(ConsoleMode* mode) {
    *mode = g_scb.console_mode;
    return CSV_OK;
}


CallStatusValue kernel_console_set_mode(const ConsoleMode mode) {
    g_scb.console_mode = mode;
    return CSV_OK;
}


CallStatusValue kernel_console_get_output_delimiter(char* byte) {
    *byte = g_scb.output_delimiter;
    return CSV_OK;
}


CallStatusValue kernel_console_set_output_delimiter(const char byte) {
    g_scb.output_delimiter = byte;
    return CSV_OK;
}
