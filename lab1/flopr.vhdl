library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity flopr is
    port (
        -- Valor a almacenar
        d : in std_logic_vector(31 downto 0);
        -- Salida del valor almacenado
        q : out std_logic_vector(31 downto 0);
        clk, reset : in std_logic);
end entity;

architecture floprx of flopr is begin
    process (clk, reset) begin -- Dadas dos entradas, hacer:
        if (reset = '1') then
            q <= conv_std_logic_vector('0', 32); -- q = x"00000000"
        elsif (clk'event and clk='1') then
            q <= d;
        end if;
    end process;
end architecture;