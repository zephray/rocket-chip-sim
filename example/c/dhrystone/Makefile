OBJS = start.o dhry_1.o dhry_2.o stdlib.o
CFLAGS = -MD -O3 -march=rv64imafdc -mcmodel=medany -DTIME -DRISCV -DUSE_MYSTDLIB -ffreestanding -nostdlib
TOOLCHAIN_PREFIX = riscv64-unknown-elf-

all: dhry.bin dhry.dump

dhry.bin: dhry.elf
	riscv64-unknown-elf-objcopy -O binary $< $@

dhry.dump: dhry.elf
	$(TOOLCHAIN_PREFIX)objdump -d $< > $@

dhry.elf: $(OBJS) sections.lds
	$(TOOLCHAIN_PREFIX)gcc $(CFLAGS) -Wl,-Bstatic,-T,sections.lds,-Map,dhry.map,--strip-debug -o $@ $(OBJS) -lgcc
	size $@

%.o: %.c
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<

%.o: %.S
	$(TOOLCHAIN_PREFIX)gcc -c $(CFLAGS) $<

dhry_1.o dhry_2.o: CFLAGS += -Wno-implicit-int -Wno-implicit-function-declaration

clean:
	rm -rf *.o *.d dhry.elf dhry.map dhry.bin

.PHONY: clean

-include *.d

