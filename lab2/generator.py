# -*- coding: utf-8 -*-
import random

list_modes = ["E", "e", "R", "r"]

def get_mode():
    mode = ""
    while mode not in list_modes:
        print "Ahora seleccione un modo de ejecución"
        mode = raw_input("Modo: [E | e | R | r]\n")
    return mode

def get_value_int(value):
    value_int = ""
    while not value_int.isdigit():
        value_int = raw_input("Ingrese una cantidad numérica para %s\n" % value)
    return value_int

def get_custom_mode():
    mode = ""
    while mode not in ["S", "s", "n", "N"]:
        mode = raw_input("¿Generar automáticamente? \n [S | s] | n\n")
    return mode == "s" or mode == "S"

def main():

    c_m = get_custom_mode()

    if not c_m:
        m = get_mode()
        N = get_value_int("N")
        k = get_value_int("k")
        j = get_value_int("j")
    else: 
        m = str(random.choice(list_modes))
        N = str(random.randint(2, 100))
        k = str(random.randint(1, 100))
        j = str(random.randint(1, 20))


    filename = "mode%s_N%s_k%s_j%s.txt" % (m, N, k, j)

    output = m+"\n"+N+"\n"+k+"\n"+j+"\n"
    for i in range(int(j)):
        output += str(random.randint(0, int(N)-1)) + " "
        output += str(random.randint(0, int(N)-1)) + " "
        output += str(random.random()*10) + "\n"

    f = open(filename, "w")
    f.write(output)
    f.close()
    print "Dumpeo finalizado en "+filename 

main()