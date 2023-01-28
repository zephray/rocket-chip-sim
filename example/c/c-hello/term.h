#pragma once

#include <stdint.h>
#include <stdbool.h>

void term_putchar(char p);
int term_print(const char *format, ...);
void term_print_string(const char *p);
void term_print_hex(uint32_t v, int digits);
//void term_print_dec(uint32_t v);
