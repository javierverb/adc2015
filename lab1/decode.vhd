library ieee;
use ieee.std_logic_1164.all;

entity decode is
    port(InstrD, Wd3: in std_logic_vector(31 downto 0);
        A3: in std_logic_vector(4 downto 0);
        RegWrite, clk:in std_logic;
        RtD,RdD: out std_logic_vector(4 downto 0);
        SignImmD, RD1D, RD2D: out std_logic_vector(31 downto 0)
    );
end entity;

architecture decode_arq of fetch is
--declaracion de los componentes internos del modulo DECODE
    component regfile
         port (
            rd1, rd2: out std_logic_vector(31 downto 0);
            wd3: in std_logic_vector(31 downto 0);
            ra1, ra2, wa3: in std_logic_vector(4 downto 0);
            we3, clk: in std_logic
            );
    end component;

    component signext
        port (
		a : in std_logic_vector(15 downto 0);
		y : out std_logic_vector(31 downto 0)
	    );
    end component;
------------------------------------------------------------
begin

    signext_d: signext port map(a=>InstrD(15 downto 0), 
                                y=>SignImmD); --salida

    regfile_d: regfile port map(ra1=>InstrD(25 downto 21),
                            ra2=>InstrD(20 downto 16),
                            wa3=>A3;
                            wd3=>Wd3;
                            clk=>CLK;
                            we3=>RegWrite;
                            rd1=>RD1D; --salida
                            rd2=>RD2D --salida
                            );

    RtD<=InstrD(20 downto 16); --salida
    RdD<=InstrD(15 downto 11); --salida

--los marcados con salida, son las salidas del modulo decode
end architecture;
