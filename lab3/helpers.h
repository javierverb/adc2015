#ifndef HELPERS_H
#define HELPERS_H

#define _ROOT 0
#define DATA_LENGHT 3
#define INDEX_X 0
#define INDEX_Y 1
#define INDEX_T 2


void reset_sources(int my_pid, int comm_sz, int length_fonts_temperature, int N,
                    int fragment_size, double *a_xyt, double *partition_T);   

void print_matrix (double *partition_T, int num_rows, int num_cols);

void construct_t_prime(int N, int comm_sz, int my_pid,
                        double *T, double *bottom_row, double *top_row);

void ensamble_data(int my_pid, int N, int comm_sz, int fragment_size, double *partition_T);

#endif
