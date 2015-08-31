library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;

entity sl2 is
    port (a: in std_logic_vector(31 downto 0);
		y: out std_logic_vector(31 downto 0));
end sl2;
 
architecture sl2x of sl2 is begin
    y <= std_logic_vector(unsigned(a) sll 2);
end sl2x;
