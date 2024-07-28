#include "kernel.h"
#include "uart.h"
#include "ccp/ccp.h"


[[gnu::aligned(8)]]
extern const void* const g_ram_end;


[[noreturn, gnu::retain, gnu::section(".kmain"), gnu::visibility("hidden")]]
void kmain(void) {
    uart_init();
    ccp_main();
    warm_boot();
}


[[noreturn]]
void warm_boot(void) {
    asm volatile (
        "mv sp, %[g_ram_end]\r\n"       /* Unwind the call stack by resetting the stack point */
        "jr %[kmain]"                   /* Jump back to the start of kmain */
        :
        : [g_ram_end] "r" (g_ram_end),
          [kmain] "r" (kmain)
        : "t0"
    );
    __builtin_unreachable();
}
