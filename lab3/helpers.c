#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "helpers.h"
#include "mpi.h"


void print_matrix (double *partition_T, int num_rows, int num_cols) {
    int i = 0, j = 0;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            printf ("%.2f ", partition_T[i *num_cols + j]);
        }
        printf ("\n");
    }
}

void ensamble_data(int my_pid, int N, int comm_sz, int fragment_size, double *partition_T) {
    int j;
    /* Si soy el proceso raíz me encargo de recibir cada parte de matriz de mis 
    hijos */
    if (my_pid == _ROOT) {
        print_matrix (partition_T, N/comm_sz, N);
        /* Recibo cada partición y la voy imprimiendo de manera ordenada */
        for (j = 1; j < comm_sz; j++) {
            MPI_Recv(partition_T, fragment_size, MPI_DOUBLE, j, 0, MPI_COMM_WORLD,
                        MPI_STATUS_IGNORE);
            print_matrix(partition_T, N/comm_sz, N);
        }
    } else {
        /* Le envío mi fragmento a la raíz */
        MPI_Send (partition_T, fragment_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
}


void reset_sources(int my_pid, int comm_sz, int length_fonts_temperature, int N,
                    int fragment_size, double *a_xyt, double *partition_T) {


    int x, y; 
    double t; 
    int i, index_xy = 0;

    while (i < length_fonts_temperature*DATA_LENGHT) {
        
        x = a_xyt[i+INDEX_X];
        y = a_xyt[i+INDEX_Y];
        t = a_xyt[i+INDEX_T];

        if (my_pid*N/comm_sz <= x < (my_pid+1)*N/comm_sz) {
            index_xy = x*N + y - my_pid * fragment_size;
            partition_T[index_xy] = t;
        }
        i = i+DATA_LENGHT;
    }
}

void construct_t_prime(int N, int comm_sz, int my_pid,
                        double *T, double *bottom_row, double *top_row) {

    double average = 0;
    double sum_temperature = 0; 

    double *temp = calloc((N*N)/comm_sz, sizeof(double));
    
    int total_neighbors = 0; 
    int SELF = 1;
    int x, y;
    int rows_to_process = 0;

    for (x = 0; x < N/comm_sz; x++) {
        for (y = 0; y < N; y++) {

            total_neighbors = SELF;
            sum_temperature = T[x*N+y];
            
            if (x > 0) {
                sum_temperature += T[(x-1)*N+y];
                total_neighbors++;
            }
            if (x < (N/comm_sz)-1) {
                sum_temperature += T[(x+1)*N+y];
                total_neighbors++;
            }
            if (y > 0) {
                sum_temperature += T[x*N+y-1];
                total_neighbors++;
            }
            if (y < N-1) {
                sum_temperature += T[x*N+y+1];
                total_neighbors++;
            }
            if (x == 0 && my_pid != 0) {
                sum_temperature += top_row[y];
                total_neighbors++;
            }
            if (x == (N/comm_sz-1) && my_pid != comm_sz - 1) {
                sum_temperature += bottom_row[y];
                total_neighbors++;
            }

            average = sum_temperature/total_neighbors;
            temp[x*N+y] = average;
        }
    }
    /* Reemplazo la partición de matriz con la nueva */
    for (x = 0; x < N / comm_sz; x++) {
        for (y = 0; y < N; y++) {
            T[x * N + y] = temp[x * N + y];
        }
    }
    free (temp);
}