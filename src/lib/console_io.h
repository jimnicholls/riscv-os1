#ifndef LIB_CONSOLE_IO_H
#define LIB_CONSOLE_IO_H

#include <stdbool.h>
#include <stdint.h>
#include "call_status_value.h"


typedef struct {
    bool ctrl_c_only: 1;
    bool disable_start_stop_scroll: 1;
    bool enable_raw_output: 1;
    bool disable_ctrl_c_termination: 1;
} ConsoleMode;

_Static_assert(sizeof(ConsoleMode) == 1, "The number of fields in ConsoleMode must fit in 1 byte");


[[gnu::nonnull]]
CallStatusValue console_input(char* byte);

CallStatusValue console_output(char byte);

#endif //LIB_CONSOLE_IO_H
