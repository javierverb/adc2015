library ieee;
use ieee.std_logic_1164.all;
 
entity flopr_tb is
end flopr_tb;

architecture behav of flopr_tb is
	component flopr is
		port (
			d: in std_logic_vector (31 downto 0);
			clk, reset : in  std_logic;
			q: out std_logic_vector (31 downto 0)
		);
	end component;

	signal rst_s, clk_s: std_logic;
	signal q_s: std_logic_vector(31 downto 0); 
	signal d_s: std_logic_vector (31 downto 0);

	-- Luego de declarar los componentes y las señales,
	begin

		-- Mapeo de puertos
		ff_map: flopr port map (clk=>clk_s, reset=>rst_s, 
								d=>d_s, q=>q_s);
	
	d_s <= x"0FF00FF0";
	-- Comportamiento síncrono
	process begin
		clk_s <= '0';
		wait for 5 ns;
		clk_s <= '1';
		wait for 5 ns;
	end process;

	-- Comportamiento por cada pulso de clock
	process begin
		rst_s <= '1';
		wait for 5 ns;
		rst_s <= '0';
		wait for 10 ns;
		-- corroboramos que la entrada se haya almacenado
		assert q_s = d_s;
		assert false report "Fin del test" severity note;
	end process;
end;
