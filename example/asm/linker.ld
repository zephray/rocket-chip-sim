SECTIONS
{
    ROM_BASE = 0x80000000;

    . = ROM_BASE;
    .text.start : { *(.text.start) }
}
