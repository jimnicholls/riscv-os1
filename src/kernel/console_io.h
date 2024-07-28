#ifndef KERNEL_CONSOLE_IO_H
#define KERNEL_CONSOLE_IO_H

#include <stdint.h>
#include "lib/call_status_value.h"

CallStatusValue kernel_console_input(uint8_t* byte);

#endif //KERNEL_CONSOLE_IO_H
