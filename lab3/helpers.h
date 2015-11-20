#ifndef HELPERS_H
#define HELPERS_H

#define _ROOT 0
#define DATA_LENGHT 3
#define INDEX_X 0
#define INDEX_Y 1
#define INDEX_T 2

void reset_sources(int my_pid, int k, int N, int comm_sz,
                    double *a_xyt, double *fragment_T,
                    double *bottom_row, double *top_row);

void construct_t_prime(int N, int comm_sz, int my_pid,
                        double *T, double *bottom_row, double *top_row);

void distribute_data(int my_pid, double *T, int partition_matrix_size, int comm_sz);

void share_limit_rows(int my_pid, int partition_matrix_size, int comm_sz, int N,
                        double *T, double *top_row, double *bottom_row);


void swap_limit_rows(double *T, double *T_prime, int my_pid, int N, int comm_sz);
int get_index_from_coordinate(int x, int y, int N);
void print_matrix(int N, double *T);

#endif
