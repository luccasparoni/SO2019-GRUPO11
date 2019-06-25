/* Trabalho Disciplina Sistemas Operacionais

Metodo de com  */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double borwein(int);

int main(){

  double pi = borwein(1000000000); // desired number os iterations
  printf("%f /n ", pi);

  return 0;
}

double borwein(int n){
  //n is the number of iterarions wanted
  double pi = 0.0;
  double currentIteration = 0.0;

  double frac1, frac2, frac3, frac4, frac5;

  for(currentIteration; currentIteration < n; currentIteration++){

    frac1 = pow(16,currentIteration);

    frac2 = 4/(8 * currentIteration + 1);
    frac3 = 2/(8 * currentIteration + 4);
    frac4 = 1/(8 * currentIteration + 5);
    frac5 = 1/(8 * currentIteration + 6);

    pi += (1/frac1 * (frac2 - frac3 - frac4 - frac5));

  }

  return pi;
}

