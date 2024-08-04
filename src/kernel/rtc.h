#ifndef KERNEL_RTC_H
#define KERNEL_RTC_H

#include <stdint.h>


void kernel_rtc_init(void);

uint64_t kernel_rtc_get_time(void);

void kernel_rtc_set_alarm(uint64_t time);
uint64_t kernel_rtc_get_alarm(void);
void kernel_rtc_reset_alarm(void);
bool kernel_rtc_is_alarm_running(void);

void kernel_rtc_clear_pending_interrupt(void);


void kernel_rtc_alarmed(void);


#endif //KERNEL_RTC_H
