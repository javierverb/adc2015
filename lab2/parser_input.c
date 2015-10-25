#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser_input.h"

struct tripleValues {
    int x;
    int y;
    float t;
};

struct inputData {
    char type_operation;
    int N;
    int length_iterations;
    int length_fonts_temperature;
    triple_data_t a_xyt;
};

triple_data_t triple_data_new(int N) {
    triple_data_t a_xyt = calloc(N, sizeof(struct tripleValues));
    return a_xyt;
}

input_data_t input_container_new() {
    input_data_t container_data = calloc(1, sizeof(struct inputData));
    return container_data;
}

void triple_data_add(triple_data_t a_xyt, int i, int x, int y, float t) {
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
    float t;

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
    float t = 0.0;
    int is_redeable = 0;
    const char delim[2] = " ";
    char *value;

    // leo desde la 4 línea en adelante y parseo sus tres valores por línea
    while (feof(input_to_load) == 0) {
        getline(&line_to_read, &len, input_to_load);
        if (is_redeable != -1) {
            sscanf(line_to_read, "%d %d %f", &x, &y, &t);
            triple_data_add(a_xyt, i, x, y, t);
        }
        i++;
        line_to_read = NULL;
    }
    // finalmente enlazo mi subestructura a la estructura principal
    container_data->a_xyt = a_xyt;
    return container_data;
}

int main(void) {
    
    input_data_t input = NULL;
    input = input_container_new();
    input = load_input("modee_N77_k56_j98.txt", input);
    dump_all_values(input);
    input_container_destroy(input);

    return EXIT_SUCCESS;
}