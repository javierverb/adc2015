library ieee;
use ieee.std_logic_1164.all;
 
entity mux2_tb is
end mux2_tb;

architecture behav of mux2_tb is
	component mux2 is
		port (
			s: in std_logic;
			d0, d1: in std_logic_vector (31 downto 0);
			y: out std_logic_vector (31 downto 0)
		);
	end component;

	signal d0_s, d1_s, y_s: std_logic_vector(31 downto 0);
	signal s_s: std_logic;

	-- Luego de declarar los componentes y las señales,
	begin

		-- Mapeo de puertos
		mux2_map: mux2 port map (d0=>d0_s, d1=>d1_s, 
									y=>y_s, s=>s_s);
	
	-- Puedo precargar valores
	d0_s <= x"00000FF0";
	d1_s <= x"FFFFF00F";
	
	-- Comportamiento para cada señal s
	process begin
		s_s <= '0';
		wait for 15 ns;
		-- La salida y_s debería dar el valor d0
		assert y_s = d0_s;
		s_s <= '1';
		wait for 15 ns;
		assert y_s = d1_s;
		
		assert false report "Fin del test" severity note;
	end process;
end architecture;
