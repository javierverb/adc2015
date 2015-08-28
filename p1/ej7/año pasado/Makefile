all: run

run: imem_tb
	ghdl -r imem_tb --stop-time=50ns --vcd=imem.vcd

imem_tb: imem imem_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit imem_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit imem_tb	

imem: imem.vhdl
	ghdl -a --ieee=synopsys -fexplicit imem.vhdl

clean: 
	rm -rf imem_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
