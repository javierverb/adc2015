all: run

run: adder_tb
	ghdl -r adder_tb --stop-time=50ns --vcd=adder.vcd

adder_tb: adder adder_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit adder_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit adder_tb	

adder: adder.vhdl
	ghdl -a --ieee=synopsys -fexplicit adder.vhdl

clean: 
	rm -rf adder_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
