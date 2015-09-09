all: run

run: dmem_tb
	ghdl -r dmem_tb --stop-time=100ns --vcd=dmem.vcd

dmem: dmem.vhd
	ghdl -a dmem.vhd

dmem_tb: dmem dmem_tb.vhd
	ghdl -a dmem_tb.vhd
	ghdl -e dmem_tb

clean: 
	rm -rf dmem_tb	rm -rf *.o rm -rf *.cf rm -rf *.vcd rm *.vhd~ rm Makefile~
