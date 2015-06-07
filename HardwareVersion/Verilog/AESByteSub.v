
module AESByteSubRow(
	input clk,
	input en,
	input [31:0] addr,
	output [31:0] data
	);
	SBoxRam sbox1(.clk(clk), .en(en), .addr(addr[ 7: 0]), .data(data[ 7: 0]));
	SBoxRam sbox2(.clk(clk), .en(en), .addr(addr[15: 8]), .data(data[15: 8]));
	SBoxRam sbox3(.clk(clk), .en(en), .addr(addr[23:16]), .data(data[23:16]));
	SBoxRam sbox4(.clk(clk), .en(en), .addr(addr[31:24]), .data(data[31:24]));
endmodule