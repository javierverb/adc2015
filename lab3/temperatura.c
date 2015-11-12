#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpi.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);




    MPI_Finalize();
return 0;
}
