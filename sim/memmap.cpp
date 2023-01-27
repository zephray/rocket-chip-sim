#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "memmap.h"

Memmap::Memmap() {
    this->mem = (uint64_t *)malloc(RAM_SIZE);
    assert(this->mem);
}

Memmap::~Memmap() {
    free(mem);
}

void Memmap::reset() {

}

static uint64_t get_bitmask(uint8_t mask) {
    uint64_t bm = 0;
    for (int i = 0; i < 8; i++) {
        if (mask & 0x01)
            bm |= (0xffull << i * 8);
        mask >>= 1;
    }
    return bm;
}

uint64_t Memmap::read(uint64_t addr) {
    // Unaligned access is legal
    addr -= RAM_BASE;
    addr >>= 3;
    if (addr > RAM_SIZE) {
        fprintf(stderr, "Illegal read\n");
        return 0;
    }
    return mem[addr];
}

void Memmap::write(uint64_t addr, uint64_t data, uint8_t mask) {
    // Check MMIO first
    if (addr == CON_BASE) {
        printf("%c", (int)(data & 0xff));
        fflush(stdout);
        return;
    }

    addr -= RAM_BASE;
    addr >>= 3;
    if (addr > RAM_SIZE) {
        fprintf(stderr, "Illegal write\n");
        return;
    }
    if (mask == 0xff) {
        mem[addr] = data;
    }
    else {
        uint64_t d = mem[addr];
        uint64_t bm = get_bitmask(mask);
        d &= ~bm;
        d |= data & bm;
        mem[addr] = d;
    }
}

void Memmap::load(const char *fn, size_t offset) {
    FILE *fp;
    fp = fopen(fn, "rb+");
    if (!fp) {
        fprintf(stderr, "Error: unable to open file %s\n", fn);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    size_t result = fread((void *)((size_t)mem + offset), fsize, 1, fp);
    assert(result == 1);
    fclose(fp);
}
