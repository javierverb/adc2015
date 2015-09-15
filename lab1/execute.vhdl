library ieee;
use ieee.std_logic_1164.all;

entity execute is
    port (RD1E, RD2E, PCPLus4E, SignImmE: in std_logic_vector(31 downto 0);
        RtE, RdE: in std_logic_vector(4 downto 0);
        RegDst, AluSrc: in std_logic;
        AluControl: in std_logic_vector(2 downto 0);
        AluOutE, WriteDataE, PCBranchE: out std_logic_vector(31 downto 0);
        zeroE: out std_logic;
        WriteRegE: out std_logic_vector(4 downto 0)
    );
end entity;

architecture execute_arq of execute is
    component alu
        port (a, b : in std_logic_vector (31 downto 0);
		        alucontrol : in std_logic_vector (2 downto 0);
		        result : out std_logic_vector (31 downto 0);
		        zero : out std_logic 
		        );
    end component;

    component mux2
        port (d0, d1 : in std_logic_vector (31 downto 0);
	        s : in std_logic;
	        y : out std_logic_vector (31 downto 0)
	    );
    end component;

    component sl2
        port (a: in std_logic_vector(31 downto 0);
		    y: out std_logic_vector(31 downto 0)
        );
    end component;

    component adder
        port (a, b : in std_logic_vector(31 downto 0);
            y : out std_logic_vector(31 downto 0)
        ); 
    end component;

signal SrcBE, sl2adder: std_logic_vector(31 downto 0);

begin

    mux2_a: mux2 port map(d0=>RtE, d1=>RdE, s=>RegDst, y=>WriteRegE);

    mux2_b: mux2 port map(d0=>RD2E, d1=>SignImmE, s=>AluSrc, y=>SrcBE); 

    alu_a: alu port map(a=>RD1E ,b=>SrcBE, alucontrol=>AluControl,
                        result=>AluOutE,
                        zero=>zeroE
                        );
    sl2_a: sl2 port map(a=>SignImmE, y=>sl2adder);

    adder1: adder port map(a=>sl2adder,b=>PCPLus4E,y=>PCBranchE);

WriteDataE<=RD2E;

end architecture;
