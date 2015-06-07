module AESKeyScheduleTestBench;

	reg clk = 0, en = 1;
	always #5 clk = ~clk;
	reg [127:0] din = 128'h2b7e151628aed2a6abf7158809cf4f3c;
	wire [127:0] dout, dout2;
	reg [3:0] round = 1;
	

	parameter [3:0] round1 = 1;
	parameter [3:0] round2 = 2;
	AESKeySchedule keysched1(.clk(clk), .en(en), .din(din), .dout(dout), .round(round1));
	AESKeySchedule keysched2(.clk(clk), .en(en), .din(dout), .dout(dout2), .round(round2));
	initial
		#1000 $stop;
	initial 
		$monitor("at time %t, dout=%h dout2=%h", $time, dout, dout2);

endmodule