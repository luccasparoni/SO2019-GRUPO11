#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NUM_THREADS 4
#define NUM_ITERATIONS 1000

double gauss_legendre_sequential(){


	double a[NUM_ITERATIONS];
	double b[NUM_ITERATIONS];
	double t[NUM_ITERATIONS];
	double p[NUM_ITERATIONS];

	a[0] = 1.00;
	b[0] = 1.00 / (sqrt(2));
	t[0] = 1.00 / 4.00;
	p[0] = 1.00;


	int i;
	for(i = 1; i < NUM_ITERATIONS; i++){
		a[i] = (a[i-1] + b[i-1]) / 2.00;
		b[i] = sqrt(a[i-1] * b[i-1]);
		t[i] = t[i-1] - p[i-1] * pow(a[i-1] - a[i] , 2);
		p[i] = 2.00 * p[i-1];
	}

	double pi =  pow(a[i-1] + b[i-1] , 2) / (4.0 * t[i-1]);

	return pi;
}



int main(){
	printf("pi = %.10f\n", gauss_legendre_sequential());

	return 0;
}
