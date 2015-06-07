
module AESEncrypt(
	input clk,
	input en,
	input rst, // reset the state
	input [127:0] din,
	input [127:0] key,
	output [127:0] dout
	);

	reg [7:0] state;
	reg [127:0] cipher;
	reg [127:0] keys [0:9];
	
	wire [127:0] key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9, key_0;

	// key schedule list
	AESKeySchedule key_step_01(.clk(clk), .en(en), .round( 1), .din(key    ), .dout(key_0));
	AESKeySchedule key_step_02(.clk(clk), .en(en), .round( 2), .din(keys[0]), .dout(key_1));
	AESKeySchedule key_step_03(.clk(clk), .en(en), .round( 3), .din(keys[1]), .dout(key_2));
	AESKeySchedule key_step_04(.clk(clk), .en(en), .round( 4), .din(keys[2]), .dout(key_3));
	AESKeySchedule key_step_05(.clk(clk), .en(en), .round( 5), .din(keys[3]), .dout(key_4));
	AESKeySchedule key_step_06(.clk(clk), .en(en), .round( 6), .din(keys[4]), .dout(key_5));
	AESKeySchedule key_step_07(.clk(clk), .en(en), .round( 7), .din(keys[5]), .dout(key_6));
	AESKeySchedule key_step_08(.clk(clk), .en(en), .round( 8), .din(keys[6]), .dout(key_7));
	AESKeySchedule key_step_09(.clk(clk), .en(en), .round( 9), .din(keys[7]), .dout(key_8));
	AESKeySchedule key_step_10(.clk(clk), .en(en), .round(10), .din(keys[8]), .dout(key_9));

	reg [127:0] reg_sub;
	wire [127:0] sub, shift, mix;
	AESByteSub bytesub(.clk(clk), .en(en), .addr(cipher), .data(sub));
	
	AESMixColumn mixcol1(.clk(clk), .en(en), .din(shift[127: 96]), .dout(mix[127: 96]));
	AESMixColumn mixcol2(.clk(clk), .en(en), .din(shift[ 95: 64]), .dout(mix[ 95: 64]));
	AESMixColumn mixcol3(.clk(clk), .en(en), .din(shift[ 63: 32]), .dout(mix[ 63: 32]));
	AESMixColumn mixcol4(.clk(clk), .en(en), .din(shift[ 31:  0]), .dout(mix[ 31:  0]));

	always @(posedge clk) begin
	if (rst) begin 
		state <= 0; 
	end
	else begin
		if (en) begin // only work when the enable signal is set
			state <= state + 1;
			case (state[7:1])
			7'd0: begin // initialize step, round 0
				cipher 		<= din ^ key;
			end
			7'd1: begin
				reg_sub 	<= sub; 
				keys[0] 	<= key_0;
			end
			7'd2: begin
				cipher 		<= mix ^ keys[0];
			end
			7'd3: begin
				reg_sub		<= sub;
				keys[1]		<= key_1;
			end
			7'd4: begin
				cipher 		<= mix ^ keys[1];
			end
			7'd5: begin
				reg_sub 	<= sub;
				keys[2] 	<= key_2;
			end
			7'd6: begin
				cipher		<= mix ^ keys[2];
			end
			7'd7: begin
				reg_sub 	<= sub;
				keys[3] 	<= key_3;
			end
			7'd8: begin
				cipher		<= mix ^ keys[3];
			end
			7'd9: begin
				reg_sub 	<= sub;
				keys[4] 	<= key_4;
			end
			7'd10: begin
				cipher		<= mix ^ keys[4];
			end
			7'd11: begin
				reg_sub 	<= sub;
				keys[5] 	<= key_5;
			end
			7'd12: begin
				cipher		<= mix ^ keys[5];
			end
			7'd13: begin
				reg_sub 	<= sub;
				keys[6] 	<= key_6;
			end
			7'd14: begin
				cipher		<= mix ^ keys[6];
			end
			7'd15: begin
				reg_sub 	<= sub;
				keys[7] 	<= key_7;
			end
			7'd16: begin
				cipher		<= mix ^ keys[7];
			end
			7'd17: begin
				reg_sub 	<= sub;
				keys[8] 	<= key_8;
			end
			7'd18: begin
				cipher		<= mix ^ keys[8];
			end
			7'd19: begin
				reg_sub 	<= sub;
				keys[9] 	<= key_9;
			end
			7'd20: begin
				cipher		<= shift ^ keys[9];
			end
			endcase
		end
	end
	end
	assign dout = cipher;

	assign shift = {
		reg_sub[127:120], reg_sub[ 87: 80], reg_sub[ 47: 40], reg_sub[  7:  0],
		reg_sub[ 95: 88], reg_sub[ 55: 48], reg_sub[ 15:  8], reg_sub[103: 96],
		reg_sub[ 63: 56], reg_sub[ 23: 16], reg_sub[111:104], reg_sub[ 71: 64],
		reg_sub[ 31: 24], reg_sub[119:112], reg_sub[ 79: 72], reg_sub[ 39: 32]
	};
endmodule