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


void construct_t_prime(int N, int my_pid, double *T, int length_rows) {
    
    int sum_temperature, total_neighbors = 0;
    int index, i, x, y = 0;
    int SELF = 1;

    /* Local array for neighbors */
    int array_neighbors[4];

    printf("my_pid%d\n", my_pid);

    while (i < N) {

        x = get_x_from_index(i, length_rows);
        y = get_y_from_index(i, length_rows);
        
        printf("x%d y%d\n", x, y);
        
        index = get_index_from_coordinate(x, y, N);
        
        if (T[index] > 0) {
            // calculate prom
            sum_temperature = T[index];
            if (x > 0) {
                index = get_index_from_coordinate(x-1, y, N);
                sum_temperature += T[index];
                array_neighbors[total_neighbors] = index;
                total_neighbors++;
            }
            if (x < N-1) {
                index = get_index_from_coordinate(x+1, y, N);
                sum_temperature += T[index];
                array_neighbors[total_neighbors] = index;
                total_neighbors++;
            }
            if (y > 0) {
                index = get_index_from_coordinate(x, y-1, N);
                sum_temperature += T[index];
                array_neighbors[total_neighbors] = index;
                total_neighbors++;
            }
            if (y < N-1) {
                index = get_index_from_coordinate(x, y+1, N);
                sum_temperature += T[index];
                array_neighbors[total_neighbors] = index;
                total_neighbors++;
            }
        }
        i++;
    }

    int average = (double)sum_temperature/total_neighbors+SELF;
    printf("average:%d\n", average);
    int index_neighbor;
    int rows_to_process = N;

    for (i = 0; i < total_neighbors; ++i) {
        index_neighbor = array_neighbors[i];
        if (my_pid * rows_to_process <= index_neighbor < 
            (my_pid+1) * rows_to_process) {
            T[index_neighbor] = average;
        }
    }
    i++;
}