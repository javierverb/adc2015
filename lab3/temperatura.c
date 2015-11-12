#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpi.h"

int main(int argc, char** argv) {

    int comm_size, rank, n, k, j, data_array[];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //leemos los datos n, k, j por entrada standar y los guada en data_array
    input_data(data_array, rank, n, k, j);
    //leemos los datos x, y, t por entrada standar y los guarda en data_temp
    input_data_temp(data_temp, rank, x, y, t);


    //ajustamos el tamaño maximo de la matriz para que sea multiplo de comm_size <----------------------------------------ver!!!
    //.... hacer ese paso, pensarlo!!!


    //mandamos desde el proceso padre, a los procesos hijos
    MPI_Bcast(data_array[0], 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(data_array[1], 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(data_array[2], 1, MPI_INT, 0, MPI_COMM_WORLD);
    //enviamos los datos de la temperatura desde el ROOT a todos los procesos
    MPI_Bcast(data_temp, j, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    //CONTINUARAAAA..........!!!! fap fap 

    MPI_Finalize();
return 0;
}
