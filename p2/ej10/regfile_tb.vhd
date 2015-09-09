library ieee;
use ieee.std_logic_1164.all;

entity regfile_tb is
end entity;

architecture behaviour of regfile_tb is
    component regfile
        port (ra1, ra2, wa3: in std_logic_vector(4 downto 0);
              wd3: in std_logic_vector(31 downto 0);
              we3, clk: in std_logic;
              rd1, rd2: out std_logic_vector(31 downto 0));
    end component;
    signal ra1, ra2, wa3: std_logic_vector(4 downto 0);
    signal wd3, rd1, rd2: std_logic_vector(31 downto 0);
    signal we3, clk: std_logic;
begin
    prueba: regfile port map (ra1, ra2, wa3, wd3, we3, clk, rd1, rd2);
    process
    begin
        clk <= '0';
        wait for 5 ns;
        clk <= '1';
        wait for 5 ns;
    end process;
    process
    begin
        we3 <= '1';
        wait for 15 ns;
        we3 <= '0';
        wait for 10 ns;
    end process;
    process
    begin
        wd3 <= x"ab120abb";
        wait for 5 ns;
        wd3 <= x"fff01bba";
        wait for 5 ns;
        wd3 <= x"abc99fff";
        wait for 5 ns;
        wd3 <= x"88888999";
        wait for 10 ns;
        wd3 <= x"66ff1010";
        wait for 5 ns;
        wd3 <= x"44ff8acc";
        wait for 5 ns;
        wd3 <= x"67bfaf11";
        wait for 5 ns;
    end process;        
    process
    begin
        wa3 <= "00001";
        ra1 <= "00001";
        ra2 <= "11111";
        wait for 5 ns;
        wa3 <= "00010";
        ra1 <= "00110";
        ra2 <= "00010";
        wait for 5 ns;
        wa3 <= "11111";
        ra1 <= "00010";
        ra2 <= "11111";
        wait for 5 ns;
        wa3 <= "10100";
        ra1 <= "10100";
        ra2 <= "00011";
        wait for 5 ns;
        wa3 <= "00011";
        ra1 <= "00011";
        ra2 <= "10100";
        wait for 5 ns;
        wa3 <= "00110";
        ra1 <= "10100";
        ra2 <= "00000";
        wait for 5 ns;
    end process;
end architecture;
