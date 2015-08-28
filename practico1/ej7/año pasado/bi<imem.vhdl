library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity imem is
		port (
			a : in integer range 0 to 63;
			rd : out std_logic_vector(31 downto 0)
		);
end entity;

architecture imemx of imem is
begin
	process (a)
		type trom is array (0 to 63) of std_logic_vector(31 downto 0);
		variable rom : trom;
	begin
		for i in 0 to 63 loop
			rom(i) := std_logic_vector(to_unsigned(i, 32));
		end loop;
		rd <= rom(a);
	end process;
end architecture;