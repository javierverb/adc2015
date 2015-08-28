all: run

run: signext_tb
	ghdl -r signext_tb --stop-time=50ns --vcd=signext.vcd

signext_tb: signext signext_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit signext_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit signext_tb	

signext: signext.vhdl
	ghdl -a --ieee=synopsys -fexplicit signext.vhdl

clean: 
	rm -rf signext_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
