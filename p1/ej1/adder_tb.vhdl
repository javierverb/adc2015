library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--  Un testbench no tiene puertos.
entity adder_tb is
end adder_tb;
 
architecture behav of adder_tb is
    --  Declaración del componente que será instanciado.
    component adder is
    
        port (a, b : in std_logic_vector (31 downto 0);
                y : out std_logic_vector (31 downto 0));

    end component;
    signal a_s, b_s, y_s: std_logic_vector (31 downto 0);

    --  Instanciamos el componente.
    begin
        adder_0: adder port map (a => a_s, b => b_s, y => y_s);   
        --  Este process hace realmente el trabajo.
        process begin
            a_s <= x"FFF000FF";
            b_s <= x"000FFF00";
            wait for 10 ns;
            assert y_s = x"FFFFFFFF";
            a_s <= x"AAA000CC";
            b_s <= x"000FFF00";
            wait for 10 ns;
            assert y_s = x"AAAFFFCC";
            a_s <= x"12345678";
            b_s <= x"00000000";
            wait for 10 ns;
            assert y_s = x"12345678";
            assert false report "Fin del test" severity note;
        end process;
end behav;
