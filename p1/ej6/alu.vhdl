library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
--use ieee.std_logic_arith.all;


entity alu is
	port (a, b : in std_logic_vector (31 downto 0); -- Entradas del sumador 
		alucontrol : in std_logic_vector (2 downto 0);
		result : out std_logic_vector (31 downto 0);
		zero : out std_logic 
		); -- Resultado del sumador
end entity;

architecture alux of alu is begin
	process (alucontrol, a, b) is
		variable resultx : std_logic_vector (31 downto 0); begin
			case alucontrol is
				when "000" => resultx := a and b;
				when "001" => resultx := a or b;
				when "010" => resultx := std_logic_vector(unsigned(a) + unsigned(b));
				when "100" => resultx := a and not(b);
				when "101" => resultx := a or not(b);
				when "110" => resultx := std_logic_vector(unsigned(a) - unsigned(b));
				when "111" => 
					if a < b then
						resultx := x"00000001";
					else 
						resultx := x"00000000";			
					end if;
				when others => resultx :=  "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
			end case;
		-- Al ser código secuencial, es conveniente 
		-- dejar lo más simple posible la ejecución del case: 
		-- El if se chequea afuera.
		if (resultx = x"00000000") then
			zero <= '1';
		else 
			zero <= '0';
		end if;

		-- La salida se asigna al final de todo.
		result <= resultx;
	end process;
end architecture;