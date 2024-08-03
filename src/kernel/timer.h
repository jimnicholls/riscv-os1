#ifndef KERNEL_TIMER_H
#define KERNEL_TIMER_H

#include <stdint.h>


void kernel_timer_init(void);
void kernel_timer_alarmed(void);

void kernel_timer_reset(void);
void kernel_timer_set(uint64_t ms_from_now);
void kernel_timer_pause(uint64_t ms_from_now);


#endif //KERNEL_TIMER_H
