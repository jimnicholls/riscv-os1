#include <stdint.h>
#include <stdio.h>
#include "ecall.h"


typedef struct {
    uint64_t a_regs[8];
    uint64_t s_regs[12];
    uint64_t t_regs[7];
    uint16_t sp;
    uint64_t ra;
    uint64_t gp;
    uint64_t tp;
} TrapContext;


[[noreturn]] static void unhandled(uint64_t cause, uint64_t tval, void* pc, const TrapContext* context, bool is_interrupt);
[[noreturn]] static void reboot(void);
static void print_context(const TrapContext* context);


void* trap_handler(uint64_t cause, uint64_t tval, void* const pc, TrapContext* context) {
    /* Context has already been saved, and will be restored when trap_handler exists. See trap_handler_0 in traps.S */
    bool is_interrupt;
    asm (
        "bexti %[is_interrupt], %[cause], 63\n\t"
        "bclri %[cause], %[cause], 63"
        : [is_interrupt] "=r" (is_interrupt),
          [cause] "+r" (cause)
    );
    if (is_interrupt) {
        /* For interrupts, pc is the instruction that the CPU will execute after returning from the trap handler. */
        unhandled(cause, tval, pc, context, is_interrupt);
    } else {
        /* For exceptions, pc is the instruction that caused the instruction. */
        if (cause == 11) {
            kernel_ecall(context->a_regs);
            return pc + 4;  // Resume _after_ the ecall instruction, which is 4 bytes
        } else {
            unhandled(cause, tval, pc, context, is_interrupt);
        }
    }
}


void unhandled(const uint64_t cause, const uint64_t tval, void* const pc, const TrapContext* const context, const bool is_interrupt) {
    printf(
        "\x1b[1m\x1b[31m\x1b[40m\n"
        "┌───────────────────────────────────────────────────────────────────┐\n"
        "│ Software failure      Unexpected %-9s      \x1b[7mType ^C to reboot\x1b[27m │\n"
        "│ Guru mediation %016lx:%016lx@%016p │\n"
        "└───────────────────────────────────────────────────────────────────┘\n",
        is_interrupt ? "interrupt" : "exception",
        cause, tval, pc
    );
    for (;;) {
        int c = getchar();
        switch (c) {
            case 0x03:  // ^C
                reboot();
            case 'r':
                print_context(context);
                break;
            default:
                putchar('\a');
        }
    }
}


void reboot(void) {
    // Remove QEMU via the SiFive test device
    uint32_t* const sifive_test_device = (uint32_t*) 0x100000;
    *sifive_test_device = 0x7777;
    __builtin_unreachable();
}


static const char* const register_labels[] = {
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6",
    "sp", "tp", "gp", "ra",
};
static constexpr unsigned register_count = sizeof(register_labels) / sizeof(register_labels[0]);
_Static_assert(
    register_count == sizeof(TrapContext) / sizeof(uint64_t),
    "the number of strings in register_labels must match the number of registers in TrapContext"
);

void print_context(const TrapContext* context) {
    const uint64_t* const base_int_regs = (uint64_t* const)context;
    for (unsigned i = 0; i < register_count; ++i) {
        printf("%-3s %016lx%c", register_labels[i], base_int_regs[i], i % 4 == 3 ? '\n': '\t');
    }
    putchar('\n');
}
