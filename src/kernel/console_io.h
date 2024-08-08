#ifndef KERNEL_CONSOLE_IO_H
#define KERNEL_CONSOLE_IO_H

#include <stdint.h>
#include <stddef.h>
#include "lib/call_status_value.h"
#include "lib/console_io.h"


CallStatusValue kernel_console_reset(void);
CallStatusValue kernel_console_update_scb(void);
CallStatusValue kernel_console_status(void);

CallStatusValue kernel_console_input(char* byte);
CallStatusValue kernel_console_output(char byte);
CallStatusValue kernel_console_print_string(const char* str);

CallStatusValue kernel_console_immediately_read_string(size_t buffer_size, char buffer[static buffer_size], uint64_t timeout_ms, size_t* input_count);

CallStatusValue kernel_console_flush_input(void);
CallStatusValue kernel_console_flush_output(void);

CallStatusValue kernel_console_get_mode(ConsoleMode* mode);
CallStatusValue kernel_console_set_mode(ConsoleMode mode);

CallStatusValue kernel_console_get_output_delimiter(char* byte);
CallStatusValue kernel_console_set_output_delimiter(char byte);


#endif //KERNEL_CONSOLE_IO_H
