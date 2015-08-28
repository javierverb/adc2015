library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

use ieee.numeric_std.all;

entity signext is
	port (
		a : in std_logic_vector(15 downto 0); -- Entrada de tamaño 16
		y : out std_logic_vector(31 downto 0) -- Salida de tamaño 32
	);
end entity;
 
architecture signextx of signext is begin
	process (a) begin -- POR FAVOR CONSERVAR LA ENTRADA !!
		
		-- Si el bit mas significativo es uno relleno con uno's. 
		if (a(a'left) = '0') then

			for i in 31 downto 16 loop
				y(i) <= '0'; -- Rellenando
			end loop;
		
		-- Idem para 0 con cero's (dos formas de comparar)
		elsif (a(a'left) = '1') then 

			for i in 31 downto 16 loop
				y(i) <= '1';
			end loop;
			
		end if;

		-- El resto de los bits del vector de 32 
		-- se cargan a la salida sin modificar
		for i in 15 downto 0 loop
			y(i) <= a(i);
		end loop;

	end process;
end architecture;
