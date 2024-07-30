#include "kernel.h"
#include "console_io.h"
#include "system_control_block.h"
#include "uart.h"
#include "ccp/ccp.h"


[[gnu::aligned(8)]]
extern const void* const g_ram_end;


[[noreturn, gnu::retain, gnu::section(".kmain"), gnu::visibility("hidden")]]
void kmain(void) {
    kernel_console_reset();
    kernel_console_print_string("RISCV-OS/1 1.0-alpha.1\n");
    warm_boot();
}


[[noreturn]]
void warm_boot(void) {
    /* Reset the stack pointer to the top of memory */
    asm volatile ( "mv sp, %[g_ram_end]" : : [g_ram_end] "r" (g_ram_end) );
    kernel_uart_init();
    kernel_reset_scb();
    kernel_console_output('\n');
    ccp_main();
}
