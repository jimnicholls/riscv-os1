#ifndef KERNEL_STDIO_H
#define KERNEL_STDIO_H

#include <stdio.h>

int kernel_stdio_regetch(FILE* stream);
bool kernel_stdio_has_ungetch(FILE* stream);
int kernel_stdio_peek_ungetch(FILE* stream);

#endif //KERNEL_STDIO_H
