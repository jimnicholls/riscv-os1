#include "lib/lib.h"

static void write_prompt(void);


void ccp_main(void) {
    write_prompt();
    for (;;) {
        char c;
        console_input(&c);
        if (c == '\r') {
            // TODO: Process the command input
            print_string("\n?\n");
            write_prompt();
        }
    }
}


void write_prompt(void) {
    print_string("A> ");
}
