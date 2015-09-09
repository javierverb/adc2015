all: run

run: regfile_tb
	ghdl -r regfile_tb --stop-time=100ns --vcd=regfile.vcd

regfile: regfile.vhd
	ghdl -a regfile.vhd

regfile_tb: regfile regfile_tb.vhd
	ghdl -a regfile_tb.vhd
	ghdl -e regfile_tb

clean: 
	rm -rf regfile_tb	rm -rf *.o rm -rf *.cf rm -rf *.vcd rm *.vhd~ rm Makefile~
