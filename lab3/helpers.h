#ifndef HELPERS_H
#define HELPERS_H

#define _ROOT 0
#define DATA_LENGHT 3
#define INDEX_X 0
#define INDEX_Y 1
#define INDEX_T 2

void reset_sources(int length_fonts_temperature, int my_pid, int N,
                   double *T, double *a_xyt, 
                   int comm_sz);

void construct_t_prime(int N, int my_pid, double *T, int length_rows);
int get_index_from_coordinate(int x, int y, int N);


#endif
