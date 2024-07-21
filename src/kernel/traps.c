[[gnu::aligned(4), gnu::interrupt, gnu::visibility("hidden")]]
void trap_handler(void) {
    for(;;);
}
