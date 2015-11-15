#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int get_total_rows_to_process(int N, int comm_sz) {
    return N/comm_sz;
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
    printf("my_pid: %d\n", my_pid);
    while (i < length_fonts_temperature) {
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
