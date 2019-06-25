#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#include <gmp.h>

// Metodo de execução p/ imprimir no arquivo saida.txt e ler de entrada.txt  ./blackscholes<entrada.txt>saida.txt
// Metodo de compillação   gcc blackscholes.c -o blackscholes -lm -lpthread



#define thread_num 4

//global variables

double S, E, r, sigma, T, M;

//declared with the biggest value possible to avoid dinamyc vector
double trials[100000];

int calculated[4];

double max(double, double);

int correct_current(int n){//this function resolve the problem since the code is not sequencial
  if(n ==4){
    n = 0;
  }
  if(calculated[n] == 1){
    n++;
    n = correct_current(n);
  }
  calculated[n] = 1;
  return n;
}

void* black_scholes(void* arg){
  int i;
  int current_iteration = *((int*)arg);
  current_iteration = correct_current(current_iteration);

  srand(time(NULL));

  //declaring aux variables to calculate trials
  double aux1,aux2, aux3, aux4, aux5, aux6, aux7, t;

  for(i = M*current_iteration/4; i < M*(current_iteration + 1)/4; i++){

    //now, we calcuate trials with the given parameters

    t = S * pow(M_E, (r - 0.5*pow(sigma, 2)) * T + sigma*sqrt(T)* (rand()/(double)RAND_MAX));

    trials[i] =  pow(M_E,-r*T) * max(t-E, 0);

  }
}

double max(double num1, double num2){
	if(num1 > num2) return num1;
	else return num2;
}

double calculate_mean(){
    double sum = 0.00;

    for(int i = 0; i < M; i++){
        sum += trials[i];
    }

    sum = sum/((double) M);

    return sum;
}

double calculate_stddev(double mean){
    double sum = 0.00;

    for(int i = 0; i < M; i++){
        sum += pow(trials[i] - mean, 2);
    }

    sum = sum/((double) M);
    sum = sqrt(sum);

    return sum;
}

double calculate_confwidth(double deviation){
    return (1.96 * deviation / sqrt(M));
}

double calculate_confmin(double mean, double confwidth){
    return mean - confwidth;
}

double calculate_confmax(double mean, double confwidth){
    return mean + confwidth;
}


int main(){
  double mean, stddev, confwidth, confmin, confmax;
  int thread_number, rstatus;
  scanf("%lf %lf %lf %lf %lf %lf", &S, &E, &r, &sigma, &T, &M);

  // declaring threads that will be used
  pthread_t all_threads[thread_num];

  for(thread_number =  0; thread_number < thread_num; thread_number++){

    pthread_create(&all_threads[thread_number], NULL, black_scholes, &thread_number);
  }
  // implemented with 'for'=> if the number of threads change, the code adapts itself

  for(thread_number =  0; thread_number < thread_num; thread_number++){
    rstatus = pthread_join(all_threads[thread_number], NULL);

    if(rstatus != 0){
      printf("Error ocurred on thread %d\n", thread_number);
    }
  }

  //now, we have all trials calculated, lets now find mean, stddev, confwidth tc;

  mean = calculate_mean();
  stddev = calculate_stddev(mean);
  confwidth = calculate_confwidth(stddev);
  confmin = calculate_confmin(mean, confwidth);
  confmax = calculate_confmax(mean, confwidth);

  printf("S         %.0lf\nE         %.0lf\nr         %.0lf\nsigma     %.0lf\nT         %.0lf\nM         %.0lf\nConfidence interval (%.4lf, %.4lf)",S, E, r, sigma, T, M, confmin, confmax);





  return 0;
}
