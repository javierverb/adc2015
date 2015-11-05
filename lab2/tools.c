#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"


struct tripleValues {
    int x;
    int y;
    double t;
};

struct neighbors {
    int total_neighbors;
    triple_data_t a_xyt;  
};

struct inputData {
    char type_operation;
    int N;
    int length_iterations;
    int length_fonts_temperature;
    triple_data_t a_xyt;
};

/* Getters */
char get_type_operation(input_data_t input) {
    return input->type_operation;
}

int get_N(input_data_t input) {
    return input->N;
}

int get_length_iterations(input_data_t input) {
    return input->length_iterations;
}

int get_length_fonts_temperature(input_data_t input) {
    return input->length_fonts_temperature;
}

triple_data_t get_array_from_input(input_data_t input) {
    return input->a_xyt;
}

triple_data_t get_array_from_neighbors(neighbors_t n) {
    return n->a_xyt;
}

int get_x_from_index(triple_data_t a_xyt, int i) {
    return a_xyt[i].x;
}

int get_y_from_index(triple_data_t a_xyt, int i) {
    return a_xyt[i].y;
}

double get_t_from_index(triple_data_t a_xyt, int i) {
    return a_xyt[i].t;
}

int get_total_neighbors(neighbors_t n) {
    return n->total_neighbors;
}

triple_data_t triple_data_new(int N) {
    triple_data_t a_xyt = new tripleValues[N];
    return a_xyt;
}

input_data_t input_container_new() {
    input_data_t container_data =  new inputData(); //calloc(1, sizeof(struct inputData));
    return container_data;
}

void triple_data_add(triple_data_t a_xyt, int i, int x, int y, double t) {
    a_xyt[i].x = x;
    a_xyt[i].y = y;
    a_xyt[i].t = t;
}

void input_container_destroy(input_data_t container_data) {
    free(container_data);
    container_data = NULL;
}

void dump_all_values(input_data_t input) {
    
    int x,y;
    double t;

    printf("%c\n", input->type_operation);
    printf("%d\n", input->N);
    printf("%d\n", input->length_iterations);
    printf("%d\n", input->length_fonts_temperature);
    for (int i = 0; i < input->length_fonts_temperature; ++i) {
        x = input->a_xyt[i].x;
        y = input->a_xyt[i].y;
        t = input->a_xyt[i].t;
        printf("%d %d %f\n", x,y,t);
    }
}

void dump_all_neighbors(neighbors_t n) {
    for (int i = 0; i < n->total_neighbors; ++i) {
        printf("%d ", n->a_xyt[i].x);
        printf("%d\n", n->a_xyt[i].y);
    }
}

input_data_t load_input(char* path, input_data_t container_data) {
    
    size_t len = 0;
    FILE *input_to_load;
    printf("Abriendo %s...\n", path);

    input_to_load = fopen(path, "r");
    
    if (!input_to_load) {
        printf("Error al abrir el archivo. "
                "Asegúrece de que el archivo exista o el path sea correcto.\n");
        exit(EXIT_FAILURE);
    }

    // leo las primeras 4 líneas
    char *line_to_read = NULL;
    getline(&line_to_read, &len, input_to_load);
    container_data->type_operation = (char)*line_to_read;
    line_to_read = NULL;
    
    getline(&line_to_read, &len, input_to_load);
    container_data->N = atoi(line_to_read);
    line_to_read = NULL;

    getline(&line_to_read, &len, input_to_load);
    container_data->length_iterations = atoi(line_to_read);
    line_to_read = NULL;

    getline(&line_to_read, &len, input_to_load);
    container_data->length_fonts_temperature = atoi(line_to_read);
    line_to_read = NULL;

    // en base al 'N' de la matriz, generamos un arreglo de N de triplas
    triple_data_t a_xyt = triple_data_new(container_data->length_fonts_temperature);

    int i, x, y = 0;
    double t = 0.0;
    int is_redeable = 0;
    const char delim[2] = " ";
    char *value;

    // leo desde la 4 línea en adelante y parseo sus tres valores por línea
    while (feof(input_to_load) == 0) {
        getline(&line_to_read, &len, input_to_load);
        if (is_redeable != -1) {
            sscanf(line_to_read, "%d %d %lf", &x, &y, &t);
            triple_data_add(a_xyt, i, x, y, t);
        }
        i++;
        line_to_read = NULL;
    }
    // finalmente enlazo mi subestructura a la estructura principal
    container_data->a_xyt = a_xyt;
    return container_data;
}


// Para obtener los vecinos de la matriz:
neighbors_t neighbors_new(void) {
    neighbors_t n = new neighbors();
    return n;
}

neighbors_t get_neighbors(int x, int y, int N, neighbors_t n) {
    // dado que pueden pasar varias condiciones a la vez, es por el cual
    // utilizo 4 ifs en vez de un switch case que sólo considera un caso.
    int MAX_NEIGHBORS = 4;
    triple_data_t a_xyt = triple_data_new(MAX_NEIGHBORS);
    int i = 0;

    if (x > 0) {
        a_xyt[i].x = x-1;
        a_xyt[i].y = y;
        i++;
    }
    if (x < N-1) {
        a_xyt[i].x = x+1;
        a_xyt[i].y = y;
        i++;
    }
    if (y > 0) {
        a_xyt[i].x = x;
        a_xyt[i].y = y-1;
        i++;
    }
    if (y < N-1) {
        a_xyt[i].x = x;
        a_xyt[i].y = y+1;
        i++;
    }
    n->total_neighbors = i;
    n->a_xyt = a_xyt;
    return n;
}