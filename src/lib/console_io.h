#ifndef LIB_CONSOLE_IO_H
#define LIB_CONSOLE_IO_H

#include "call_status_value.h"

[[gnu::nonnull]]
CallStatusValue console_input(char* byte);

CallStatusValue console_output(char byte);

#endif //LIB_CONSOLE_IO_H
