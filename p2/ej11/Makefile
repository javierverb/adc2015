all: run

run: maindec_tb
	ghdl -r adder_tb --stop-time=50ns --vcd=maindec.vcd

adder_tb: maindec maindec_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit maindec_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit maindec_tb	

adder: maindec.vhdl
	ghdl -a --ieee=synopsys -fexplicit maindec.vhdl

clean: 
	rm -rf maindec_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
