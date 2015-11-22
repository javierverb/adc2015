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
    
    T_prime[x*N+y] = T;
}