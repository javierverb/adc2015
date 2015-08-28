all: run

run: flopr_tb
	ghdl -r flopr_tb --stop-time=50ns --vcd=flopr.vcd

flopr_tb: flopr flopr_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit flopr_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit flopr_tb	

flopr: flopr.vhdl
	ghdl -a --ieee=synopsys -fexplicit flopr.vhdl

clean: 
	rm -rf flopr_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
