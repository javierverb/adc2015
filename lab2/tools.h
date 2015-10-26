#ifndef _TOOLS_
#define _TOOLS_


typedef struct tripleValues *triple_data_t;
typedef struct inputData *input_data_t;
typedef struct neighbors *neighbors_t;

/*
Crea un arreglo de estructuras nuevo. 
El espacio reservado debe ser liberado por el programador.
*/
triple_data_t triple_data_new();


/*
Crea un nuevo contenedor.
El espacio reservado debe ser liberado por el programador.
*/
input_data_t input_container_new();


/*
Dada una posición i del arreglo y sus tres valores, 
los añade en la estructura
*/
void triple_data_add(triple_data_t a_xyt, int i, int x, int y, float t);

/* 
Para debuggin, esta función imprime TODOS los valores
cargados en la estrucutra de tipo input_data_t 
*/
void dump_all_values(input_data_t input);


/*
Carga a la estructura de tipo input_data_t todos los 
datos provistos en el archivo con el formato correspondiente
(ver consigna).
Es deber del programador liberar los recursos.
*/
input_data_t load_input(char* path, input_data_t container_data);


/* Crea un nuevo contenedor de vecinos de tipo triple_data_t */
neighbors_t neighbors_new(void);

/*
Dadas las posiciones 'x', 'y' y N como tamaño de una matriz, calcula
todos los vecinos adyacentes a estas posiciones.
*/
neighbors_t get_neighbors(int x, int y, int N, neighbors_t n);

/*
Para debuggin, esta función imprime TODOS los vecinos de las coordenadas x,y
dentro de la estructura de tipo neighbors_t.
*/
void dump_all_neighbors(neighbors_t n);

#endif