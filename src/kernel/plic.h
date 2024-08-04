#ifndef KERNEL_PLIC_H
#define KERNEL_PLIC_H

#include <stdint.h>


void kernel_plic_init(void);


uint16_t kernel_plic_get_priority(uint32_t source_id);
void kernel_plic_set_priority(uint32_t source_id, uint16_t priority);

bool kenrel_plic_is_pending(uint32_t source_id);

void kernel_plic_enable_interrupt(uint32_t source_id);
void kernel_plic_disable_interrupt(uint32_t source_id);
bool kenrel_plic_is_enabled(uint32_t source_id);

uint32_t kernel_plic_get_threshold(void);
void kernel_plic_set_threshold(uint32_t threshold);

uint32_t kernel_plic_claim_interrupt(void);
void kernel_plic_complete_interrupt(uint32_t source_id);


#endif //KERNEL_PLIC_H
