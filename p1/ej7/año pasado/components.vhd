-------------------------------------------------------------------------------
--
-- Title       : components
-- Design      : Mips
-- Author      : Eduardo Sanchez
-- Company     : Famaf
--
-------------------------------------------------------------------------------
--
-- File        : components.vhd
--
-------------------------------------------------------------------------------
--
-- Description : Archivo de definiciones y componentes comunes al diseño.
--
-------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.all;

package components is
    -- constantes:	
	constant MIPS_SOFT_FILE: string := "//home//eduardo//docencia//virtual//mips.dat";
	constant MEMORY_DUMP_FILE: string := "mem.dump";

component adder is -- adder
  port(a, b: in  STD_LOGIC_VECTOR(31 downto 0);
       y:    out STD_LOGIC_VECTOR(31 downto 0));
end component;

component aludec is -- ALU control decoder
  port(funct:      in  STD_LOGIC_VECTOR(5 downto 0);
       aluop:      in  STD_LOGIC_VECTOR(1 downto 0);
       alucontrol: out STD_LOGIC_VECTOR(2 downto 0));
end component;

component alu is -- Arithmetic/Logic unit with add/sub, AND, OR, set less than
  port(a, b:       in  STD_LOGIC_VECTOR(31 downto 0);
       alucontrol: in  STD_LOGIC_VECTOR(2 downto 0);
       result:     out STD_LOGIC_VECTOR(31 downto 0);
       zero:       out STD_LOGIC);
end component;

component controller is -- single cycle control decoder
  port(Op, Funct:          in  STD_LOGIC_VECTOR(5 downto 0);
       MemToReg, MemWrite: out STD_LOGIC;
       AluSrc:      out STD_LOGIC;
       RegDst, RegWrite:   out STD_LOGIC;
       Jump:               out STD_LOGIC;		 
       AluControl:         out STD_LOGIC_VECTOR(2 downto 0);
       Branch: 				out STD_LOGIC);
end component;

component datapath is  -- single-path Datapath
  port(  clk, reset:        in  STD_LOGIC;
         MemToReg, Branch:   in  STD_LOGIC;
         AluSrc, RegDst:    in  STD_LOGIC;
         RegWrite, Jump:    in  STD_LOGIC;
         AluControl:        in  STD_LOGIC_VECTOR(2 downto 0);
         pc:                out STD_LOGIC_VECTOR(31 downto 0);
         instr:             out  STD_LOGIC_VECTOR(31 downto 0);
         MemWrite: 			  in STD_LOGIC;
         dump:				  in STD_LOGIC);
end component;

component dmem is -- data memory
  port(clk, we:  in STD_LOGIC;
       a, wd:    in STD_LOGIC_VECTOR(31 downto 0);
       rd:       out STD_LOGIC_VECTOR(31 downto 0);
       dump: in STD_LOGIC
		 );
end component;

component flopr is -- flip-flop with synchronous reset
  generic(width: integer);
  port(clk, reset: in  STD_LOGIC;
       d:          in  STD_LOGIC_VECTOR(width-1 downto 0);
       q:          out STD_LOGIC_VECTOR(width-1 downto 0));
end component;

component imem is -- instruction memory
  port(a:  in  STD_LOGIC_VECTOR(5 downto 0);
       rd: out STD_LOGIC_VECTOR(31 downto 0));
end component;

component maindec is -- main control decoder
  port(Op:                 in  STD_LOGIC_VECTOR(5 downto 0);
       MemToReg, MemWrite: out STD_LOGIC;
       Branch, AluSrc:     out STD_LOGIC;
       RegDst, RegWrite:   out STD_LOGIC;
       Jump:               out STD_LOGIC;
       AluOp:              out  STD_LOGIC_VECTOR(1 downto 0));
end component;

component mips is -- single cycle MIPS processor
  port(clk, reset:      in  STD_LOGIC;
       pc:              out STD_LOGIC_VECTOR(31 downto 0);
       instr:           out  STD_LOGIC_VECTOR(31 downto 0);
       dump:			in STD_LOGIC
		 );
end component;

component mux2 is -- two-input multiplexer
  generic(width: integer);
  port(d0, d1: in  STD_LOGIC_VECTOR(width-1 downto 0);
       s:      in  STD_LOGIC;
       y:      out STD_LOGIC_VECTOR(width-1 downto 0));
end component;

component regfile is 
  port(clk:           in  STD_LOGIC;
       we3:           in  STD_LOGIC;
       ra1, ra2, wa3: in  STD_LOGIC_VECTOR(4 downto 0);
       wd3:           in  STD_LOGIC_VECTOR(31 downto 0);
       rd1, rd2:      out STD_LOGIC_VECTOR(31 downto 0));
end component;

component signext is -- sign extender
  port(a: in  STD_LOGIC_VECTOR(15 downto 0);
       y: out STD_LOGIC_VECTOR(31 downto 0));
end component;

component sl2 is -- shift left by 2
  port(a: in  STD_LOGIC_VECTOR(31 downto 0);
       y: out STD_LOGIC_VECTOR(31 downto 0));
end component;

		
end components;
