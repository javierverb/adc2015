#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "helpers.h"
#include "mpi.h"


int get_index_from_coordinate(int x, int y, int N) {
    /* Convert pair x,y to index for some array */
    return (x*N+y);
}

int get_x_from_index(int i, int N) {
    /* Dado el índice del arreglo i, me devuelve la coordenada
    x de una matriz N*N */
    return i/N;
}

int get_y_from_index(int i, int N) {
    /* Dado el índice del arreglo i, me devuelve la coordenada
    y de una matriz N*N */
    return i%N;
}

void print_matrix(int N, double *T) {
    int i;
    for (i = 0; i < N*N; ++i) {
        if (i % N == 0) {
            printf("\n");
        }
        printf("%.2f ", T[i]);
    }
    printf("\n");
}


void share_limit_rows(int my_pid, int partition_matrix_size, int comm_sz, int N,
                        double *T, double *top_row, double *bottom_row) {

    /* Si no soy la raíz, tengo filas por arriba */
    if (my_pid != _ROOT) {
        MPI_Send(T, partition_matrix_size, MPI_DOUBLE, 
                my_pid-1, 0, MPI_COMM_WORLD);

        // recibo la fila superior de mi vecino de abajo
        MPI_Recv(top_row, N, MPI_DOUBLE, 
                    my_pid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    /* Si no soy el último proceso, tengo filas por debajo */
    if (my_pid != comm_sz - 1) {
        MPI_Send(bottom_row, N, MPI_DOUBLE, 
                    my_pid + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(T, partition_matrix_size, MPI_DOUBLE, my_pid+1, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

void distribute_data(int my_pid, double *T, int partition_matrix_size, int comm_sz) {
    if (my_pid == _ROOT) {
        int child_id;
        /* Recibo fragmentos de otros procesos */
        for (child_id = 1; child_id < comm_sz; child_id++) {
            MPI_Recv(T, partition_matrix_size, MPI_DOUBLE, 
                        child_id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } 
    else {
        /* Envío a la raíz */
        MPI_Send(T, partition_matrix_size, MPI_DOUBLE, _ROOT, 0, MPI_COMM_WORLD);
    }
}

void reset_sources(int my_pid, int k, int N, int comm_sz,
                    double *a_xyt, double *partition_T,
                    double *bottom_row, double *top_row) {

    int x, y; 
    double t; 
    int i, index_xy = 0;
    int total_cells_in_T = (N*N)/comm_sz;

    while (i < k*DATA_LENGHT) {
        
        x = a_xyt[i+INDEX_X];
        y = a_xyt[i+INDEX_Y];
        t = a_xyt[i+INDEX_T];
        index_xy = get_index_from_coordinate(x, y, N);

        if (my_pid*total_cells_in_T <= x < (my_pid+1)*total_cells_in_T) {
            partition_T[index_xy] = t;
        }
        i = i+DATA_LENGHT;
    }
}

void construct_t_prime(int N, int comm_sz, int my_pid,
                        double *T, double *bottom_row, double *top_row) {

    double average = 0;
    double sum_temperature = 0; 
    int total_neighbors = 0; 
    int SELF = 1;
    int x, y, index_xy = 0; 
    int rows_to_process = 0;

    for (x = 0; x < N/comm_sz; x++) {
        for (y = 0; y < N; y++) {

            index_xy = get_index_from_coordinate(x, y, N);
            
            total_neighbors = SELF;
            sum_temperature = T[index_xy];
            
            if (x > 0) {
                index_xy = get_index_from_coordinate(x-1, y, N);
                sum_temperature += T[index_xy];
                total_neighbors++;
            }
            if (x < (N/comm_sz)-1) {
                index_xy = get_index_from_coordinate(x+1, y, N);
                sum_temperature += T[index_xy];
                total_neighbors++;
            }
            if (y > 0) {
                index_xy = get_index_from_coordinate(x, y-1, N);
                sum_temperature += T[index_xy];
                total_neighbors++;
            }
            if (y < N-1) {
                index_xy = get_index_from_coordinate(x, y+1, N);
                sum_temperature += T[index_xy];
                total_neighbors++;
            }
            // significa que tengo fila siguiente
            if (x == 0 && my_pid != _ROOT) {
                sum_temperature += top_row[y];
                total_neighbors++;
            }
            // si soy la última fila pero no estoy en el final de la matriz,
            // entonces tengo vecinos
            if (x == (N/comm_sz)-1 && my_pid != comm_sz-1) {
                sum_temperature += bottom_row[y];
                total_neighbors++;
            }

            average = sum_temperature/total_neighbors;
            T[index_xy] = average;
        }
    }
}