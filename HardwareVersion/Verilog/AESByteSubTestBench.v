
module AESByteSubTestBench;
	
	reg clk = 0;
	reg en = 1;
	reg [31:0] addr = 0;
	wire [31:0] data;
	initial 
		#10000 $stop;
	always #5 clk = ~clk;
	always #10 addr = addr + 1;

	AESByteSubColumn bytesubcol(.clk(clk), .en(en), .addr(addr), .data(data));

	initial 
		$monitor("at time %t, addr=%h, data=%h", $time, addr, data);


endmodule