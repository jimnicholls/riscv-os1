#include <stdio.h>
#include <setjmp.h>
#include "console_io.h"
#include "plic.h"
#include "rtc.h"
#include "system_control_block.h"
#include "timer.h"
#include "uart.h"


void trap_handler_0();          // Provided by trap.S
[[noreturn]] void ccp_main();   // Provided by ccp/ccp.c


static jmp_buf g_do_warm_boot_jmp_buf;


[[noreturn]]
int main(void) {
    kernel_console_reset();
    puts("RISCV-OS/1 1.0-alpha.1");

    setjmp(g_do_warm_boot_jmp_buf);

    // Use trap_handler_0 for machine-mode interrupts and exceptions, including ecall
    asm volatile (
        "mv a4, %0\n\t"
        "csrw mtvec, a4\n\t"
        :
        : "r" (trap_handler_0)
        : "a4"
    );

    asm volatile ( "csrrsi zero, mstatus, 8" );     // Disable machine-mode interrupts while initialising the hardware

    kernel_timer_init();
    kernel_plic_init();
    kernel_rtc_init();
    kernel_uart_init();

    asm volatile ( "csrrsi zero, mstatus, 8" );     // Enable machine-mode interrupts

    kernel_scb_reset();
    kernel_console_output('\n');
    kernel_console_update_scb();

    ccp_main();
}


void kernel_main_warm_boot(void) {
    longjmp(g_do_warm_boot_jmp_buf, 1);
}
