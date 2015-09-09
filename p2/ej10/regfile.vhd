--implementacion de la memoria RAM
--librerias
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--entidades
entity regfile is
    port (
            rd1, rd2: out std_logic_vector(31 downto 0);
            wd3: in std_logic_vector(31 downto 0);
            ra1, ra2, wa3: in std_logic_vector(4 downto 0);
            we3, clk: in std_logic
        );
end entity;

--iniciando arquitectura
architecture regfile_32 of regfile is
    type mem_regfile is array (0 to 63) of std_logic_vector(31 downto 0); --Es una matriz
begin
    process(clk)
        variable mem: mem_regfile := (0 => x"00000000", others => "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU");
    begin
        if(clk'EVENT and clk='1') then
            -- quiero leer
            rd1 <= mem(to_integer(unsigned(ra1)));
            rd2 <= mem(to_integer(unsigned(ra2)));
            -- quiero escribir
            if (we3='1') then
                mem(to_integer(unsigned(wa3))) := wd3;
            end if;
        end if;
    end process;
end architecture;
