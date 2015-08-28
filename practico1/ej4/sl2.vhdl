library ieee;
use ieee.numeric_std.all;

entity sl2 is
    port (a: in unsigned (31 downto 0);
		y: out unsigned (31 downto 0));
end sl2;
 
architecture sl2x of sl2 is
    begin
    	y <= a sll 2;
end sl2x;
