library ieee;
use ieee.std_logic_1164.all;

entity writeback is
    port(AluOutW: in std_logic_vector(31 downto 0);
        ReadDataW: in std_logic_vector(31 downto 0);
        MemToReg: in std_logic;
        ResultW: out std_logic_vector(31 downto 0)
    );
end entity;

architecture writeback_arq of writeback is
    component mux2
        port (d0, d1 : in std_logic_vector (31 downto 0);
            s : in std_logic;
            y : out std_logic_vector (31 downto 0)
        );
    end component;

begin
    mux2_w: mux2 port map(d0=>AluOutW, d1=>ReadDataW, s=>MemToReg, 
                        y=>ResultW); --salida
end architecture;
