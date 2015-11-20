#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"
#include "helpers.h"

int main(void) {

    int u __attribute__((unused)); // para ignorar la salida de los scanf
    int N, length_iterations, length_fonts_temperature;
    int old_N;
    int x, y;
    double t;

    int comm_sz, my_pid;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_pid);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Sólamente _ROOT parsea los datos de entrada*/
    if (my_pid == _ROOT) {

        u = scanf("%d", &N);
        u = scanf("%d", &length_iterations);
        u = scanf("%d", &length_fonts_temperature);
        
        old_N = N; // hago una copia de N

        /* Relleno el tamaño de la matriz con tantas filas como procesos */
        if (N % comm_sz != 0) {
            N += comm_sz - N % comm_sz;
        }
    }
    
    /* Arreglo de coordenadas x,y con su respectiva temperatura */
    double a_xyt[length_fonts_temperature*DATA_LENGHT];

    if (my_pid == _ROOT) {
        int i = 0;
        while (i < length_fonts_temperature*DATA_LENGHT) {
            u = scanf("%d %d %lf", &x, &y, &t);
            a_xyt[i + INDEX_X] = x;
            a_xyt[i + INDEX_Y] = y;
            a_xyt[i + INDEX_T] = t;
            i = i + DATA_LENGHT;
            printf("T?%.2f\n", t);
        }
    }

    /* Comparto los datos con todos los procesos */
    MPI_Bcast(&N, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_iterations, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_fonts_temperature, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    // puntos de calor
    MPI_Bcast(&a_xyt, length_fonts_temperature*DATA_LENGHT, 
                MPI_INT|MPI_DOUBLE, _ROOT, MPI_COMM_WORLD);

    /* Cada proceso tiene su partición de la matriz */
    unsigned int partition_matrix_size = (N*N) / comm_sz;
    double *partition_T = calloc(partition_matrix_size, sizeof(double));
    
    /* A diferencia de cada partición de T, bottom y top rows tienen el 
    tamaño de UNA sola fila cada uno respectivamente */
    double *top_row = calloc(N, sizeof(double));
    double *bottom_row = calloc(N, sizeof(double));

    /* Cargamos las fuentes de calor */
    reset_sources(my_pid, length_fonts_temperature, N, comm_sz,
                        a_xyt, partition_T,
                        bottom_row, top_row);

    distribute_data(my_pid, partition_T, partition_matrix_size, comm_sz);
    /* Todos los procesos deben haber finalizado su inicialización */
    MPI_Barrier(MPI_COMM_WORLD);

    if (my_pid == _ROOT) {
        print_matrix(N, partition_T);
    }
    

    /* Comienza el procesamiento de las fuentes de calor */
    int j = 0;
    while (j < length_iterations) {
        share_limit_rows(my_pid, partition_matrix_size, comm_sz, N,
                        partition_T, top_row, bottom_row);
        construct_t_prime(N, comm_sz, my_pid, partition_T, bottom_row, top_row);
        reset_sources(my_pid, length_fonts_temperature, N, comm_sz, 
                        a_xyt, partition_T, bottom_row, top_row);
        j++;
    }

    distribute_data(my_pid, partition_T, partition_matrix_size, comm_sz);
    MPI_Barrier(MPI_COMM_WORLD);

    if (my_pid == _ROOT) {
        print_matrix(N, partition_T);
    }  


    MPI_Finalize();
    /* Libero los recursos alocados */
    free(partition_T);
    free(top_row);
    free(bottom_row);

    return EXIT_SUCCESS;
}