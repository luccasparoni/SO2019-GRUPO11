#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include <gmp.h>

#define NUM_ITERATIONS 100000

mpf_t aux1, aux2, aux3, aux4, aux5, gmp_sixteen, gmp_eight, num_8k;
  mpf_t frac2, frac3, frac4, frac5;
  mpf_t frac1;
  mpf_t pi;


void * frac1_calculation(void *arg){
  mpf_pow_ui(aux1, gmp_sixteen, *((int *)arg));
  mpf_ui_div(frac1, 1, aux1);

  pthread_exit(frac1);
}


void * frac2_calculation(void *arg){

  mpf_add_ui(aux2, num_8k, 1);
  mpf_ui_div(frac2, 4, aux2); //create each fraction used in the original formula

  pthread_exit(frac2);
}
void * frac3_calculation(void *arg){

  mpf_add_ui(aux3, num_8k, 4);
  mpf_ui_div(frac3, 2, aux3); //create each fraction used in the original formula

  pthread_exit(frac3);
}
void * frac4_calculation(void *arg){

  mpf_add_ui(aux4, num_8k, 5);
  mpf_ui_div(frac4, 1, aux4); //create each fraction used in the original formula

  pthread_exit(frac4);
}
void * frac5_calculation(void *arg){

  mpf_add_ui(aux5, num_8k, 6);
  mpf_ui_div(frac5, 1, aux5); //create each fraction used in the original formula

  pthread_exit(frac5);
}

void parallel_borwein(int n){

  // setting the precision

  mpf_set_default_prec(pow(10,5));

  // Variable declarations

  int i, rstatus1, rstatus2, rstatus3, rstatus4, rstatus5;

  //Varibables initialization

  mpf_init(pi);
  mpf_init(frac1);
  mpf_init(frac2);
  mpf_init(frac3);
  mpf_init(frac4);
  mpf_init(frac5);
  mpf_init(aux1);
  mpf_init(aux2);
  mpf_init(aux3);
  mpf_init(aux4);
  mpf_init(aux5);
  mpf_init(gmp_sixteen);
  mpf_init(gmp_eight);
  mpf_init(num_8k);

  //setting some default values
  mpf_set_ui(gmp_sixteen, 16);
  mpf_set_ui(gmp_eight, 8);
  mpf_set_ui(pi, 0);

  // declaring threads that will be used
  pthread_t thread_frac1[NUM_ITERATIONS];
  pthread_t thread_frac2[NUM_ITERATIONS];
  pthread_t thread_frac3[NUM_ITERATIONS];
  pthread_t thread_frac4[NUM_ITERATIONS];
  pthread_t thread_frac5[NUM_ITERATIONS];




// Now we can start to iterate and create all threads

  for(i=0; i< n; i++){
    mpf_mul_ui(num_8k, gmp_eight, i); // num_8k

    pthread_create(&thread_frac1[i], NULL, frac1_calculation, &i);
    pthread_create(&thread_frac2[i], NULL, frac2_calculation, &i);
    pthread_create(&thread_frac3[i], NULL, frac3_calculation, &i);
    pthread_create(&thread_frac4[i], NULL, frac4_calculation, &i);
    pthread_create(&thread_frac5[i], NULL, frac5_calculation, &i);

    rstatus1= pthread_join(thread_frac1[i], NULL);
    if(rstatus1 != 0)printf("deu erro no frac1\n");
    rstatus2= pthread_join(thread_frac2[i], NULL);
    if(rstatus2 != 0)printf("deu erro no frac2\n");
    rstatus3= pthread_join(thread_frac3[i], NULL);
    if(rstatus3 != 0)printf("deu erro no frac3\n");
    rstatus4= pthread_join(thread_frac4[i], NULL);
    if(rstatus4 != 0)printf("deu erro no frac4\n");
    rstatus5= pthread_join(thread_frac5[i], NULL);
    if(rstatus5 != 0)printf("deu erro no frac5\n");

    mpf_sub(frac2,frac2, frac3); //frac2 = frac2 - frac3
    mpf_sub(frac2,frac2, frac4);
    mpf_sub(frac2,frac2, frac5);

    mpf_mul(frac1, frac1, frac2);

    mpf_add(pi, pi, frac1); //add to the current value of pi the value calculated in this step
  }

  gmp_printf("Value of Pi calculted with parallel Borwein: %.16Ff", pi);
}



void main(){

  parallel_borwein(NUM_ITERATIONS);

  mpf_clear(pi);
  mpf_clear(frac1);
  mpf_clear(frac2);
  mpf_clear(frac3);
  mpf_clear(frac4);
  mpf_clear(frac5);
  mpf_clear(aux1);
  mpf_clear(aux2);
  mpf_clear(aux3);
  mpf_clear(aux4);
  mpf_clear(aux5);
  mpf_clear(gmp_sixteen);
  mpf_clear(gmp_eight);
  mpf_clear(num_8k);

  return;
}
