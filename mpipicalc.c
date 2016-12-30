//Run using "mpicc mpipicalc.c"
//mpiexec -n 128 ./mpipicalc.out

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int comm_sz, my_rank, i, j;
    float x,y, tempSquare, piEst, piFinal;
    long long int hits, tosses, finalHits;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    if (my_rank == 0) {
        printf("How many tosses?\n");
        tosses = 0;
        scanf("%lld", &tosses);
    }
    MPI_Bcast(&tosses, 1, MPI_INT, 0, MPI_COMM_WORLD);
    hits=0;
    srand(time(NULL)+my_rank);
    for(i=0; i<tosses; i++){
        x=0;
        y=0;
        x =
                (rand()/(float)(RAND_MAX))*abs(-1-1)+-1;
        y =
                (rand()/(float)(RAND_MAX))*abs(-1-1)+-1;
        tempSquare = (x*x) + (y*y);
        if (tempSquare<=1){
            hits++;
        }
    }
    MPI_Reduce(&hits, &finalHits, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if (my_rank == 0) {
        piFinal =
                4*((finalHits/comm_sz)/((float)tosses));
        printf("PI is about: %f \n", (piFinal));
    }
    MPI_Finalize();
    return 0;
}
