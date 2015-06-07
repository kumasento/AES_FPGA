module AESEncryptTestBench;
	reg clk = 0, en = 1, rst = 1;
	initial #6 rst = 0;
	always #5 clk = ~clk;
	initial #1000 $stop;

	reg [127:0] text = 128'h3243f6a8885a308d313198a2e0370734;
	reg [127:0] key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
	wire [127:0] cipher;

	AESEncrypt aes(.clk(clk), .en(en), .rst(rst), .din(text), .key(key), .dout(cipher));

	initial
		$monitor("At time %t, dout %h", $time, cipher);

endmodule