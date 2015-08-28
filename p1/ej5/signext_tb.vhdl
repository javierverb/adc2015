library ieee;

-- El type Hexadecimal se encuentra acá:
use ieee.std_logic_1164.all;

entity signext_tb is
end signext_tb;

architecture behav of signext_tb is
	component signext is
		port (
			a: in std_logic_vector (15 downto 0);
			y: out std_logic_vector (31 downto 0)
		);
	end component;

	signal a_s: std_logic_vector (15 downto 0);
	signal y_s: std_logic_vector (31 downto 0);

	-- Luego de declarar los componentes y las señales,
	begin
		-- Mapeo de puertos
		signext_map: signext port map (a=>a_s, y=>y_s);
	
	
	-- Comportamiento para cada señal _s
	process begin
		-- Puedo precargar valores
		a_s <= x"0000";
		wait for 15 ns;
		-- La salida y_s debería dar el valor a_s más 16bits
		-- con del bit más significativo
		assert y_s = x"00000000";
		assert false report "Fin del test" severity note;
		
	end process;
end architecture;
