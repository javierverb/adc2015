-- implementacion de la memoria dmem
-- librerias
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- entidades
-- a = direccion, wd = dato a ingresar, clk = reloj, we = 1(escritura) 
-- o 0(lectura)
entity dmem is
    generic (bits: integer := 32; words: integer := 64);
    port (
            a, wd: in std_logic_vector(bits-1 downto 0);
            rd: out std_logic_vector(bits-1 downto 0);
            clk, we: in bit
        );
end entity;

-- iniciando arquitectura
architecture rom_32 of dmem is
    type type_mem is array (0 to words-1) of std_logic_vector(bits-1 downto 0); --Es una matriz
begin
    process(clk)
        variable position: integer;
        variable mem: type_mem;
    begin
        --inicializando la memoria
        for var in 0 to words-1 loop
            mem(var) := std_logic_vector(to_unsigned(var, bits));
        end loop;
        if (clk'EVENT and clk='1') then
            --de "a" copio de 7 a 2
            position := to_integer(unsigned(a(7 downto 2)));
            --si quiero escribir la memoria
            if (we='1') then
                mem(position) := wd;
                rd<=wd;
            --si quiero leer
            else
                rd<=mem(position);
            end if;
        end if;
    end process;
end architecture;
