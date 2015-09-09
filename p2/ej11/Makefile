all: run

run: maindec_tb
	ghdl -r maindec_tb --stop-time=100ns --vcd=maindec.vcd

maindec: maindec.vhd
	ghdl -a maindec.vhd

maindec_tb: maindec maindec_tb.vhd
	ghdl -a maindec_tb.vhd
	ghdl -e maindec_tb

clean: 
	rm -rf maindec_tb rm -rf *.o rm -rf *.cf rm -rf *.vcd rm *.vhd~ rm Makefile~
