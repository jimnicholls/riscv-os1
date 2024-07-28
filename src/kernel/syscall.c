#include <stdint.h>
#include "kernel.h"
#include "syscall.h"
#include "console_io.h"
#include "lib/call_status_value.h"


void kernel_syscall(uint64_t a_regs[8]) {
    CallStatusValue csv = CSV_E_NOT_SUPPORTED;
    // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
    switch (a_regs[7]) {

    case SYSCALL_SYSTEM_RESET:
        warm_boot();    // Does not return

    case SYSCALL_CONSOLE_INPUT:
        csv = kernel_console_input((uint8_t*) a_regs);
        break;

    case SYSCALL_CONSOLE_OUTPUT:
        csv = kernel_console_output(a_regs[0]);
        break;

    }
    a_regs[7] = csv;
}
