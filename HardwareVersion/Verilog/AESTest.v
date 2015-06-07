
module AES_Test(
	input clk, 
	input rst,
	input enable,
	input [127:0] AES_Plain_Text,
	input [127:0] AES_Key,
	output [127:0] AES_Cipher
	);
	reg  [  7:0] AES_Compute_State; // state register
	reg  [127:0] AES_Key_Round[0:10]; // store key result after every schedule
	reg  [127:0] AES_Cipher_Encoded;

	wire [127:0] 

endmodule