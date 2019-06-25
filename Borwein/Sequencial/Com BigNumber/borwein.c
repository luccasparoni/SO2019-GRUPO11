#include <gmp.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Compilation gcc program_name.c -o program_name -lgmp


void borwein(int n);

int main(){
    int n = 100000;
    borwein(n);
    return 0;
}

void borwein(int n){

    //setting the precicion

    mpf_set_default_prec(pow(10,5));//ver pq é assim


    //Variable declarations
    mpf_t pi;

    mpf_t frac1, frac2, frac3, frac4, frac5, aux1, aux2, aux3, aux4, aux5, gmp_sixteen, gmp_eight, num_8k;

    int i;

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

    for(i=0; i < n; i++){

       //equivallent of pow(16, i)
        mpf_pow_ui(aux1, gmp_sixteen, i);


        mpf_mul_ui(num_8k, gmp_eight, i); // num_8k

        mpf_add_ui(aux2, num_8k, 1);
        mpf_add_ui(aux3, num_8k, 4);
        mpf_add_ui(aux4, num_8k, 5);
        mpf_add_ui(aux5, num_8k, 6);

        mpf_ui_div(frac1, 1, aux1); // In this line, we have 1/(16^k)

        mpf_ui_div(frac2, 4, aux2); //create each fraction used in the original formula
        mpf_ui_div(frac3, 2, aux3);
        mpf_ui_div(frac4, 1, aux4);
        mpf_ui_div(frac5, 1, aux5);

        mpf_sub(frac2,frac2, frac3); //frac2 = frac2 - frac3
        mpf_sub(frac2,frac2, frac4);
        mpf_sub(frac2,frac2, frac5);

        mpf_mul(frac1, frac1, frac2);

        mpf_add(pi, pi, frac1); //add to the current value of pi the value calculated in this step
        gmp_printf("%.15Ff\n", pi);
    }

    gmp_printf("Value of Pi calculated with Borwein algorithm  %.15Ff", pi);


    //clear all variables used

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


}
