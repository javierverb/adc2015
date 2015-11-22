#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>
#include "helpers.h"

int main(void) {

    int u __attribute__((unused)); // para ignorar la salida de los scanf
    int N, length_iterations, length_fonts_temperature;
    int x, y;
    double t;
    int fragment_size;
    int rows_for_process;
    int comm_sz, my_pid;
    
    double *partition_T, *top_row, *bottom_row;
    double *a_xyt;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_pid);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Sólamente _ROOT parsea los datos de entrada*/
    if (my_pid == _ROOT) {

        u = scanf("%d", &N);
        u = scanf("%d", &length_iterations);
        u = scanf("%d", &length_fonts_temperature);
        
        /* Relleno el tamaño de la matriz con tantas filas como procesos */
        if (N % comm_sz != 0) {
            N += comm_sz - N % comm_sz;
        }
    }

    /* Comparto los datos con todos los procesos */
    MPI_Bcast(&N, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_iterations, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_fonts_temperature, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    
    /* Arreglo de coordenadas x,y con su respectiva temperatura */
    a_xyt = calloc(length_fonts_temperature*DATA_LENGHT, sizeof(double));

    fragment_size = (N*N)/comm_sz;

    if (my_pid == _ROOT) {
        int i = 0;
        while (i < length_fonts_temperature*DATA_LENGHT) {
            u = scanf("%d %d %lf", &x, &y, &t);
            a_xyt[i + INDEX_X] = x;
            a_xyt[i + INDEX_Y] = y;
            a_xyt[i + INDEX_T] = t;
            i = i + DATA_LENGHT;
        }
    }
    // puntos de calor
    MPI_Bcast(a_xyt, length_fonts_temperature*DATA_LENGHT, 
                MPI_INT|MPI_DOUBLE, _ROOT, MPI_COMM_WORLD);

    partition_T = calloc(fragment_size, sizeof(double));

    /* A diferencia de cada partición de T, bottom y top rows tienen el 
    tamaño de UNA sola fila cada uno respectivamente */
    top_row = calloc(N, sizeof(double));
    bottom_row = calloc(N, sizeof(double));

    /* Initialize matrices with heat sources */
    reset_sources(my_pid, comm_sz, length_fonts_temperature, N,
                 fragment_size, a_xyt, partition_T); 


    /* Comienza el procesamiento de las fuentes de calor */
    int j = 0;
        while (j < length_iterations) {

        /* Intercambiar filas: 
        Si no soy ROOT significa que tengo filas arriba por recibir */
        if (my_pid != _ROOT) {
            MPI_Send(partition_T, N, MPI_DOUBLE, my_pid-1, 0,
                            MPI_COMM_WORLD);
            MPI_Recv(top_row, N, MPI_DOUBLE, my_pid-1, 0,
                            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        /* Si no soy el último proceso, 
        significa que tengo filas debajo por recibir */
        if (my_pid < comm_sz - 1) {
            MPI_Send(partition_T + (N/comm_sz-1)*N, N, MPI_DOUBLE, my_pid+1, 0, 
                            MPI_COMM_WORLD);
            MPI_Recv(bottom_row, N, MPI_DOUBLE, my_pid+1, 0,
                            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        /* Calculo el promedio de cada fragmento de T sin importar 
        las fuentes de calor */
        construct_t_prime(N, comm_sz, my_pid, partition_T, bottom_row, top_row);
        /* Reseteo las fuentes de calor */
        reset_sources(my_pid, comm_sz, length_fonts_temperature, N, 
                        fragment_size, a_xyt, partition_T);  
        j++;
    }

    /* Unifico cada partición de T y la imprimo */
    ensamble_data(my_pid, N, comm_sz, fragment_size, partition_T);

    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Finalize();

    /* Libero los recursos alocados */
    free(partition_T);
    free(top_row);
    free(bottom_row);

    return EXIT_SUCCESS;
}