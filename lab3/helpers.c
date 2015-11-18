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

void construct_t_prime(double *T, int N, int comm_sz, int my_pid, 
                        double *neightbour_top, double *neightbour_bot) {

    float accum = 0, *temp = NULL;
    int row = 0, col = 0, operands = 0, fragment_size = 0;

    /* Each process work over a fragment of the whole matrix,
     the matrix is partitioned on equally-sized portions */
    fragment_size = (N * N) / comm_sz;

    temp = (float *) calloc (fragment_size, sizeof (float));

    for (row = 0; row < N / comm_sz; row++) {
        for (col = 0; col < N; col++) {
            accum = T[row * N + col];
            operands = 1;
            if (row != 0) {
                accum += T[(row - 1) * N + col];
                operands++;
            }
            if (row != N / comm_sz - 1) {
                accum += T[(row + 1) * N + col];
                operands++;
            }
            if (col != 0) {
                accum += T[row * N + col - 1];
                operands++;
            }
            if (col != N - 1) {
                accum += T[row * N + col + 1];
                operands++;
            }
            if (row == 0 && my_pid != 0) {
                accum += neightbour_top[col];
                operands++;
            }
            if (row == N / comm_sz - 1 && my_pid != comm_sz - 1) {
                accum += neightbour_bot[col];
                operands++;
            }
            temp[row * N + col] = accum / operands;
        }
    }

    /* Replace old matrix values with the new ones */
    for (row = 0; row < N / comm_sz; row++) {
        for (col = 0; col < N; col++) {
            T[row * N + col] = temp[row * N + col];
        }
    }
  free (temp);
}