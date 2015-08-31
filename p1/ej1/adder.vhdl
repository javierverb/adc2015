library ieee;
use ieee.std_logic_1164.all;


entity adder is
    port (a, b : in std_logic_vector(31 downto 0); -- Entradas del sumador 
            y : out std_logic_vector(31 downto 0)); -- Resultado del sumador
end adder;

architecture adderx of adder is
    begin
    y <= a xor b;
end adderx;
