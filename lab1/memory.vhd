library ieee;
use ieee.std_logic_1164.all;

entity memory is
    port(AluOutM, WriteDataM: in std_logic_vector(31 downto 0);
        ZeroM, MemWrite, Branch, clk, dump: in std_logic;
        ReadDat: out std_logic_vector(31 downto 0);
        PCSrcM:out std_logic
    );
end entity;

architecture memory_arq of memory is
    component dmem
        generic (bits: integer := 32; words: integer := 64);
        port (
            a, wd: in std_logic_vector(bits-1 downto 0);
            rd: out std_logic_vector(bits-1 downto 0);
            clk, we: in bit
            dump: in std_logic
        );
    end component;

begin

    PCSrcM<=(Branch and ZeroM); --salida
    AluOutM<=AluOutM; -- salida

    dmem_a: dmem port map(a=>AluOutM, wd=>WriteDataM, clk=>clk, we=>MemWrite,
                        rd=>ReadDat --salida
                        );
end architecture;
    








end architecture;
