OBJS = start.o firmware.o stdlib.o term.o
CFLAGS = -MD -O1 -march=rv64imafdc -mcmodel=medany -ffreestanding -nostdlib -Wl,--no-relax
TOOLCHAIN_PREFIX = riscv64-unknown-elf-

all: firmware.bin firmware.dump

firmware.bin: firmware.elf
	$(TOOLCHAIN_PREFIX)objcopy -O binary $< $@

firmware.dump: firmware.elf
	$(TOOLCHAIN_PREFIX)objdump -d $< > $@

firmware.elf: $(OBJS) sections.lds
	$(TOOLCHAIN_PREFIX)gcc $(CFLAGS) -Wl,-Bstatic,-T,sections.lds,-Map,firmware.map,--strip-debug -o $@ $(OBJS) -lgcc
	size $@

%.o: %.c
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<

%.o: %.S
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<

clean:
	rm -rf *.o *.d *.elf *.bin *.map

.PHONY: clean

-include *.d

