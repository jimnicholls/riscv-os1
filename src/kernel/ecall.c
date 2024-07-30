#include <stdint.h>
#include "kernel.h"
#include "ecall.h"
#include "console_io.h"
#include "system_control_block.h"
#include "lib/call_status_value.h"


void kernel_ecall(uint64_t a_regs[8]) {
    CallStatusValue csv = CSV_E_NOT_SUPPORTED;
    // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
    switch (a_regs[7]) {

        case ECALL_SYSTEM_RESET:
            warm_boot();    // Does not return

        case ECALL_CONSOLE_INPUT:
            csv = kernel_console_input((uint8_t*) a_regs);
            break;

        case ECALL_CONSOLE_OUTPUT:
            csv = kernel_console_output(a_regs[0]);
            break;

        case ECALL_GET_SET_SYSTEM_CONTROL_BLOCK_PARAMETER:
            switch (a_regs[0]) {
                case 0:
                    csv = kernel_get_scb_parameter(a_regs[1], a_regs);
                    break;
                case 1:
                    csv = kernel_set_scb_parameter(a_regs[1], a_regs[2]);
                    break;
                default:
                    csv = CSV_E_INVALID_ARG_0;
            }
            break;

        case ECALL_GET_SET_CONSOLE_MODE: {
            if (*(int64_t*) (void*) a_regs == -1) {
                // ReSharper disable once CppRedundantCastExpression
                csv = kernel_get_console_mode((void*) a_regs);
            } else if (a_regs[0] < 256) {
                csv = kernel_set_console_mode(*(ConsoleMode*) (void*) a_regs);
            } else {
                csv = CSV_E_INVALID_ARG_0;
            }
            break;
        }

        case ECALL_GET_SET_OUTPUT_DELIMITER: {
            if (*(int64_t*) (void*) a_regs == -1) {
                csv = kernel_get_output_delimiter((char*) a_regs);
            } else if (a_regs[0] < 128) {
                csv = kernel_set_output_delimiter(a_regs[0]);
            } else {
                csv = CSV_E_INVALID_ARG_0;
            }
        }

    }
    a_regs[7] = csv;
}
