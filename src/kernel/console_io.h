#ifndef KERNEL_CONSOLE_IO_H
#define KERNEL_CONSOLE_IO_H

#include <stdint.h>
#include "lib/call_status_value.h"


[[gnu::nonnull]]
CallStatusValue kernel_console_input(uint8_t* byte);

CallStatusValue kernel_console_output(uint8_t byte);


#endif //KERNEL_CONSOLE_IO_H
