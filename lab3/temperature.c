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

        /* Relleno el tamaño de la matriz con tantas filas como procesos */
        old_N = N;
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
        }
    }
    int rows_to_process = N*N/comm_sz;

    /* Comparto los datos con todos los procesos */
    MPI_Bcast(&N, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_iterations, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_fonts_temperature, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    // puntos de calor
    MPI_Bcast(&a_xyt, length_fonts_temperature, MPI_INT, _ROOT, MPI_COMM_WORLD);


    /* Cada proceso tiene su partición de la matriz */
    unsigned int partition_matrix_size = (N*N) / comm_sz;
    double *T = calloc(partition_matrix_size, sizeof (double));
    
    /* Espacio para mis filas vecinas */
    double *neightbour_top = calloc(partition_matrix_size, sizeof(double));
    double *neightbour_bot = calloc(partition_matrix_size, sizeof(double));

    /* Creamos la matriz inicial */
    reset_sources(length_fonts_temperature, my_pid, partition_matrix_size, T, 
              a_xyt, comm_sz);
    
    /* Todos los procesos deben haber finalizado su inicialización */
    MPI_Barrier(MPI_COMM_WORLD);

// ------>
    /* Comienza el procesamiento de las fuentes de calor */
    int j = 0;
    while (j < length_iterations) {
        
        /* Si no soy la primera fila o estoy siendo procesado por el primer proceso
        puedo recibir datos desde la fila de arriba */
        if (my_pid != _ROOT) {
            MPI_Send(T, N, MPI_DOUBLE, my_pid - 1, _ROOT, MPI_COMM_WORLD);
            MPI_Recv (neightbour_top, N, MPI_DOUBLE, my_pid - 1, 0,
                        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        /* Process comm_sz - 1 don't receive a row from a process "below", neither
        it should send its last row */
        if (my_pid != comm_sz - 1) {
            MPI_Send(T, N, MPI_DOUBLE, my_pid + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(neightbour_bot, N, MPI_DOUBLE, my_pid + 1, 0,
                      MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        /* Recursive formula applied to modify the matrix */
        construct_t_prime(T, N, comm_sz, my_pid, neightbour_top,
                            neightbour_bot);

        /* Every time the matrix is transformed, all heat sources should
           keep its temperature */
        reset_sources(length_fonts_temperature, my_pid, 
                      rows_to_process, T, a_xyt, comm_sz);
        j++;
    }

    /* Process 0 is in charge of printing the whole matrix to STDOUT,
     thus it should print its fragment of the matrix, and all other
     processes should send its fragment to process 0 */
    if (my_pid == _ROOT) {
        /* Receive fragments from other processes & print */
        for (j = 1; j < comm_sz; j++) {
            MPI_Recv(T, partition_matrix_size, MPI_DOUBLE, j, 
                     _ROOT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        print_matrix(old_N, T);
    } else {
        /* Send fragment to process 0*/
        MPI_Send(T, partition_matrix_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    /* En este punto todos los procesos terminaron de procesar sus fragmentos */
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
    /* Libero los recursos alocados */
    free(T);
    free(neightbour_top);
    free(neightbour_bot);

    return EXIT_SUCCESS;
}