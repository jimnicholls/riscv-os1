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
