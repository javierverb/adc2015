#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int get_total_rows_to_process(int N, int comm_sz) {
    return N/comm_sz;
}

void init_matrix(int N, double T[][N]) {
    int i, j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            T[i][j] = 0;
        }
    }
}

void print_matrix(int N, double T[][N]) {
    int i, j;
    for (i = 0; i < N; ++i) {
        printf("\n");
        for (j = 0; j < N; ++j) {
            printf("%.2f", T[i][j]);
        }
    }
    printf("\n");
}

void reset_sources(int length_fonts_temperature, int my_pid, int N,
                   double T[][N], double *a_xyt, 
                   int comm_sz) {
    int i, x, y = 0;
    double t;
    printf("my_pid: %d\n", my_pid);
    int rows_to_process = get_total_rows_to_process(N, comm_sz);
    while (i < length_fonts_temperature) {
        if (my_pid * rows_to_process <= a_xyt[i + INDEX_X] < 
            (my_pid+1) * rows_to_process) {
            x = a_xyt[i + INDEX_X];
            y = a_xyt[i + INDEX_Y];
            t = a_xyt[i + INDEX_T];
            T[x][y] = t;
        }
        i = i + DATA_LENGHT;
    }
}