/*gcc -o ising_energy ising_energy.c -lgsl -lgslcblas*/


#include "ising_energy.h"
#include <stdio.h>


int main () {
  lattice *test = create_lattice(3, 3, 1);
  gsl_rng *r = set_zufall(0);
  rand_spin(test, r);
  e_tot(test);
  for(int i = 0; i < 9; i++){
    printf("%i\t", test->spin[i]);
    if ((i+1)%3 == 0) printf("\n");
  }
  printf("%lf\n", test->e_tot);
  lattice_invert(test);
  for(int i = 0; i < 9; i++){
    printf("%i\t", test->spin[i]);
    if ((i+1)%3 == 0) printf("\n");
  }
  printf("%lf\n", test->e_tot);
  return 0;
}

void rand_spin(lattice *lat, gsl_rng *r){
  int i;
  for(i = 0; i < (lat->y_max)*(lat->x_max); i++) {
    if (gsl_rng_uniform(r) < 0.5){
      lat->spin[i] = -1;
    }
    else {
      lat->spin[i] = 1;
    }
  }

}

double e_tot(lattice *lat){
  int x_max = lat->x_max, y_max = lat->y_max, *spin = lat->spin;
  double J = lat->J;
  double e = 0;
  for (int i = 0; i < y_max*x_max; i++){
    if (i - x_max < 0){
      if (i == 0){
        e += J*spin[i]*(spin[i+1]+spin[i+x_max]+spin[i+x_max-1]+spin[x_max*y_max-x_max+i]);
      } else
      if (i == x_max-1){
        e += J*spin[i]*(spin[i-1]+spin[i+x_max]+spin[i-x_max+1]+spin[i+x_max*y_max-x_max]);
      } else {
        e += J*spin[i]*(spin[i-1]+spin[i+1]+spin[i+x_max]+spin[i+x_max*y_max-x_max]);
      }
    } else
    if (i + x_max >= x_max*y_max){
      if (i%x_max == 0){
        e += J*spin[i]*(spin[i+1]+spin[i-x_max]+spin[i+x_max-1]+spin[i-x_max*y_max+x_max]);
      } else
      if ((i+1)%x_max == 0){
        e += J*spin[i]*(spin[i-1]+spin[i-x_max]+spin[i-x_max*y_max+x_max]+spin[i-x_max+1]);
      } else {
        e += J*spin[i]*(spin[i-1]+spin[i+1]+spin[i-x_max]+spin[i-x_max*y_max+x_max]);
      }
    } else
    if (i%x_max == 0){
      e += J*spin[i]*(spin[i-x_max]+spin[i+1]+spin[i+x_max]+spin[i+x_max-1]);
    } else
    if ((i+1)%x_max == 0){
      e += J*spin[i]*(spin[i-x_max]+spin[i-1]+spin[i+x_max]+spin[i-x_max+1]);
    } else {
      e += J*spin[i]*(spin[i-x_max]+spin[i+1]+spin[i+x_max]+spin[i-1]);
    }
  }
  lat->e_tot = -e;
  return -e;
}


lattice *create_lattice(int x_max, int y_max, double J) {
  lattice *tmp = malloc(sizeof(lattice));
  tmp->spin = malloc(x_max*y_max*sizeof(int));
  tmp->x_max = x_max;
  tmp->y_max = y_max;
  tmp->J = J;
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

void lattice_invert(lattice *lat){
  for (int i = 0; i < (lat->x_max*lat->y_max); i++) lat->spin[i] = -lat->spin[i];
}
