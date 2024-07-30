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
    print_string("A> ");
}
