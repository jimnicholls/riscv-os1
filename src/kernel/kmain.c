#include "kernel/kernel.h"
#include "ccp/ccp.h"

extern const void* const g_ram_end;

[[noreturn, gnu::retain, gnu::section(".kmain"), gnu::visibility("hidden")]]
void kmain(void) {
    ccp_main();
    warm_boot();
}

[[noreturn]]
void warm_boot(void) {
    __asm__ __volatile__ (
        "mv sp, %[g_ram_end]\r\n"       /* Unwind the call stack by resetting the stack point */
        "jr %[kmain]"                   /* Jump back to the start of kmain */
        :
        : [g_ram_end] "r" (&g_ram_end),
          [kmain] "r" (kmain)
        : "t0"
    );
    for (;;); /* Satisify the compiler that warm_boot never returns */
}
