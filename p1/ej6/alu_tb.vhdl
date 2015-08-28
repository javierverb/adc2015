library ieee;
use ieee.std_logic_1164.all;
 
entity alu_tb is
end alu_tb;

architecture behav of alu_tb is
	component alu is
		port (
			a, b: in std_logic_vector (31 downto 0);
			alucontrol: in std_logic_vector (2 downto 0);
			result: out std_logic_vector (31 downto 0);
			zero: out std_logic
		);
	end component;

	signal a_s, b_s: std_logic_vector (31 downto 0);
	signal alucontrol_s: std_logic_vector (2 downto 0);
	signal result_s: std_logic_vector (31 downto 0);
	signal zero_s: std_logic;

	-- Luego de declarar los componentes y las señales,
	begin

		-- Mapeo de puertos
		alu_map: alu port map (a=>a_s, b=>b_s, 
								alucontrol=>alucontrol_s,
								result=>result_s,
								zero=>zero_s);
	-- Puedo precargar valores
	a_s <= x"00000FF0";
	b_s <= x"FFFFF00F";
	
	-- Comportamiento para cada señal s
	process begin
		-- Cada operación de la alu 
		-- con el valor esperado se debe satisfacer
		alucontrol_s <= "000";
		wait for 5 ns;
		assert result_s = x"00000000";
		assert zero_s = '1';
		
		-- a or b
		alucontrol_s <= "001";
		wait for 5 ns;
		assert result_s = x"FFFFFFFF";

		-- a + b
		alucontrol_s <= "010";
		wait for 5 ns;
		assert result_s = x"FFFFFFFF";

		-- a and not(b)
		alucontrol_s <= "100";
		wait for 5 ns;
		assert result_s = x"00000FF0";

		-- a or not(b)
		alucontrol_s <= "101";
		wait for 5 ns;
		assert result_s = x"00000FF0";

		-- a - b
		alucontrol_s <= "110";
		wait for 5 ns;
		assert zero_s = '0';

		-- Slt: a < b => 1
		alucontrol_s <= "111";
		wait for 5 ns;
		assert result_s = x"00000001";

		-- alucontrol_s = 011
		alucontrol_s <= "011";
		wait for 5 ns;
		assert result_s = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
		assert false report "Fin del test" severity note;
	end process;
end architecture;
