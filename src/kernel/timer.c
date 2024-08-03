#include <stdint.h>
#include "timer.h"
#include "system_control_block.h"

#pragma GCC optimize (2)


static constexpr uint64_t timebase_frequency = 0x989680;                        // timer ticks / s
static constexpr uint32_t timebase_frequency_ms = timebase_frequency / 1000;    // timer ticks / ms

static auto const clint_base = (void*) 0x2000000;
static volatile auto const mtimecmp_base = (uint64_t*) (clint_base + 0x4000);
static volatile auto const mtime_register = (uint64_t*) (clint_base + 0xbff8);

[[gnu::always_inline, gnu::const]]
static inline uint64_t* mtimecmp_register(const unsigned hart_id) {
    return mtimecmp_base + (hart_id << 3);
}


[[gnu::always_inline]]
static inline void enable_machine_timer_interrupt(void) {
    asm ( "li a5, 0x80\n\t" "csrrs zero, mie, a5" ::: "a5" );
}


[[gnu::always_inline]]
static inline void disable_machine_timer_interrupt(void) {
    asm ( "li a5, 0x80\n\t" "csrrc zero, mie, a5" ::: "a5" );
}


void kernel_timer_init() {
    kernel_timer_reset();
}


#include <stdio.h>

// Called on interrupt #7 by trap_handler in trap.c.
void kernel_timer_alarmed(void) {
    disable_machine_timer_interrupt();
    *mtimecmp_register(0) = UINT64_MAX;    // Clear the pending interrupt bit
    g_scb.timer_has_alarmed = true;
}


void kernel_timer_reset(void) {
    disable_machine_timer_interrupt();
    *mtimecmp_register(0) = UINT64_MAX;
    g_scb.timer_has_alarmed = false;
}


void kernel_timer_set(const uint64_t ms_from_now) {
    constexpr unsigned hart_id = 0;
    g_scb.timer_has_alarmed = false;
    *mtimecmp_register(hart_id) = *mtime_register + ms_from_now * timebase_frequency_ms;
    enable_machine_timer_interrupt();
}


void kernel_timer_pause(const uint64_t ms_from_now) {
    kernel_timer_set(ms_from_now);
    volatile bool* timer_has_alarmed = &g_scb.timer_has_alarmed;
    do {
        asm volatile ( "wfi" );
    } while (!*timer_has_alarmed);
    kernel_timer_reset();
}
