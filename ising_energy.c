/*gcc -o ising_energy ising_energy.c -lgsl -lgslcblas*/


#include "ising_energy.h"
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <time.h>

gsl_rng *set_zufall(int sec);

int main () {
  gsl_rng *rand = set_zufall(0);
  lattice *test = create_lattice(3, 3);
  int i;
  for(i = 0; i < 9; i++) {
    if (gsl_rng_uniform(rand) < 0.5){
      test->spin[i] = -1;
    }
    else {
      test->spin[i] = 1;
    }
  }
  for(i = 0; i < 9; i++){
    printf("%i\t", test->spin[i]);
    if((i+1)%test->x_max == 0){
      printf("\n");
    }
  }
  return 0;
}



lattice *create_lattice(int x_max, int y_max) {
  lattice *tmp = malloc(sizeof(lattice));
  tmp->spin = malloc(x_max*y_max*sizeof(int));
  tmp->x_max = x_max;
  tmp->y_max = y_max;
  return tmp;
}

gsl_rng *set_zufall(int sec){
	gsl_rng *r;
	const gsl_rng_type *T;

	gsl_rng_env_setup();
	/*Alternativen fuer gsl_rng_:
		random8_bsd (178 MHz), random256_bsd (117 MHz),
		gfsr4 (107 MHz), mt19937 (84 MHz),
		ranlxs0 (22 MHz), ranlxs1 (15 MHz),
		ranlxd1 (8,3 MHz), ranlxd2 (4,6 MHz)
	Ich empfehle:
		mt19937 fuer Standardsachen,
		ranlxd2 fuer wirklich heikle Berechnungen*/
	T = gsl_rng_mt19937;
	r = gsl_rng_alloc(T);
	gsl_rng_set(r, time(NULL)+sec);

	return r;
}
