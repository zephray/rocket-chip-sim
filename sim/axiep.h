#pragma once

class AXIEp {
public:
    AXIEp(Memmap *memmap);
    ~AXIEp();
    void reset();
    void apply(uint8_t awid, uint32_t awaddr, uint8_t awlen, uint8_t awsize,
        uint8_t awburst, uint8_t awvalid, uint8_t &awready, uint64_t wdata,
        uint8_t wstrb, uint8_t wlast, uint8_t wvalid, uint8_t &wready,
        uint8_t bready, uint8_t &bid, uint8_t &bresp, uint8_t &bvalid,
        uint8_t arid, uint32_t araddr, uint8_t arlen, uint8_t arsize,
        uint8_t arburst, uint8_t arvalid, uint8_t &arready, uint8_t rready,
        uint8_t &rid, uint64_t &rdata, uint8_t &rresp, uint8_t &rlast, 
        uint8_t &rvalid);
private:
    typedef struct {
        // Request
        uint64_t addr;
        uint8_t id;
        uint8_t size;
        uint8_t len;
        uint8_t burst;
        // State
        int beatcount;
        uint8_t firstbeat;
        int bubble;
    } req_t;

    // Current processing request
    req_t read_req;
    req_t write_req;

    Memmap *memmap;

    uint64_t get_bitmask(uint8_t mask);
    int get_beats(uint8_t size, uint8_t len);
};
