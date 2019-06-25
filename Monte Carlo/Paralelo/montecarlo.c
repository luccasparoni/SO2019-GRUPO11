#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NUM_ITERATIONS 100000
#define NUM_INSTANCES 1000


int parallelCount = 0;


void *monteCarlo_par_instance(void *threadid){

    long id = (long) threadid;


    srand(time(NULL));

    double x[NUM_ITERATIONS];
    double y[NUM_ITERATIONS];
    double d[NUM_ITERATIONS];

    int insideCount = 0;

    for(int i = 0; i < NUM_ITERATIONS; i++){
        x[i] = ((rand()%200) - 100)/100.00;
        y[i] = ((rand()%200) - 100)/100.00;

        d[i] = sqrt(pow(x[i], 2) + pow(y[i], 2));

        if(d[i] <= 1.00)
            insideCount++;
    }

    parallelCount += insideCount;

}

double monteCarlo_parallel(){
    pthread_t thread[NUM_INSTANCES];

    for(long i = 0; i < NUM_INSTANCES; i++){
        pthread_create(&thread[i], NULL, monteCarlo_par_instance, (void *) i);
    }

    for(int i = 0; i < NUM_INSTANCES; i++){
        pthread_join(thread[i], NULL);
    }


    double pi = 4.00 * (((double) parallelCount) / ((double) (NUM_ITERATIONS * NUM_INSTANCES)));

    return pi;

}

int main(){

    printf("%.7f\n", monteCarlo_parallel());

}
