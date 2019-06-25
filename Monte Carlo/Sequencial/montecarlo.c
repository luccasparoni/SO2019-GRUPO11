#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_ITERATIONS 100000
#define NUM_INSTANCES 1000


double monteCarlo_seq_instance(){

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

    return insideCount;
}

double monteCarlo_sequential(){
    int sequentialCount = 0;
    for(int i = 0; i < NUM_INSTANCES; i++)
        sequentialCount += monteCarlo_seq_instance();

    double pi = 4 * (sequentialCount / (double) (NUM_INSTANCES * NUM_ITERATIONS));
    return pi;
}


int main(){

    printf("%.7f\n", monteCarlo_sequential());

}
