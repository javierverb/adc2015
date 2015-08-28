all: run

run: alu_tb
	ghdl -r alu_tb --stop-time=50ns --vcd=alu.vcd

alu_tb: alu alu_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit alu_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit alu_tb	

alu: alu.vhdl
	ghdl -a --ieee=synopsys -fexplicit alu.vhdl

clean: 
	rm -rf alu_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
