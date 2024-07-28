#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void cold_boot(void);
void warm_boot(void);

int uart_receive(uint8_t* t);
void uart_transmit(uint8_t b);

#endif //KERNEL_H
