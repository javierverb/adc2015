library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity problema_8_tb is
end entity;

architecture test_bench of problema_8_tb is
  function to_string (sv: std_logic_vector) return string is
    use std.textio.all;
    variable bv : bit_vector (sv'range) := to_bitvector (sv);
    variable lp : line;
  begin
    write (lp, bv);
    return lp.all;
  end;
  component dmem
  port(a, wd: in std_logic_vector(31 downto 0);
       rd: out std_logic_vector(31 downto 0);
       clk, we: in std_logic);
  end component;
  signal sa, swd, srd : std_logic_vector(31 downto 0);
  signal sclk, swe : std_logic;
begin
  tb_component : dmem port map (a => sa, wd => swd, rd => srd, clk => sclk, we => swe);
  process
  begin
    sclk <= '1';
    wait for 1 ns;
    sclk <= '0';
    wait for 1 ns;
  end process;
  process
  begin
    swe <= '1';
    wait for 5 ns;
    sa <= "00110101000110000101001001000001";
    swd <= "00100001110000001000101010100011";
    wait for 5 ns;
    sa <= "00010100101000000110010010010101";
    swd <= "11000101000110000110010000100001";
    wait for 5 ns;
    sa <= "00100100000100010101001110001010";
    swd <= "00011110000001101000100000100101";
    wait for 5 ns;
    sa <= "01100011010010101100000100010000";
    swd <= "01010000001001010011000001101100";
    wait for 5 ns;
    sa <= "00101001000110001101010001000101";
    swd <= "00110001010011010010100000010010";
    wait for 5 ns;
    swe <= '0';
    wait for 5 ns;
    sa <= "01100011010010101100000100010000";
    wait for 5 ns;
--    report "srd vector value: " & to_string(srd);
    assert srd = "01010000001001010011000001101100";
    sa <= "00100100000100010101001110001010";
    wait for 5 ns;
--    report "srd vector value: " & to_string(srd);
    assert srd = "00011110000001101000100000100101";
    sa <= "00110101000110000101001001000001";
    wait for 5 ns;
--    report "srd vector value: " & to_string(srd);
    assert srd = "00100001110000001000101010100011";
    sa <= "00101001000110001101010001000101";
    wait for 5 ns;
--    report "srd vector value: " & to_string(srd);
    assert srd = "00110001010011010010100000010010";
    sa <= "00010100101000000110010010010101";
    wait for 5 ns;
--    report "srd vector value: " & to_string(srd);
    assert srd = "11000101000110000110010000100001";
  end process;
end architecture;
