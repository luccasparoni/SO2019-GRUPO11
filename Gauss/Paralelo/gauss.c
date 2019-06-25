#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 1000

typedef struct struct_a_data{
	double a;
	double prev_a;
	double prev_b;
}A_DATA;

typedef struct struct_b_data{
	double b;
	double prev_a;
	double prev_b;
}B_DATA;

typedef struct struct_t_data{
	double t;
	double a;
	double prev_a;
	double prev_b;
	double prev_t;
	double prev_p;
}T_DATA;

typedef struct struct_p_data{
	double p;
	double prev_p;
}P_DATA;

void *a_calculation(void* arg){
	A_DATA* a_data = arg;
	a_data->a = (a_data->prev_a + a_data->prev_b) / 2.00;
	//pthread_exit(0);

}

void *b_calculation(void* arg){
	B_DATA* b_data = arg;
	b_data->b = sqrt(b_data->prev_a * b_data->prev_b);
	//pthread_exit(0);
}

void *t_calculation(void* arg){
	T_DATA* t_data = arg;
	t_data->t = t_data->prev_t - t_data->prev_p * pow(t_data->prev_a - t_data->a, 2);
	//pthread_exit(0);
}

void *p_calculation(void* arg){
	P_DATA* p_data = arg;
	p_data->p = 2.00 * p_data->prev_p;
	//pthread_exit(0);
}

double gauss_legendre_parallel(){
	pthread_t threadA[NUM_ITERATIONS];
	pthread_t threadB[NUM_ITERATIONS];
	pthread_t threadP[NUM_ITERATIONS];
	pthread_t threadT[NUM_ITERATIONS];

	double a[NUM_ITERATIONS];
	double b[NUM_ITERATIONS];
	double t[NUM_ITERATIONS];
	double p[NUM_ITERATIONS];

	a[0] = 1.00;
	b[0] = 1.00 / (sqrt(2));
	t[0] = 1.00 / 4.00;
	p[0] = 1.00;

	a[1] = (a[0] + b[0]) / 2.00;
	b[1] = sqrt(a[0] * b[0]);

	A_DATA a_data;
	B_DATA b_data;
	T_DATA t_data;
	P_DATA p_data;

	int i;

	for(i = 2; i < NUM_ITERATIONS; i++){

		t_data.a = a[i-1];

		a_data.prev_a = a[i-1];
		b_data.prev_a = a[i-1];
		t_data.prev_a = a[i-2];

		a_data.prev_b = b[i-1];
		b_data.prev_b = b[i-1];
		t_data.prev_b = b[i-2];

		t_data.prev_t = t[i-2];

		t_data.prev_p = p[i-2];
		p_data.prev_p = p[i-2];



		pthread_create(&threadA[i], NULL, a_calculation, &a_data);
		pthread_create(&threadB[i], NULL, b_calculation, &b_data);
		pthread_create(&threadT[i], NULL, t_calculation, &t_data);
		pthread_create(&threadP[i], NULL, p_calculation, &p_data);

		pthread_join(threadA[i], NULL);
		pthread_join(threadB[i], NULL);
		pthread_join(threadT[i], NULL);
		pthread_join(threadP[i], NULL);

		a[i] = a_data.a;
		b[i] = b_data.b;
		t[i-1] = t_data.t;
		p[i-1] = p_data.p;


	}

	double pi =  pow(a[i-2] + b[i-2] , 2) / (4.0 * t[i-2]);

	return pi;
}


int main(){
	printf("pi = %.10f\n", gauss_legendre_parallel());

	pthread_exit(NULL);

	return 0;
}
