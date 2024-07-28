#include "lib/lib.h"

static void write_prompt(void);


void ccp_main(void) {
    write_prompt();
    for (;;) {
        char c;
        console_input(&c);
    }
}


void write_prompt(void) {
    console_output('\n');
    console_output('A');
    console_output('>');
    console_output(' ');
}
