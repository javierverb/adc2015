library ieee;
use ieee.std_logic_1164.all;

entity mux2 is
    port (
	d0, d1 : in std_logic_vector (31 downto 0);
	s : in std_logic;
	y : out std_logic_vector (31 downto 0)
	);
end mux2;
 
architecture mux2x of mux2 is begin
	process (s) begin
		if (s = '0') then --Asincronico en reset
			y <= d0;
		elsif (s = '1') then 
			y <= d1;
		end if;
	end process;
end architecture;