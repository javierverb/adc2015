#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"
#include "helpers.h"

int main(void) {

    int u __attribute__((unused)); // para ignorar la salida de los scanf
    int N, length_iterations, length_fonts_temperature;
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
        if (N % comm_sz != 0) {
            N += comm_sz - N % comm_sz;
        }
    }
    
    /* Arreglo de coordenadas x,y con su respectiva temperatura */
    double a_xyt[length_fonts_temperature*DATA_LENGHT];
    int i = 0;
    while (i < length_fonts_temperature) {
        u = scanf("%d %d %lf", &x, &y, &t);
        a_xyt[i + INDEX_X] = x;
        a_xyt[i + INDEX_Y] = y;
        a_xyt[i + INDEX_T] = t;
        i = i + DATA_LENGHT;
    }

    
    /* Comparto los datos con todos los procesos */
    MPI_Bcast(&N, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_iterations, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&length_fonts_temperature, 1, MPI_INT, _ROOT, MPI_COMM_WORLD);
    // puntos de calor
    MPI_Bcast(&a_xyt, length_fonts_temperature, MPI_INT, _ROOT, MPI_COMM_WORLD);

    double T[N][N];
    init_matrix(N, T);
    /* Creamos la matriz inicial */

    reset_sources(length_fonts_temperature, my_pid, N, T, 
              a_xyt, comm_sz);
    if (my_pid == 0) {
        print_matrix(N, T);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}