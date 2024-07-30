#include <stdint.h>
#include "system_control_block.h"
#include "kernel/ecall.h"

#pragma GCC optimize (2)


ecall_defn_va1r1(get_scb_parameter, ECALL_GET_SET_SYSTEM_CONTROL_BLOCK_PARAMETER, 0, uint64_t, parameter, uint64_t, scb_value);
ecall_defn_va2(set_scb_parameter, ECALL_GET_SET_SYSTEM_CONTROL_BLOCK_PARAMETER, 1, uint64_t, parameter, uint64_t, scb_value);
