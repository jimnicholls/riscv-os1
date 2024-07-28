#ifndef KERNEL_SYSCALL_H
#define KERNEL_SYSCALL_H

#include <stdint.h>

typedef enum : uint64_t {
    SYSCALL_SYSTEM_RESET = 0x00,
} SysCallNumber;

[[gnu::nonnull]]
void kernel_syscall(uint64_t a_regs[8]);

#endif //KERNEL_SYSCALL_H
