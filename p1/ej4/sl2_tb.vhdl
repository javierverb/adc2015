library ieee;
use ieee.numeric_std.all;
-- El type Hexadecimal se encuentra acá:
use ieee.std_logic_1164.all;

entity sl2_tb is
end sl2_tb;

architecture behav of sl2_tb is
    component sl2 is
        port (
            a: in std_logic_vector(31 downto 0);
            y: out std_logic_vector(31 downto 0)
        );
    end component;

    signal a_s, y_s: std_logic_vector(31 downto 0);

    -- Luego de declarar los componentes y las señales,
    begin

        -- Mapeo de puertos
        sl2_map: sl2 port map (a=>a_s, y=>y_s);
    
    -- Puedo precargar valores
    a_s <= "00000000000000000000000000001111";
    -- Comportamiento para cada señal s
    process begin
        wait for 15 ns;
        -- La salida y_s debería dar el valor a_s desplazado 2bits
        assert y_s = "00000000000000000000000000111100";
        assert false report "Fin del test" severity note;
    end process;

end architecture;
