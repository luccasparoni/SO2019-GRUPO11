#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


double max(double num1, double num2){
	if(num1 > num2) return num1;
	else return num2;
}

double* black_scholes(double S, double E, double r, double sigma, double T, int size){

	double* trials = (double*) malloc (sizeof(double) * size);

	srand(time(NULL));

	double aux;

	for(int i = 0; i < size; i++){
		aux = S * exp(((r - 0.5 * pow(sigma, 2) ) * T) + (sigma * sqrt(T) * (rand()/(double) RAND_MAX) ) );

		trials[i] = exp(- r * T) * max(aux - E, 0);
	}

	return trials;

}

double mean(double* array, int size){
	double sum = 0.00;

	for(int i = 0; i < size; i++){
		sum += array[i];
	}

	sum = sum/((double) size);

	return sum;
}

double stddev(double* array, double mean, int size){
	double sum = 0.00;

	for(int i = 0; i < size; i++){
		sum += pow(array[i] - mean, 2);
	}

	sum = sum/((double) size);
	sum = sqrt(sum);

	return sum;
}

double confwidth(double deviation, int size){
	return (1.96 * deviation / sqrt(size));
}

double confmin(double mean, double confwidth){
	return mean - confwidth;
}

double confmax(double mean, double confwidth){
	return mean + confwidth;
}


int main(){

	double S;
	double E;
	double r;
	double sigma;
	double T;
	int num_iterations;

	scanf("%lf", &S);
	scanf("%lf", &E);
	scanf("%lf", &r);
	scanf("%lf", &sigma);
	scanf("%lf", &T);
	scanf("%d", &num_iterations);

	double* result = black_scholes(S, E, r, sigma, T, num_iterations);

	double result_mean = mean(result, num_iterations);
	double result_stddev = stddev(result, result_mean, num_iterations);
	double result_confwidth = confwidth(result_stddev, num_iterations);
	double result_confmin = confmin(result_mean, result_confwidth);
	double result_confmax = confmax(result_mean, result_confwidth);

	printf("S: %lf\n", S);
	printf("E: %lf\n", E);
	printf("r: %lf\n", r);
	printf("sigma: %lf\n", sigma);
	printf("T: %lf\n", T);
	printf("Confidente Interval: %lf, %lf", result_confmin, result_confmax);

	return 0;

}
