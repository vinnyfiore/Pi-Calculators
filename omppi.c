////Run using gcc -fopenmp omppi.c
////./omppi.out

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    long long int tosses, finalHits;
    int thread_count = 4;
    float piFinal;

    printf("How many tosses?\n");
    tosses = 0;
    scanf("%lld", &tosses);

    srand(time(NULL));


#pragma omp parallel num_threads(thread_count)
    {
    finalHits=0;
    int i;
    float x, y, tempSquare;
    long long int hits;
    hits = 0;

        for (i = 0; i < tosses; i++) {
            x = 0;
            y = 0;
            x = (rand() / (float) (RAND_MAX)) * abs(-1 - 1) + -1;
            y = (rand() / (float) (RAND_MAX)) * abs(-1 - 1) + -1;

            tempSquare = (x * x) + (y * y);

            if (tempSquare <= 1) {
                #pragma omp critical
                    hits++;
            }


        }

#pragma omp parallel reduction(+: finalHits)
        finalHits += hits;
    }


    piFinal = 4*((finalHits/thread_count)/((float)tosses));
    printf("PI is about: %f  \n", (piFinal));


    return 0;
}
