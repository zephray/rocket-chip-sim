#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "term.h"

void irq_handler(uint64_t cause, uint64_t status, uint64_t epc) {
    term_print_string("EXCEPTION\nMCAUSE = 0x");
    term_print_hex(cause, 8);
    term_print_string("\nMSTATUS = 0x");
    term_print_hex(status, 8);
    term_print_string("\nMEPC = 0x");
    term_print_hex(epc, 8);
    while (1);
}

void main() {
	printf("Hello, world!\n");
    while (1);
}
