#include <stdio.h>
#include <mpi.h>

static void input_data(int data_array[], int *rank, int *n, int *k, int *j){
    if(rank==0){
        scanf("ingrese el tamaño de la matriz\n",n);
        scanf("ingrese la cantidad de iteraciones\n",k);
        scanf("ingrese la cantidad de puntos de calor\n",j);
        data_array[0]=n;
        data_array[1]=k;
        data_array[2]=j;
    }
}

static void input_data_temp(int data_temp, int *rank, float *x, float *y, float *t){
    if(rank==0){
        printf("ingrese los valores x y t");
        int i=0;
        while(scanf("%f %f %f",&x,&y,&t)!=EOF){
            data_temp[i*3]=x;
            data_temp[(i+1)*3]=y;
            data_temp[(i+2)*3]=t;
        }
    }
}
