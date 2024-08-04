#include <stdint.h>
#include "plic.h"

#pragma GCC optimize(2)


static constexpr uint64_t plic_0 = 0xc000000;
static constexpr uint64_t plic_0_priority_base = plic_0;
static constexpr uint64_t plic_0_pending_base = plic_0 + 0x1000;
static constexpr uint64_t plic_0_enable_base = plic_0 + 0x2000;
static constexpr uint64_t plic_0_context_base = plic_0 + 0x200000;
static constexpr uint64_t context_threshold_offset = 0;
static constexpr uint64_t context_claim_offset = 4;
static constexpr uint64_t plic_0_num_sources = 96;


[[gnu::always_inline, gnu::const]]
static inline volatile uint32_t* priority_register(const uint32_t source_id) {
    return (volatile uint32_t*) (plic_0_priority_base + (source_id << 2));
}

uint16_t kernel_plic_get_priority(const uint32_t source_id) {
    return *priority_register(source_id);
}

void kernel_plic_set_priority(const uint32_t source_id, const uint16_t priority) {
    *priority_register(source_id) = priority;
}


[[gnu::always_inline, gnu::const]]
static inline volatile uint32_t* pending_register(const uint32_t source_id) {
    return (volatile uint32_t*) (plic_0_pending_base + (source_id >> 5 << 2));
}

bool kenrel_plic_is_pending(uint32_t source_id) {
    const uint32_t bit_number = source_id & 0x1f;
    const uint32_t pending_bit = *pending_register(source_id) & 1 << bit_number;
    return pending_bit != 0;
}


[[gnu::always_inline, gnu::const]]
static inline volatile uint32_t* enable_register(const uint64_t hart_id, const uint32_t source_id) {
    return (volatile uint32_t*) (plic_0_enable_base + (hart_id << 7) + (source_id >> 5 << 2));
}

void kernel_plic_enable_interrupt(const uint32_t source_id) {
    constexpr uint64_t hart_id = 0;
    const auto mmio_address = enable_register(hart_id, source_id);
    const auto bit_number = source_id & 0x1f;
    auto x = *mmio_address;
    x |= 1 << bit_number;
    *mmio_address = x;
}

void kernel_plic_disable_interrupt(const uint32_t source_id) {
    constexpr uint64_t hart_id = 0;
    const auto mmio_address = enable_register(hart_id, source_id);
    const auto bit_number = source_id & 0x1f;
    *mmio_address &= ~(1 << bit_number);
}

bool kenrel_plic_is_enabled(const uint32_t source_id) {
    constexpr uint64_t hart_id = 0;
    const auto mmio_address = enable_register(hart_id, source_id);
    const auto bit_number = source_id & 0x1f;
    return (*mmio_address & 1 << bit_number) > 0;
}


[[gnu::always_inline, gnu::const]]
static inline uint64_t context_base_for_hart(const uint64_t hart_id) {
    return plic_0_context_base + (hart_id << 13);
}


[[gnu::always_inline, gnu::const]]
static inline volatile uint32_t* threshold_register(const uint64_t hart_id) {
    return (volatile uint32_t*) (context_base_for_hart(hart_id) + context_threshold_offset);
}

uint32_t kernel_plic_get_threshold(void) {
    constexpr uint64_t hart_id = 0;
    return *threshold_register(hart_id);
}

void kernel_plic_set_threshold(const uint32_t threshold) {
    constexpr uint64_t hart_id = 0;
    *threshold_register(hart_id) = threshold;
}


[[gnu::always_inline, gnu::const]]
static inline volatile uint32_t* claim_complete_register(const uint64_t hart_id) {
    return (volatile uint32_t*) (context_base_for_hart(hart_id) + context_claim_offset);
}

uint32_t kernel_plic_claim_interrupt(void) {
    constexpr uint64_t hart_id = 0;
    return *claim_complete_register(hart_id);
}

void kernel_plic_complete_interrupt(const uint32_t source_id) {
    constexpr uint64_t hart_id = 0;
    *claim_complete_register(hart_id) = source_id;
}


void kernel_plic_init(void) {
    for (auto source_id = 0; source_id < plic_0_num_sources; source_id += 32) {
        *enable_register(0, source_id) = 0;
    }
    for (auto source_id = 0; source_id < plic_0_num_sources; ++source_id) {
        *priority_register(source_id) = 0;
    }
    kernel_plic_set_threshold(0);
    // Enable machine external interrupts
    asm ( "li a5, 0x800\n\t" "csrrs zero, mie, a5" ::: "a5" );
}
