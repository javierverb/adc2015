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

int max(int a, int b) {
    int max = 0;
    if (a > b) {
        max = a;
    }
    else {
        max = b;
    }
    return max;
}

__kernel void temperature(__global double *T, __global double *T_prime,
                __global int N, __global int length_fonts_temperature,
                __global int length_iterations) {


    /* Get the work-item’s unique ID */
    int x = get_global_id(0);
    int y = get_global_id(1);

    int total_neighbors, index, 
    int SELF = 1;
    int sum_temperature = 0;
    int average = 0;

    /* Local array for neighbors */
    int array_neighbors[4];

    while (i < length_iterations) {
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
        average = (double)sum_temperature/total_neighbors+SELF;
        barrier(CLK_LOCAL_MEM_FENCE);

        int index_neighbor = 0;
        for (int i = 0; i < total_neighbors; ++i) {
            index_neighbor = array_neighbors[i];
            // asumimos que siempre nos quedamos con la temperatura más alta
            // INCOMPLETO: hay que swapear? no lo sé, puedo esperar...me tengo que ir a sistemas
            T_prime[index_neighbor] = max(average, T[index_neighbor]);
        }
        i++;
    }
}