library ieee;
use ieee.std_logic_1164.all;

entity dmem_tb is 
end entity;

architecture arq_dmem_tb of dmem_tb is
    component dmem
          port (a: in std_logic_vector(31 downto 0);
                wd: in std_logic_vector(31 downto 0);
                clk, we: in bit;
                rd: out std_logic_vector(31 downto 0));
    end component;
    signal a1, wd1, rd1: std_logic_vector(31 downto 0);
    signal clk1, we1: bit;
begin
    prueba0: dmem port map(a=>a1, wd=>wd1, clk=>clk1, we=>we1, rd=>rd1);
    process
    begin
        a1 <= x"00010001";
        wait for 5 ns;
        a1 <= x"11100101";
        wait for 5 ns;
        a1 <= x"11104000";
        wait for 5 ns;
        a1 <= x"1121121F";
        wait for 5 ns;
        a1 <= x"AA0000AF";
        wait for 5 ns;
        a1 <= x"FFFFFFFF";
        wait for 5 ns;
    end process;
    process
    begin
        wd1 <= x"AAAAAAAA";
        wait for 5 ns;
        wd1 <= x"BBBBBBBB";
        wait for 6 ns;
        wd1 <= x"CCCCCCCC";
        wait for 7 ns;
        wd1 <= x"DDDDDDDD";
        wait for 8 ns;
        wd1 <= x"EEEEEEEE";
        wait for 9 ns;
        wd1 <= x"FFFFFFFF";
        wait for 10 ns;
        wd1 <= x"99999999";
        wait for 11 ns;
    end process;
    process
    begin
        clk1 <= '0';
        wait for 5 ns;
        clk1 <= '1';
        wait for 5 ns;
    end process;
    process
    begin
        we1 <= '0';
        wait for 6 ns;
        we1 <= '1';
        wait for 8 ns;
        we1 <= '0';
        wait for 12 ns;
        we1 <= '1';
        wait for 9 ns;
        we1 <= '0';
        wait for 7 ns;
        we1 <= '1';
        wait for 4 ns;
        we1 <= '0';
        wait for 8 ns;
    end process;
end architecture;

