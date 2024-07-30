#ifndef KERNEL_UART_H
#define KERNEL_UART_H

#include <stdint.h>


void kernel_uart_init(void);

int kernel_uart_receive(uint8_t* b);
void kernel_uart_transmit(uint8_t b);


#endif //KERNEL_UART_H
