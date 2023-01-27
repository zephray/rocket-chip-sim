`default_nettype none
module core_wrapper(
    // Input clock and reset
    input  wire         clk,
    input  wire         rst,
    // MEM
    output wire [3:0]   mem_awid,
    output wire [31:0]  mem_awaddr,
    output wire [7:0]   mem_awlen,
    output wire [2:0]   mem_awsize,
    output wire [1:0]   mem_awburst,
    output wire         mem_awvalid,
    input  wire         mem_awready,
    output wire [63:0]  mem_wdata,
    output wire [7:0]   mem_wstrb,
    output wire         mem_wlast,
    output wire         mem_wvalid,
    input  wire         mem_wready,
    output wire         mem_bready,
    input  wire [3:0]   mem_bid,
    input  wire [1:0]   mem_bresp,
    input  wire         mem_bvalid,
    output wire [3:0]   mem_arid,
    output wire [31:0]  mem_araddr,
    output wire [7:0]   mem_arlen,
    output wire [2:0]   mem_arsize,
    output wire [1:0]   mem_arburst,
    output wire         mem_arvalid,
    input  wire         mem_arready,
    output wire         mem_rready,
    input  wire [3:0]   mem_rid,
    input  wire [63:0]  mem_rdata,
    input  wire [1:0]   mem_rresp,
    input  wire         mem_rlast,
    input  wire         mem_rvalid,
    // MMIO
    output wire [3:0]   mmio_awid,
    output wire [31:0]  mmio_awaddr,
    output wire [7:0]   mmio_awlen,
    output wire [2:0]   mmio_awsize,
    output wire [1:0]   mmio_awburst,
    output wire         mmio_awvalid,
    input  wire         mmio_awready,
    output wire [63:0]  mmio_wdata,
    output wire [7:0]   mmio_wstrb,
    output wire         mmio_wlast,
    output wire         mmio_wvalid,
    input  wire         mmio_wready,
    output wire         mmio_bready,
    input  wire [3:0]   mmio_bid,
    input  wire [1:0]   mmio_bresp,
    input  wire         mmio_bvalid,
    output wire [3:0]   mmio_arid,
    output wire [31:0]  mmio_araddr,
    output wire [7:0]   mmio_arlen,
    output wire [2:0]   mmio_arsize,
    output wire [1:0]   mmio_arburst,
    output wire         mmio_arvalid,
    input  wire         mmio_arready,
    output wire         mmio_rready,
    input  wire [3:0]   mmio_rid,
    input  wire [63:0]  mmio_rdata,
    input  wire [1:0]   mmio_rresp,
    input  wire         mmio_rlast,
    input  wire         mmio_rvalid
    );

    ExampleRocketSystem dut(
        .clock(clk),
        .reset(rst),
        .mem_axi4_0_aw_ready(mem_awready),
        .mem_axi4_0_aw_valid(mem_awvalid),
        .mem_axi4_0_aw_bits_id(mem_awid),
        .mem_axi4_0_aw_bits_addr(mem_awaddr),
        .mem_axi4_0_aw_bits_len(mem_awlen),
        .mem_axi4_0_aw_bits_size(mem_awsize),
        .mem_axi4_0_aw_bits_burst(mem_awburst),
        .mem_axi4_0_aw_bits_lock(),
        .mem_axi4_0_aw_bits_cache(),
        .mem_axi4_0_aw_bits_prot(),
        .mem_axi4_0_aw_bits_qos(),
        .mem_axi4_0_w_ready(mem_wready),
        .mem_axi4_0_w_valid(mem_wvalid),
        .mem_axi4_0_w_bits_data(mem_wdata),
        .mem_axi4_0_w_bits_strb(mem_wstrb),
        .mem_axi4_0_w_bits_last(mem_wlast),
        .mem_axi4_0_b_ready(mem_bready),
        .mem_axi4_0_b_valid(mem_bvalid),
        .mem_axi4_0_b_bits_id(mem_bid),
        .mem_axi4_0_b_bits_resp(mem_bresp),
        .mem_axi4_0_ar_ready(mem_arready),
        .mem_axi4_0_ar_valid(mem_arvalid),
        .mem_axi4_0_ar_bits_id(mem_arid),
        .mem_axi4_0_ar_bits_addr(mem_araddr),
        .mem_axi4_0_ar_bits_len(mem_arlen),
        .mem_axi4_0_ar_bits_size(mem_arsize),
        .mem_axi4_0_ar_bits_burst(mem_arburst),
        .mem_axi4_0_ar_bits_lock(),
        .mem_axi4_0_ar_bits_cache(),
        .mem_axi4_0_ar_bits_prot(),
        .mem_axi4_0_ar_bits_qos(),
        .mem_axi4_0_r_ready(mem_rready),
        .mem_axi4_0_r_valid(mem_rvalid),
        .mem_axi4_0_r_bits_id(mem_rid),
        .mem_axi4_0_r_bits_data(mem_rdata),
        .mem_axi4_0_r_bits_resp(mem_rresp),
        .mem_axi4_0_r_bits_last(mem_rlast),
        .mmio_axi4_0_aw_ready(mmio_awready),
        .mmio_axi4_0_aw_valid(mmio_awvalid),
        .mmio_axi4_0_aw_bits_id(mmio_awid),
        .mmio_axi4_0_aw_bits_addr(mmio_awaddr),
        .mmio_axi4_0_aw_bits_len(mmio_awlen),
        .mmio_axi4_0_aw_bits_size(mmio_awsize),
        .mmio_axi4_0_aw_bits_burst(mmio_awburst),
        .mmio_axi4_0_aw_bits_lock(),
        .mmio_axi4_0_aw_bits_cache(),
        .mmio_axi4_0_aw_bits_prot(),
        .mmio_axi4_0_aw_bits_qos(),
        .mmio_axi4_0_w_ready(mmio_wready),
        .mmio_axi4_0_w_valid(mmio_wvalid),
        .mmio_axi4_0_w_bits_data(mmio_wdata),
        .mmio_axi4_0_w_bits_strb(mmio_wstrb),
        .mmio_axi4_0_w_bits_last(mmio_wlast),
        .mmio_axi4_0_b_ready(mmio_bready),
        .mmio_axi4_0_b_valid(mmio_bvalid),
        .mmio_axi4_0_b_bits_id(mmio_bid),
        .mmio_axi4_0_b_bits_resp(mmio_bresp),
        .mmio_axi4_0_ar_ready(mmio_arready),
        .mmio_axi4_0_ar_valid(mmio_arvalid),
        .mmio_axi4_0_ar_bits_id(mmio_arid),
        .mmio_axi4_0_ar_bits_addr(mmio_araddr),
        .mmio_axi4_0_ar_bits_len(mmio_arlen),
        .mmio_axi4_0_ar_bits_size(mmio_arsize),
        .mmio_axi4_0_ar_bits_burst(mmio_arburst),
        .mmio_axi4_0_ar_bits_lock(),
        .mmio_axi4_0_ar_bits_cache(),
        .mmio_axi4_0_ar_bits_prot(),
        .mmio_axi4_0_ar_bits_qos(),
        .mmio_axi4_0_r_ready(mmio_rready),
        .mmio_axi4_0_r_valid(mmio_rvalid),
        .mmio_axi4_0_r_bits_id(mmio_rid),
        .mmio_axi4_0_r_bits_data(mmio_rdata),
        .mmio_axi4_0_r_bits_resp(mmio_rresp),
        .mmio_axi4_0_r_bits_last(mmio_rlast),
        .l2_frontend_bus_axi4_0_aw_ready(),
        .l2_frontend_bus_axi4_0_aw_valid(1'b0),
        .l2_frontend_bus_axi4_0_aw_bits_id(8'd0),
        .l2_frontend_bus_axi4_0_aw_bits_addr(32'd0),
        .l2_frontend_bus_axi4_0_aw_bits_len(8'd0),
        .l2_frontend_bus_axi4_0_aw_bits_size(3'd0),
        .l2_frontend_bus_axi4_0_aw_bits_burst(2'd0),
        .l2_frontend_bus_axi4_0_aw_bits_lock(1'b0),
        .l2_frontend_bus_axi4_0_aw_bits_cache(4'd0),
        .l2_frontend_bus_axi4_0_aw_bits_prot(3'd0),
        .l2_frontend_bus_axi4_0_aw_bits_qos(4'd0),
        .l2_frontend_bus_axi4_0_w_ready(),
        .l2_frontend_bus_axi4_0_w_valid(1'b0),
        .l2_frontend_bus_axi4_0_w_bits_data(64'd0),
        .l2_frontend_bus_axi4_0_w_bits_strb(8'd0),
        .l2_frontend_bus_axi4_0_w_bits_last(1'b0),
        .l2_frontend_bus_axi4_0_b_ready(1'b0),
        .l2_frontend_bus_axi4_0_b_valid(),
        .l2_frontend_bus_axi4_0_b_bits_id(),
        .l2_frontend_bus_axi4_0_b_bits_resp(),
        .l2_frontend_bus_axi4_0_ar_ready(),
        .l2_frontend_bus_axi4_0_ar_valid(1'b0),
        .l2_frontend_bus_axi4_0_ar_bits_id(8'd0),
        .l2_frontend_bus_axi4_0_ar_bits_addr(32'd0),
        .l2_frontend_bus_axi4_0_ar_bits_len(8'd0),
        .l2_frontend_bus_axi4_0_ar_bits_size(3'd0),
        .l2_frontend_bus_axi4_0_ar_bits_burst(2'd0),
        .l2_frontend_bus_axi4_0_ar_bits_lock(),
        .l2_frontend_bus_axi4_0_ar_bits_cache(4'd0),
        .l2_frontend_bus_axi4_0_ar_bits_prot(3'd0),
        .l2_frontend_bus_axi4_0_ar_bits_qos(4'd0),
        .l2_frontend_bus_axi4_0_r_ready(1'b0),
        .l2_frontend_bus_axi4_0_r_valid(),
        .l2_frontend_bus_axi4_0_r_bits_id(),
        .l2_frontend_bus_axi4_0_r_bits_data(),
        .l2_frontend_bus_axi4_0_r_bits_resp(),
        .l2_frontend_bus_axi4_0_r_bits_last(),
        .resetctrl_hartIsInReset_0(1'b0),
        .debug_clock(1'b0),
        .debug_reset(1'b0),
        .debug_clockeddmi_dmi_req_ready(),
        .debug_clockeddmi_dmi_req_valid(1'b0),
        .debug_clockeddmi_dmi_req_bits_addr(7'd0),
        .debug_clockeddmi_dmi_req_bits_data(32'd0),
        .debug_clockeddmi_dmi_req_bits_op(2'd0),
        .debug_clockeddmi_dmi_resp_ready(1'b0),
        .debug_clockeddmi_dmi_resp_valid(),
        .debug_clockeddmi_dmi_resp_bits_data(),
        .debug_clockeddmi_dmi_resp_bits_resp(),
        .debug_clockeddmi_dmiClock(1'b0),
        .debug_clockeddmi_dmiReset(1'b0),
        .debug_ndreset(),
        .debug_dmactive(),
        .debug_dmactiveAck(1'b0),
        .interrupts(2'd0)
    );

endmodule