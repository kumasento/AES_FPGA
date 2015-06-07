module AESKeySchedule(
	input clk,
	input en,
	input [3:0] round,
	input [127:0] din,
	output [127:0] dout
	);
	reg [31:0] din1, din2, din3, din4;
	reg [31:0] rcon;
	always @(posedge clk) begin
	if (en) begin
		din1 <= din[127: 96];
		din2 <= din[ 95: 64];
		din3 <= din[ 63: 32];
		din4 <= din[ 31:  0];
		case (round) 
		4'h1: rcon <= 32'h01000000; 4'h2: rcon <= 32'h02000000; 4'h3: rcon <= 32'h04000000; 4'h4: rcon <= 32'h08000000;
		4'h5: rcon <= 32'h10000000; 4'h6: rcon <= 32'h20000000; 4'h7: rcon <= 32'h40000000; 4'h8: rcon <= 32'h80000000;
		4'h9: rcon <= 32'h1b000000;	4'hA: rcon <= 32'h36000000;
		endcase
	end
	end
	wire [31:0] rot, sub;

	assign rot  = {din4[23:16], din4[15:8], din4[7:0], din4[31:24]};
	AESByteSubColumn bytesub(.clk(clk), .en(en), .addr(rot), .data(sub));

	assign dout[127: 96] = din1 ^ sub ^ rcon;
	assign dout[ 95: 64] = din2 ^ dout[127: 96];
	assign dout[ 63: 32] = din3 ^ dout[ 95: 64];
	assign dout[ 31:  0] = din4 ^ dout[ 63: 32];
endmodule