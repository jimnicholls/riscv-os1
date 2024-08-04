#include <stdint.h>
#include "plic.h"
#include "rtc.h"
#include "system_control_block.h"


static constexpr auto rtc_irq = 11;

static auto const rtc_base  = (volatile uint32_t*) 0x101000;
static auto const time_low_register  = rtc_base + 0;
static auto const time_high_register  = rtc_base + 1;
static auto const alarm_low_register  = rtc_base + 2;
static auto const alarm_high_register  = rtc_base + 3;
static auto const irq_enable_register  = rtc_base + 4;
static auto const clear_alarm_register  = rtc_base + 5;
static auto const alarm_status_register  = rtc_base + 6;
static auto const clear_interrupt_register  = rtc_base + 7;


void kernel_rtc_init(void) {
    kernel_rtc_reset_alarm();
    kernel_rtc_clear_pending_interrupt();
    kernel_plic_set_priority(rtc_irq, 7);
    kernel_plic_enable_interrupt(rtc_irq);
}


uint64_t inline kernel_rtc_get_time(void) {
    return (uint64_t) *time_high_register << 32 | *time_low_register;
}


void kernel_rtc_set_alarm(const uint64_t time) {
    g_scb.utc_has_alarmed = false;
    *irq_enable_register = 1;
    // Must write high before low
    *alarm_high_register = time >> 32;
    *alarm_low_register = time;
}


uint64_t inline kernel_rtc_get_alarm(void) {
    return (uint64_t) *alarm_high_register << 32 | *alarm_low_register;
}


void kernel_rtc_reset_alarm(void) {
    *irq_enable_register = 0;
    *clear_alarm_register = 0;
    g_scb.utc_has_alarmed = false;
}


bool inline kernel_rtc_is_alarm_running(void) {
    return *alarm_status_register;
}


void inline kernel_rtc_clear_pending_interrupt(void) {
    *clear_interrupt_register = 0;
}


void kernel_rtc_alarmed(void) {
    kernel_rtc_clear_pending_interrupt();
    g_scb.utc_has_alarmed = true;
}
