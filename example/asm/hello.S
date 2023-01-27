// This program prints "Hello, world!", then idles

#define CON_BASE    0x60000000

.section .text.start, "ax", @progbits
.globl _start
_start:
    li t0, CON_BASE
    la t1, str
loadchar:
    lb t2, 0(t1)
    addi t1, t1, 1
    beq t2, zero, done
sendchar:
    sw t2, 0(t0)
    j loadchar
done:
    wfi
    j done

.section .rodata
str:
.string "Hello, world!\n"
