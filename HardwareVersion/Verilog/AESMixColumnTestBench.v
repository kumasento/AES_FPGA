
module AESMixColumnTestBench;
	reg [31:0] din1 = 32'hd4bf5d30;
	reg [31:0] din2 = 32'he0b452ae;
	reg [31:0] din3 = 32'hb84111f1;
	reg [31:0] din4 = 32'h1e2798e5;
	wire [31:0] dout1, dout2, dout3, dout4;

	reg clk = 0, en = 1;
	always #5 clk = ~clk;
	initial 
		#1000 $stop;

	AESMixColumn mix1(.clk(clk), .en(en), .din(din1), .dout(dout1));
	AESMixColumn mix2(.clk(clk), .en(en), .din(din2), .dout(dout2));
	AESMixColumn mix3(.clk(clk), .en(en), .din(din3), .dout(dout3));
	AESMixColumn mix4(.clk(clk), .en(en), .din(din4), .dout(dout4));

	initial 
		$monitor("at time %t, dout={%h,%h,%h,%h}", $time, dout1, dout2, dout3, dout4);

endmodule