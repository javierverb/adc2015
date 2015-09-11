library ieee;
use ieee.std_logic_1164.all;

entity fetch is
    port( Jump, PcSrcM, clk, reset: in std_logic;
        PcBranchM: in std_logic_vector(31 downto 0);
        InstrF, PCF, PCPLus4F: out std_logic_vector(31 down to 0)
    );

architecture fetch_arq of fetch is
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
