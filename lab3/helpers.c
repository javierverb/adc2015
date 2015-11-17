#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int get_total_rows_to_process(int N, int comm_sz) {
    return N/comm_sz;
}

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
}

void reset_sources(int length_fonts_temperature, int my_pid, int rows_to_process,
                   double *T, double *a_xyt, 
                   int comm_sz) {
    int i, x, y = 0;
    double t;
    while (i < length_fonts_temperature*DATA_LENGHT) {
        if (my_pid * rows_to_process <= a_xyt[i + INDEX_X] < 
            (my_pid+1) * rows_to_process) {
            x = a_xyt[i + INDEX_X];
            y = a_xyt[i + INDEX_Y];
            t = a_xyt[i + INDEX_T];
            T[x*i +y] = t;
        }
        i = i + DATA_LENGHT;
    }
}

void construct_t_prime(matrix, matrix_size, comm_sz, my_pid, top_row,
                      bottom_row);