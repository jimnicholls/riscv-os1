#include "call_status_value.h"
#include "console_io.h"
#include "kernel/syscall.h"

#pragma GCC optimize (2)


CallStatusValue console_input(char* byte) {
    char b;
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "ecall\n\t"
        "mv %[b], a0\n\t"
        "mv %[csv], a7"
        : [csv] "=r" (csv),
          [b] "=r" (b)
        : [FUNC_NUM] "n" (SYSCALL_CONSOLE_INPUT)
        : "a7"
     );
    if (csv >= CSV_OK) {
        *byte = b;
    }
    return csv;
}


CallStatusValue console_output(char byte) {
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "ecall\n\t"
        "mv %[csv], a7"
        : [csv] "=r" (csv)
        : [FUNC_NUM] "n" (SYSCALL_CONSOLE_OUTPUT)
        : "a7"
     );
    return csv;
}


CallStatusValue get_console_mode(ConsoleMode* mode) {
    ConsoleMode v;
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "li a0, -1\n\t"
        "ecall\n\t"
        "mv %[csv], a7\n\t"
        "mv %[v], a0\n\t"
        : [csv] "=r" (csv),
          [v] "=r" (v)
        : [FUNC_NUM] "n" (SYSCALL_GET_SET_CONSOLE_MODE)
        : "a0", "a7"
     );
    if (csv >= CSV_OK) {
        *mode = v;
    }
    return csv;
}


CallStatusValue set_console_mode(ConsoleMode mode) {
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "ecall\n\t"
        "mv %[csv], a7"
        : [csv] "=r" (csv)
        : [FUNC_NUM] "n" (SYSCALL_GET_SET_CONSOLE_MODE)
        : "a7"
     );
    return csv;
}


CallStatusValue get_output_delimiter(char* byte) {
    char v;
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "li a0, -1\n\t"
        "ecall\n\t"
        "mv %[csv], a7\n\t"
        "mv %[v], a0\n\t"
        : [csv] "=r" (csv),
          [v] "=r" (v)
        : [FUNC_NUM] "n" (SYSCALL_GET_SET_OUTPUT_DELIMITER)
        : "a0", "a7"
     );
    if (csv >= CSV_OK) {
        *byte = v;
    }
    return csv;
}


CallStatusValue set_output_delimiter(char byte) {
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "ecall\n\t"
        "mv %[csv], a7"
        : [csv] "=r" (csv)
        : [FUNC_NUM] "n" (SYSCALL_GET_SET_OUTPUT_DELIMITER)
        : "a7"
     );
    return csv;
}
