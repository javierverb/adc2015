--librerias
library IEEE;
use IEEE.STD_LOGIC_1164.all;

--entidades
entity aludec is
port(
    funct: in std_logic_vector(0 to 5);
    aluop: in std_logic_vector(0 to 1);
    alucontrol: out std_logic_vector(0 to 2)
    );
end entity;

--arquitectura
architecture arch_aludec of aludec is 
begin
    process
        variable temp: std_logic_vector(0 to 2);
    begin
        case aluop is
            when "00" => temp:= "010";
            when "01" => temp:= "110";
            when others =>
                case funct is
                    when "100000" => temp := "010";
                    when "100010" => temp := "110";
                    when "100100" => temp := "000";
                    when "100101" => temp := "001";
                    when "101010" => temp := "111";
                    when others => temp := "UUU";
                end case;
        end case;
        alucontrol <= temp;
    end process;
end architecture;
