#include <stdarg.h>
#include <stdint.h>
#include "term.h"

#define uart ((volatile uint32_t *)0x60000000)

volatile uint32_t *uart_ptr = uart;

void term_putchar(char c) {
	*uart_ptr = (uint32_t)c;
}

void term_print_string(const char *p) {
    while ((*p) && (*p != 0xFF))
        term_putchar(*p++);
}

void term_print_hex(uint32_t v, int digits) {
    for (int i = 7; i >= 0; i--) {
        char c = "0123456789abcdef"[(v >> (4*i)) & 15];
        if (c == '0' && i >= digits) continue;
        term_putchar(c);
        digits = i;
    }
}

static void printf_d(int val) {
	char buffer[32];
	char *p = buffer;
	if (val < 0) {
		term_putchar('-');
		val = -val;
	}
	while (val || p == buffer) {
		*(p++) = '0' + val % 10;
		val = val / 10;
	}
	while (p != buffer)
		term_putchar(*(--p));
}

int printf(const char *format, ...) {
	int i;
	va_list ap;

	va_start(ap, format);

	for (i = 0; format[i]; i++)
		if (format[i] == '%') {
			while (format[++i]) {
				if (format[i] == 'c') {
					term_putchar(va_arg(ap,int));
					break;
				}
				if (format[i] == 's') {
					term_print_string(va_arg(ap,char*));
					break;
				}
				if (format[i] == 'd') {
					printf_d(va_arg(ap,int));
					break;
				}
				if (format[i] == 'x') {
					term_print_hex(va_arg(ap,int), 4);
					break;
				}
			}
		} else
			term_putchar(format[i]);

	va_end(ap);
}


