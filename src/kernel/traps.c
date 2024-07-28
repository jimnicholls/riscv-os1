#include <stdint.h>


[[gnu::nonnull, gnu::returns_nonnull]]
void* trap_handler(uint64_t cause, uint64_t tval, void* const pc, uint64_t a_regs[8]) {
    /* Context has already been saved, and will be restored when trap_handler exists. See trap_handler_0 in traps.S */
    for (;;);
}
