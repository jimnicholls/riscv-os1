#include "lib/lib.h"

static void write_prompt(void);


void ccp_main(void) {
    // ReSharper disable once CppDFAEndlessLoop
    for (;;) {
        write_prompt();
        char c = '\0';
        while (c != '\r') {
            console_input(&c);
        }
        // TODO: Process the input
        print_string("\n?\n");
    }
}


void write_prompt(void) {
    print_string("A> ");
}
