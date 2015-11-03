#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "tools.h"


int x_from_i(int i, int N) {
    /* Dado el índice del arreglo i, me devuelve la coordenada
    x de una matriz N*N */
    return i/N;
}

int y_from_i(int i, N) {
    /* Dado el índice del arreglo i, me devuelve la coordenada
    y de una matriz N*N */
    return i%N;
}

int main(void) {
    
    cl_uint platformCount;
    cl_device_type device_type;
    cl_uint deviceCount, maxComputeUnits;
    cl_ulong clkFrequency, perform = 0, maxPerform = 0;
    cl_int status;
    cl_platform_id *platforms;
    cl_device_id *devices;

    input_data_t input_container = input_container_new();
    input_container = load_input("input.txt", input_container);

    int N = get_N(input_container);
    int length_fonts_temperature = get_length_fonts_temperature(input_container);
    triple_data_t a_xyt = get_array_from_input(input_container);


    double *T = NULL; // T
    double *T_prime = NULL; // finalmente será T = T'

    size_t datasize = sizeof(double) * (N*N);
    T = (double*) malloc (datasize);

    /* Inicio la matriz con ceros */
    for (int i = 0; i < N*N; ++i) {
        T[i] = 0;
    }

    /* Cargo la matriz con las temperaturas de input */
    int x, y = 0;
    double t = 0;
    for (int i = 0; i < length_fonts_temperature; ++i) {
        x = get_x_from_index(a_xyt, i);
        y = get_y_from_index(a_xyt, i);
        t = get_t_from_index(a_xyt, i);
        T[x*N +y] = t; // x*N+y = row*N+col = (x,y) de T
    }

    printf("\n\nMatriz T\n");
    for(int i = 0; i < N*N; ++i) {
        printf("%f ", T[i]);
        if(((i + 1) % N) == 0){
            printf("\n");
        }
    }

    /* Get platforms count */
    status = clGetPlatformIDs(1, NULL, &platformCount);

    /* Get platforms */
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);
    
    /* Get devices */
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
    devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);
    clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

    /* Calculating perfomance */
    for (j = 0; j < deviceCount; j++) {

        /* Max Compute Units */
        clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                sizeof(maxComputeUnits), &maxComputeUnits, NULL);

        /* Clock Frequency */
        clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, 
                sizeof(clkFrequency), &clkFrequency, NULL);

        /* Index of best perfomance device */
        perform = clkFrequency * maxComputeUnits;
        if (maxPerform < perform) {
            maxPerform = perform;
            performIndex = j;
        }
    }

    /* Use the device with the best performance */
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, performIndex, devices, NULL);

    /* Create the context */
    cl_context context = clCreateContext(NULL, deviceCount, devices,
                                             NULL, NULL, &status);

    /* Create a comand queue */
    cl_command_queue cmd_queue = clCreateCommandQueue(context, devices[0], 0, 
                                                        &status);

    
    /* Need a two buffer for read and write */
    cl_mem buffer_input_T, buffer_middle_T, buffer_output_T;
    buffer_T = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize,
       NULL, &status);
    
    buffer_T_prime = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize,
       NULL, &status);

    buffer_output_T = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize,
       NULL, &status);

    /* Send (write) data to kernel */
    status = clEnqueueWriteBuffer(cmd_queue, buffer_T, CL_TRUE,
        0, datasize, T, 0, NULL, NULL);

    status = clEnqueueWriteBuffer(cmd_queue, buffer_T_prime, CL_TRUE,
        0, datasize, T_prime, 0, NULL, NULL);


    const char* program_source = readSource("temperature.cl");
    cl_program program = clCreateProgramWithSource(context, 1,
    &program_source, NULL, &status);

    /* Build (compile) the program for the device */
    status = clBuildProgram(program, deviceCount, devices,
        NULL, NULL, NULL);

    /* Create a kernel from the given program */
    clCreateKernel(program, "temperature", &status);


    /*  */
    status = clSetKernelArg(kernel, 0, sizeof(int), &N);
    status = clSetKernelArg(kernel, 1, sizeof(int), &k);

    
    return EXIT_SUCCESS;
}