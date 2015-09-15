library ieee;
use ieee.std_logic_1164.all;

entity fetch is
    port(JumpM, PcSrcM, clk, reset: in std_logic;
        PcBranchM: in std_logic_vector(31 downto 0);
        InstrF, PCF, PCPLus4F: out std_logic_vector(31 down to 0)
    );
end entity

architecture fetch_arq of fetch is
--declaracion de los componentes internos del modulo fetch
    component adder
        port(a, b : in std_logic_vector(31 downto 0);
            y : out std_logic_vector(31 downto 0));
        );
    end component;

    component mux2
        port (d0, d1 : in std_logic_vector (31 downto 0);
            s : in std_logic;
            y : out std_logic_vector (31 downto 0)
        );
    end component;

    component flopr
        port (d : in std_logic_vector(31 downto 0);
            q : out std_logic_vector(31 downto 0);
            clk, reset : in std_logic);
    end component;

    component imem
        port (a : in std_logic_vector(0 to 6);
            rd : out std_logic_vector(31 downto 0)
        );
--------------------------------------------------------

signal PCPLus4F_f: std_logic_vector(31 downto 0);
signal PC0, PC1, PCJump, PCF: std_logic_vector (31 downto 0);
signal cuatro: std_logic_vector(31 downto 0) := x"00000004";

PCJump<=PCPlus4F1(31 downto 28) & Instrf_s(25 downto 0) & "00";
PCPLus4F<=PCPLus4F_f;

begin

    mux2_a: mux2 port map(d0=>PCPLus4F_f, d1=>PCBranchM, s=>PcSrcM, y=>PC0);

    mux2_b: mux2 port map(d0=>PC0, d1=>PCJump, s=>JumpM, y=>PC1);

    flopr1: flopr port map(d=>PC1, clk=>clk, reset=>reset, q=>PCF);

    imem1: imem port map(a=>PCF(7 downto 2), rd=>InstrF);

    adder1: adder port map(a=>PCF, b=>cuatro, PCPLus4F_f);

end architecture;
