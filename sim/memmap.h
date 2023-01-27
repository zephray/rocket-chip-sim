#pragma once

#define CON_BASE            (0x60000000)

#define RAM_BASE            (0x80000000)
#define RAM_SIZE            (256 * 1024 * 1024)

class Memmap {
public:
    Memmap();
    ~Memmap();
    void reset();
    uint64_t read(uint64_t addr);
    void write(uint64_t addr, uint64_t data, uint8_t mask);
    void load(const char *fn, size_t offset);
private:
    uint64_t *mem;
};
