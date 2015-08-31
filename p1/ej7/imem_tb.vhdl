library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity imem_tb is
end imem_tb;

architecture behav of imem_tb is
    component imem is
        port (
            a: in std_logic_vector(0 to 6);
            rd: out std_logic_vector(31 downto 0)
        );
    end component;

    signal a_s: std_logic_vector(0 to 6);
    signal rd_s: std_logic_vector(31 downto 0);

    -- Luego de declarar los componentes y las señales,
    begin

    -- Mapeo de puertos
    imem_map: imem port map(a=>a_s, rd=>rd_s);

    -- El comportamiento es simple, dada una señal a_s
    -- La salida es un vector dentro de la posición de la 
    -- rom[a_s]
    process begin
        a_s <= "000001"; -- 2
        wait for 15 ns;
        assert rd_s = x"00000001";
        a_s <= "100000";
        wait for 15 ns;
        assert rd_s = x"00000020";
    end process;
end architecture;