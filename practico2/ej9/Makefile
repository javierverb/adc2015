all: run

run: aludec_tb
	ghdl -r aludec_tb --stop-time=50ns --vcd=aludec.vcd

adder_tb: aludec aludec_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit aludec_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit aludec_tb	

adder: aludec.vhdl
	ghdl -a --ieee=synopsys -fexplicit aludec.vhdl

clean: 
	rm -rf aludec_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
