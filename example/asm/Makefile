SRCS = $(wildcard *.S)
ELF = $(SRCS:.S=.elf)
BIN = $(SRCS:.S=.bin)
DUMP = $(SRCS:.S=.dump)

CROSS_COMPILE ?= riscv64-unknown-elf-
GCC = $(CROSS_COMPILE)gcc
#CFLAGS = -mabi=lp64 -march=rv64ima
CFLAGS = -march=rv64imafd
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

default: elf bin dump

.PHONY: elf
elf: $(ELF)

.PHONY: bin
bin: $(BIN)

.PHONY: dump
dump: $(DUMP)

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.elf: %.S linker.ld
	$(GCC) $(CFLAGS) -Tlinker.ld $< -nostdlib -static -o $@

%.dump: %.elf
	$(OBJDUMP) -d $< > $@

clean:
	rm -f *.elf *.dump *.bin
