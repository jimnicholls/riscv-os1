#include "lib/lib.h"
#include "kernel/system_control_block.h"


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
    if (g_scb.current_user != 0) {
        console_output('0' + g_scb.current_user);
    }
    console_output('A' + g_scb.current_drive);
    print_string("> ");
}
