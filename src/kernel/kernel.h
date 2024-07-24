#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void cold_boot();
void warm_boot();

void uart_transmit(uint8_t b);

#endif //KERNEL_H
