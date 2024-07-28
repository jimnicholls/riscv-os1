#include <stdint.h>
#include "syscall.h"
#include "lib/call_status_value.h"


void kernel_syscall(uint64_t a_regs[8]) {
    CallStatusValue csv = CSV_E_NOT_SUPPORTED;
    // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
    switch (a_regs[7]) {

    }
    a_regs[7] = csv;
}
