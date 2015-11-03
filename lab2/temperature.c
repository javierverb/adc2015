#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom includes
#include "helpers.h"
#include "tools.h"

// OpenCL includes
#include <CL/cl.h>

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
    int length_iterations = get_length_iterations(input_container);

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
    cl_mem buffer_T, buffer_middle_T, buffer_T_prime;
    buffer_T = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize,
       NULL, &status);
    
    buffer_middle_T = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize,
       NULL, &status);

    buffer_T_prime = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize,
       NULL, &status);

    /* Send (write) data to kernel */
    status = clEnqueueWriteBuffer(cmd_queue, buffer_T, CL_TRUE,
        0, datasize, T, 0, NULL, NULL);

    // realmente necesitamos T_prime?

    /* A matrix output with name 'T_prime' */
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


    /* Kernel args */
    status = clSetKernelArg(kernel, 0, sizeof(int), &N);
    status = clSetKernelArg(kernel, 1, sizeof(int), &length_fonts_temperature);
    status = clSetKernelArg(kernel, 2, sizeof(int), &length_iterations);
    status = clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer_T);
    status = clSetKernelArg(kernel, 4, sizeof(cl_mem), &buffer_T_prime);
    // status = clSetKernelArg(kernel, 5, sizeof(cl_mem), &buffer_middle_T);
    
    /* Define an index space (global work size) of work item for execution
    A work group size (local work group size) is not required, but can be used */

    size_t globalWorkSize[2];
    globalWorkSize[0] = N;
    globalWorkSize[1] = N;

    /* Execute the kernel for execution */
    status = clEnqueueNDRangeKernel(cmd_queue, kernel, 2, NULL,
        globalWorkSize, NULL, 0, NULL, NULL);

    // Read the device output buffer to the host output matrix
    clEnqueueReadBuffer(cmd_queue, buffer_T_prime, CL_TRUE, 0,
        datasize, T_prime, 0, NULL, NULL);

    printf("\n\nMatriz T'\n");
    for(int i = 0; i < N*N; ++i) {
        printf("%.2f ", T_prime[i]);
        if(((i + 1) % N) == 0){
            printf("\n");
        }
    }

    /* Free OpenCl resources */
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(cmd_queue);
    clReleaseMemObject(buffer_T);
    // clReleaseMemObject(buffer_middle_T); dude..
    clReleaseMemObject(buffer_T_prime);
    clReleaseContext(context);

    /* Free host resources */
    free(T);
    free(T_prime);
    free(platforms);
    free(devices);
    
    return EXIT_SUCCESS;
}