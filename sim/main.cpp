#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "config.h"
#include "memmap.h"
#include "axiep.h"

// Verilator related
#include "Vcore_wrapper.h"
Vcore_wrapper *core;
Memmap *memmap;
AXIEp *ram_ep;
AXIEp *mmio_ep;
VerilatedVcdC *trace;
uint64_t tickcount;

// Settings
bool enable_trace = false;
bool quiet = false;
bool unlimited = true;
uint64_t trace_from = 0;
uint64_t max_cycles = 100;

// Used by model
double sc_time_stamp() {
    // This is in pS. Currently we use a 10ns (100MHz) clock signal.
    return (double)tickcount * (double)CLK_PREIOD_PS;
}

void tick() {
    // Create local copy of input signals
    uint8_t mem_awready = core->mem_awready;
    uint8_t mem_wready = core->mem_wready;
    uint8_t mem_bid = core->mem_bid;
    uint8_t mem_bresp = core->mem_bresp;
    uint8_t mem_bvalid = core->mem_bvalid;
    uint8_t mem_arready = core->mem_arready;
    uint8_t mem_rid = core->mem_rid;
    uint64_t mem_rdata = core->mem_rdata;
    uint8_t mem_rresp = core->mem_rresp;
    uint8_t mem_rlast = core->mem_rlast;
    uint8_t mem_rvalid = core->mem_rvalid;
    uint8_t mmio_awready = core->mmio_awready;
    uint8_t mmio_wready = core->mmio_wready;
    uint8_t mmio_bid = core->mmio_bid;
    uint8_t mmio_bresp = core->mmio_bresp;
    uint8_t mmio_bvalid = core->mmio_bvalid;
    uint8_t mmio_arready = core->mmio_arready;
    uint8_t mmio_rid = core->mmio_rid;
    uint64_t mmio_rdata = core->mmio_rdata;
    uint8_t mmio_rresp = core->mmio_rresp;
    uint8_t mmio_rlast = core->mmio_rlast;
    uint8_t mmio_rvalid = core->mmio_rvalid;

    ram_ep->apply(
        core->mem_awid,
        core->mem_awaddr,
        core->mem_awlen,
        core->mem_awsize,
        core->mem_awburst,
        core->mem_awvalid,
        mem_awready,
        core->mem_wdata,
        core->mem_wstrb,
        core->mem_wlast,
        core->mem_wvalid,
        mem_wready,
        core->mem_bready,
        mem_bid,
        mem_bresp,
        mem_bvalid,
        core->mem_arid,
        core->mem_araddr,
        core->mem_arlen,
        core->mem_arsize,
        core->mem_arburst,
        core->mem_arvalid,
        mem_arready,
        core->mem_rready,
        mem_rid,
        mem_rdata,
        mem_rresp,
        mem_rlast,
        mem_rvalid
    );

    mmio_ep->apply(
        core->mmio_awid,
        core->mmio_awaddr,
        core->mmio_awlen,
        core->mmio_awsize,
        core->mmio_awburst,
        core->mmio_awvalid,
        mmio_awready,
        core->mmio_wdata,
        core->mmio_wstrb,
        core->mmio_wlast,
        core->mmio_wvalid,
        mmio_wready,
        core->mmio_bready,
        mmio_bid,
        mmio_bresp,
        mmio_bvalid,
        core->mmio_arid,
        core->mmio_araddr,
        core->mmio_arlen,
        core->mmio_arsize,
        core->mmio_arburst,
        core->mmio_arvalid,
        mmio_arready,
        core->mmio_rready,
        mmio_rid,
        mmio_rdata,
        mmio_rresp,
        mmio_rlast,
        mmio_rvalid
    );

    // Clock posedge
    core->clk = 1;
    core->eval();

    // Apply changed input signals after clock edge
    core->mem_awready = mem_awready;
    core->mem_wready = mem_wready;
    core->mem_bid = mem_bid;
    core->mem_bresp = mem_bresp;
    core->mem_bvalid = mem_bvalid;
    core->mem_arready = mem_arready;
    core->mem_rid = mem_rid;
    core->mem_rdata = mem_rdata;
    core->mem_rresp = mem_rresp;
    core->mem_rlast = mem_rlast;
    core->mem_rvalid = mem_rvalid;
    core->mmio_awready = mmio_awready;
    core->mmio_wready = mmio_wready;
    core->mmio_bid = mmio_bid;
    core->mmio_bresp = mmio_bresp;
    core->mmio_bvalid = mmio_bvalid;
    core->mmio_arready = mmio_arready;
    core->mmio_rid = mmio_rid;
    core->mmio_rdata = mmio_rdata;
    core->mmio_rresp = mmio_rresp;
    core->mmio_rlast = mmio_rlast;
    core->mmio_rvalid = mmio_rvalid;

    // Let combinational changes propergate
    core->eval();
    if (enable_trace && (tickcount >= trace_from))
        trace->dump(tickcount * CLK_PREIOD_PS);

    // Clk negedge
    core->clk = 0;    
    core->eval();
    if (enable_trace && (tickcount >= trace_from))
        trace->dump(tickcount * CLK_PREIOD_PS + CLK_HALF_PERIOD_PS);
    
    tickcount++;
}

void reset() {
    core->rst = 0;
    tick();
    core->rst = 1;
    for (int i = 0; i < 10; i++) {
        tick();
    }
    core->rst = 0;
    memmap->reset();
    ram_ep->reset();
    mmio_ep->reset();
}

int main(int argc, char *argv[]) {
    printf("Another rocket simulator\n");

    // Initialize testbench
    Verilated::commandArgs(argc, argv);
    Verilated::assertOn(false);

    core = new Vcore_wrapper;
    memmap = new Memmap();
    ram_ep = new AXIEp(memmap);
    mmio_ep = new AXIEp(memmap);
    Verilated::traceEverOn(true);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ram") == 0) {
            if (i == (argc - 1)) {
                fprintf(stderr, "Error: no RAM image filename provided\n");
                exit(1);
            }
            else {
                memmap->load(argv[i + 1], RAM_LOAD_OFFSET);
            }
        }
        else if (strcmp(argv[i], "--limit") == 0) {
            if (i == (argc - 1)) {
                fprintf(stderr, "Error: no cycle limit provided\n");
                exit(1);
            }
            else {
                max_cycles = atoll(argv[i + 1]);
                printf("Cycle limit set to %lu.\n", max_cycles);
                unlimited = false;
            }
        }
        else if (strcmp(argv[i], "--trace") == 0) {
            trace_from = 0;
            enable_trace = true;
        }
        else if (strcmp(argv[i], "--trace_from") == 0) {
            trace_from = atoll(argv[i + 1]);
            printf("Trace would only start after %lu cycles.\n", trace_from);
            enable_trace = true;
        }
    }

    if (enable_trace) {
        trace = new VerilatedVcdC;
        core->trace(trace, 99);
        trace->open("trace.vcd");        
    }

    // Start simulation
    if (!quiet)
        printf("Simulation start.\n");

    clock_t time = clock();

    reset();

    bool running = true;
    while (running) {
        tick();

        if ((!unlimited) && (tickcount > max_cycles)) {
            break;
        }
    }

    if (!quiet)
        printf("Stop.\n");

    time = clock() - time;
    time /= (CLOCKS_PER_SEC / 1000);
    if (!quiet)
        printf("Executed %ld cycles in %ld ms. Average clock speed: %ld kHz\n",
                tickcount, time, tickcount / time);

    if (enable_trace) {
        trace->close();
        delete trace;
    }

    delete ram_ep;
    delete mmio_ep;
    delete memmap;
    delete core;

    return 0;
}