#include "console_io.h"
#include "kernel/ecall.h"

#pragma GCC optimize (2)


ecall_defn_r1(console_input, ECALL_CONSOLE_INPUT, char, byte);
ecall_defn_a1(console_output, ECALL_CONSOLE_OUTPUT, char, byte);
ecall_defn_a1(print_string, ECALL_PRINT_STRING, const char*, str);
ecall_defn_a0(get_console_status, ECALL_GET_CONSOLE_STATUS);

ecall_defn_vr1(get_console_mode, ECALL_GET_SET_CONSOLE_MODE, -1, ConsoleMode, mode);
ecall_defn_a1(set_console_mode, ECALL_GET_SET_CONSOLE_MODE, ConsoleMode, mode);

ecall_defn_vr1(get_output_delimiter, ECALL_GET_SET_OUTPUT_DELIMITER, -1, char, byte);
ecall_defn_a1(set_output_delimiter, ECALL_GET_SET_OUTPUT_DELIMITER, char, byte);
