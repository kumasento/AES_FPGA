
// AES plain text are organized first by column, and then by row

module AESByteSubColumn(
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

module AESByteSub(
	input clk, 
	input en,
	input [127:0] addr,
	output [127:0] data
	);
	AESByteSubColumn subcol1(.clk(clk), .en(en), .addr(addr[127: 96]), .data(data[127: 96]));
	AESByteSubColumn subcol2(.clk(clk), .en(en), .addr(addr[ 95: 64]), .data(data[ 95: 64]));
	AESByteSubColumn subcol3(.clk(clk), .en(en), .addr(addr[ 63: 32]), .data(data[ 63: 32]));
	AESByteSubColumn subcol4(.clk(clk), .en(en), .addr(addr[ 31:  0]), .data(data[ 31:  0]));
endmodule