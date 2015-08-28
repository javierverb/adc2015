all: run

run: dmem_tb
	ghdl -r dmem_tb --stop-time=50ns --vcd=dmem.vcd

adder_tb: dmem dmem_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit dmem_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit dmem_tb	

adder: dmem.vhdl
	ghdl -a --ieee=synopsys -fexplicit dmem.vhdl

clean: 
	rm -rf dmem_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
