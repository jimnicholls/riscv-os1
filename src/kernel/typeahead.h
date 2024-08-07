#ifndef KERNEL_TYPEAHEAD_H
#define KERNEL_TYPEAHEAD_H


void kernel_typeahead_reset(void);
void kernel_typeahead_on_uart_interrupt(void);

bool kernel_typeahead_is_empty(void);
bool kernel_typeahead_is_full(void);

bool kernel_typeahead_getchar(char* c);
bool kernel_typeahead_immediate_getchar(char* c);
bool kernel_typeahead_putchar(char c);


#endif //KERNEL_TYPEAHEAD_H
