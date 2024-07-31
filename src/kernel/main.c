#include "console_io.h"
#include "system_control_block.h"
#include "uart.h"


[[noreturn]] void warm_boot(void);


void trap_handler_0();          // Provided by trap.S
[[noreturn]] void ccp_main();   // Provided by ccp/ccp.c


static void* sp_save;


[[noreturn]]
int main(void) {
    asm volatile (
        "mv %0, sp\n\t"             // Save the stack pointer so we can reset it in warm_boot
        "mv t0, %1\n\t"             // Jump to trap_handler_0 for interrupts and exceptions, including ecall
        "csrw mtvec, t0\n\t"
        "csrsi mstatus, 3\n\t"      // Enable interrupts
        : "=r" (sp_save)
        : "r" (trap_handler_0)
        : "t0"
    );
    kernel_console_reset();
    kernel_console_print_string("RISCV-OS/1 1.0-alpha.1\n");
    warm_boot();
}


void warm_boot(void) {
    /* Reset the stack pointer to the top of memory */
    asm volatile ( "mv sp, %0" : : "r" (sp_save) );
    kernel_uart_init();
    kernel_reset_scb();
    kernel_console_output('\n');
    ccp_main();
}
