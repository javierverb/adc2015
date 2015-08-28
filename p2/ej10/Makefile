all: run

run: regfile_tb
	ghdl -r regfile_tb --stop-time=50ns --vcd=regfile.vcd

adder_tb: regfile v_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit regfile_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit regfile_tb	

adder: regfile.vhdl
	ghdl -a --ieee=synopsys -fexplicit regfile.vhdl

clean: 
	rm -rf regfile_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
