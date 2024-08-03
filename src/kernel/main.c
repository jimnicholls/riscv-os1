#include <stdio.h>
#include <setjmp.h>
#include "console_io.h"
#include "system_control_block.h"
#include "uart.h"


void trap_handler_0();          // Provided by trap.S
[[noreturn]] void ccp_main();   // Provided by ccp/ccp.c


static jmp_buf g_do_warm_boot_jmp_buf;


[[noreturn]]
int main(void) {
    kernel_console_reset();
    puts("RISCV-OS/1 1.0-alpha.1");

    setjmp(g_do_warm_boot_jmp_buf);

    asm volatile (
        "mv a4, %0\n\t"                 // Jump to trap_handler_0 for interrupts and exceptions, including ecall
        "csrw mtvec, a4\n\t"
        "csrrsi zero, mstatus, 8\n\t"   // Enable interrupts
        :
        : "r" (trap_handler_0)
        : "a4"
    );
    kernel_uart_init();
    kernel_reset_scb();
    kernel_console_output('\n');
    ccp_main();
}


void warm_boot(void) {
    longjmp(g_do_warm_boot_jmp_buf, 1);
}
