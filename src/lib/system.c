#include "system.h"

#include "kernel/syscall.h"

#pragma GCC optimize (2)


void system_reset() {
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "ecall\n\t"
        :
        : [FUNC_NUM] "n" (SYSCALL_SYSTEM_RESET)
    );
    __builtin_unreachable();
}
