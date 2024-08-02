#ifndef KERNEL_UART_H
#define KERNEL_UART_H


void kernel_uart_init(void);
void kernel_uart_flush_receive_fifo(void);
void kernel_uart_flush_transmit_fifo(void);

bool kernel_uart_is_data_ready(void);
int kernel_uart_receive(char* b);

void kernel_uart_transmit(char b);


#endif //KERNEL_UART_H
