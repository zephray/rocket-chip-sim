// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

void irq_handler(uint64_t cause, uint64_t status, uint64_t epc) {
    // printf("EXCEPTION\nMCAUSE = %d", cause);
    // printf("\nMSTATUS = %d", status);
    // printf("\nMEPC = %d", epc);
    while (1);
}

uint64_t rdcycle()
{
	int cycles;
	asm volatile ("rdcycle %0" : "=r"(cycles));
	// printf("[time() -> %d]", cycles);
	return cycles;
}

uint64_t rdinstret()
{
	int insns;
	asm volatile ("rdinstret %0" : "=r"(insns));
	// printf("[insn() -> %d]", insns);
	return insns;
}

volatile uint32_t *UART_TXFIFO = (volatile uint32_t *)0x60000000;
__attribute__((used)) int _write(int fd, char *buf, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
		*UART_TXFIFO = (uint32_t)buf[i];
    }

    return size;
}

__attribute__((used)) void *_sbrk(ptrdiff_t incr)
{
    extern char _end[];
    extern char _heap_end[];
    static char *curbrk = _end;

    if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
    return NULL - 1;

    curbrk += incr;
    return curbrk - incr;
}
