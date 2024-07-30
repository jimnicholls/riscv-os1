#ifndef LIB_CONSOLE_IO_H
#define LIB_CONSOLE_IO_H

#include "_internal/ecall.h"


typedef struct {
    bool ctrl_c_only: 1;
    bool disable_start_stop_scroll: 1;
    bool enable_raw_output: 1;
    bool disable_ctrl_c_termination: 1;
} ConsoleMode;

_Static_assert(sizeof(ConsoleMode) == 1, "The number of fields in ConsoleMode must fit in 1 byte");


[[gnu::nonnull]] ecall_decl_r1(console_input, char, byte);
ecall_decl_a1(console_output, char, byte);

[[gnu::nonnull]] ecall_decl_r1(get_console_mode, ConsoleMode, mode);
ecall_decl_a1(set_console_mode, ConsoleMode, mode);

[[gnu::nonnull]] ecall_decl_r1(get_output_delimiter, char, byte);
ecall_decl_a1(set_output_delimiter, char, byte);

#endif //LIB_CONSOLE_IO_H
