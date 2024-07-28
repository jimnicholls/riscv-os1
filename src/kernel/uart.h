#ifndef KERNEL_UART_H
#define KERNEL_UART_H

#include <stdint.h>

void uart_init(void);
int uart_receive(uint8_t* b);

#endif //KERNEL_UART_H
