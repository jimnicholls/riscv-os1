#include <stdint.h>
#include "call_status_value.h"
#include "system_control_block.h"
#include "kernel/syscall.h"

#pragma GCC optimize (2)


[[gnu::nonnull]]
CallStatusValue get_scb_parameter(uint64_t parameter, uint64_t* value) {
    uint64_t v;
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "mv a0, zero\n\t"
        "mv a1, %[parameter]\n\t"
        "ecall\n\t"
        "mv %[csv], a7\n\t"
        "mv %[v], a0"
        : [csv] "=r" (csv),
          [v] "=r" (v)
        : [FUNC_NUM] "n" (SYSCALL_GET_SET_SYSTEM_CONTROL_BLOCK_PARAMETER),
          [parameter] "r" (parameter)
        : "a0", "a1", "a7"
     );
    if (csv >= CSV_OK) {
        *value = v;
    }
    return csv;
}


CallStatusValue set_scb_parameter(uint64_t parameter, uint64_t value) {
    CallStatusValue csv;
    asm (
        "li a7, %[FUNC_NUM]\n\t"
        "li a0, 1\n\t"
        "mv a1, %[parameter]\n\t"
        "mv a2, %[value]\n\t"
        "ecall\n\t"
        "mv %[csv], a7"
        : [csv] "=r" (csv)
        : [FUNC_NUM] "n" (SYSCALL_GET_SET_SYSTEM_CONTROL_BLOCK_PARAMETER),
          [parameter] "r" (parameter),
          [value] "r" (value)
        : "a0", "a1", "a2", "a7"
     );
    return csv;
}
