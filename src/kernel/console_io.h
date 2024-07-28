#ifndef KERNEL_CONSOLE_IO_H
#define KERNEL_CONSOLE_IO_H

#include <stdint.h>
#include "lib/call_status_value.h"
#include "lib/console_io.h"


[[gnu::nonnull]]
CallStatusValue kernel_console_input(uint8_t* byte);

CallStatusValue kernel_console_output(uint8_t byte);


[[gnu::nonnull]]
CallStatusValue kernel_get_console_mode(ConsoleMode* mode);

CallStatusValue kernel_set_console_mode(ConsoleMode mode);


[[gnu::nonnull]]
CallStatusValue kernel_get_output_delimiter(char* byte);

CallStatusValue kernel_set_output_delimiter(char byte);


#endif //KERNEL_CONSOLE_IO_H
