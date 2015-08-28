all: run

run: sl2_tb
	ghdl -r sl2_tb --stop-time=50ns --vcd=sl2.vcd

sl2_tb: sl2 sl2_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit sl2_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit sl2_tb	

sl2: sl2.vhdl
	ghdl -a --ieee=synopsys -fexplicit sl2.vhdl

clean: 
	rm -rf sl2_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
