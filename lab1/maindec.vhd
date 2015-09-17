--librerias
library ieee;
use ieee.std_logic_1164.all;

--entidades
entity maindec is
    port(
        Op: in std_logic_vector(5 downto 0);
        MemToReg, MemWrite, Branch, AluSrc, RegDst, RegWrite, Jump: out std_logic;
        AluOp: out std_logic_vector(1 downto 0)
        );
end entity;

--arquitectura
architecture maindec_32 of maindec is
begin
    process
        variable resultado_aux: std_logic_vector(8 downto 0);
    begin
        case Op is
            when "000000" => resultado_aux := ("110000010");
            when "100011" => resultado_aux := "101001000";
            when "101011" => resultado_aux := "001010000";
            when "000100" => resultado_aux := "000100001";
            when "001000" => resultado_aux := "101000000";
            when "000010" => resultado_aux := "000000100";
            when others => resultado_aux := ("---------");
        end case;
        RegWrite <= resultado_aux(8);
        RegDst <= resultado_aux(7);
        AluSrc <= resultado_aux(6);
        Branch <= resultado_aux(5);
        MemWrite <= resultado_aux(4);
        MemToReg <= resultado_aux(3);
        Jump <= resultado_aux(2);
        AluOp <= resultado_aux(1 downto 0);
    end process;
end architecture;
