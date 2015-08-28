all: run

run: mux2_tb
	ghdl -r mux2_tb --stop-time=50ns --vcd=mux2.vcd

mux2_tb: mux2 mux2_tb.vhdl
	ghdl -a --ieee=synopsys -fexplicit mux2_tb.vhdl
	ghdl -e --ieee=synopsys -fexplicit mux2_tb	

mux2: mux2.vhdl
	ghdl -a --ieee=synopsys -fexplicit mux2.vhdl

clean: 
	rm -rf mux2_tb
	rm -rf *.o
	rm -rf *.cf
	rm -rf *.vcd
