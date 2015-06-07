
module SBoxRamTestBench;
	reg clk = 0;
	reg en = 1;
	reg [7:0] addr = 0;
	wire [7:0] data;

	always #5 clk = ~clk;

	SBoxRam sbox(.clk(clk), .en(en), .addr(addr), .data(data));

	always #10 addr <= addr + 1;

	initial 
		#200 $stop;
	initial 
		$monitor("At time %t, addr=%h data=%h", $time, addr, data);

endmodule