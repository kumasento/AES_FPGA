
module AESMod(input [8:0] din,output [7:0] dout);
	reg [7:0] ext;
	reg [7:0] byte;
	always @(din) begin
		byte <= din[7:0];
		ext <= (din[8]) ? 7'h1b : 7'h0;
	end
	assign dout = ext ^ byte;
endmodule

// there're 4 kind of columns, 1-4

module AESMixColumn(input clk, input en, input [31:0] din, output [31:0] dout);
	AESMixColumn1 mix1(.clk(clk), .en(en), .din(din), .dout(dout[31:24]));
	AESMixColumn2 mix2(.clk(clk), .en(en), .din(din), .dout(dout[23:16]));
	AESMixColumn3 mix3(.clk(clk), .en(en), .din(din), .dout(dout[15: 8]));
	AESMixColumn4 mix4(.clk(clk), .en(en), .din(din), .dout(dout[ 7: 0]));
endmodule

// its combination logic
module AESMixColumn1(input clk, input en, input [31:0] din, output [7:0] dout);
	wire [8:0] tmp_in1, tmp_in2;
	wire [7:0] tmp_out1, tmp_out2;

	reg [7:0] b1, b2, b3, b4;
	always @(posedge clk) begin
	if (en) begin
		b4 <= din[ 7: 0];
		b3 <= din[15: 8];
		b2 <= din[23:16];
		b1 <= din[31:24];
	end
	end

	assign tmp_in1 = {b1, 1'b0};
	assign tmp_in2 = {b2, 1'b0};
	AESMod mod1(.din(tmp_in1), .dout(tmp_out1));
	AESMod mod2(.din(tmp_in2), .dout(tmp_out2));
	assign dout = tmp_out1 ^ tmp_out2 ^ b2 ^ b3 ^ b4;
endmodule

module AESMixColumn2(input clk, input en, input [31:0] din, output [7:0] dout);
	reg [7:0] b1, b2, b3, b4;
	always @(posedge clk) begin
	if (en) begin
		b4 <= din[ 7: 0];
		b3 <= din[15: 8];
		b2 <= din[23:16];
		b1 <= din[31:24];
	end
	end

	wire [8:0] tmp_in1, tmp_in2;
	wire [7:0] tmp_out1, tmp_out2;
	
	assign tmp_in1 = {b2, 1'b0};
	assign tmp_in2 = {b3, 1'b0};
	AESMod mod1(.din(tmp_in1), .dout(tmp_out1));
	AESMod mod2(.din(tmp_in2), .dout(tmp_out2));
	assign dout = tmp_out1 ^ tmp_out2 ^ b3 ^ b1 ^ b4;
endmodule

module AESMixColumn3(input clk, input en, input [31:0] din, output [7:0] dout);
	reg [7:0] b1, b2, b3, b4;
	always @(posedge clk) begin
	if (en) begin
		b4 <= din[ 7: 0];
		b3 <= din[15: 8];
		b2 <= din[23:16];
		b1 <= din[31:24];
	end
	end

	wire [8:0] tmp_in1, tmp_in2;
	wire [7:0] tmp_out1, tmp_out2;
	
	assign tmp_in1 = {b3, 1'b0};
	assign tmp_in2 = {b4, 1'b0};
	AESMod mod1(.din(tmp_in1), .dout(tmp_out1));
	AESMod mod2(.din(tmp_in2), .dout(tmp_out2));
	assign dout = tmp_out1 ^ tmp_out2 ^ b4 ^ b1 ^ b2;
endmodule

module AESMixColumn4(input clk, input en, input [31:0] din, output [7:0] dout);
	reg [7:0] b1, b2, b3, b4;
	always @(posedge clk) begin
	if (en) begin
		b4 <= din[ 7: 0];
		b3 <= din[15: 8];
		b2 <= din[23:16];
		b1 <= din[31:24];
	end
	end

	wire [8:0] tmp_in1, tmp_in2;
	wire [7:0] tmp_out1, tmp_out2;
	
	assign tmp_in1 = {b4, 1'b0};
	assign tmp_in2 = {b1, 1'b0};
	AESMod mod1(.din(tmp_in1), .dout(tmp_out1));
	AESMod mod2(.din(tmp_in2), .dout(tmp_out2));
	assign dout = tmp_out1 ^ tmp_out2 ^ b1 ^ b2 ^ b3;
endmodule