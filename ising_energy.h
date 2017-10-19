#ifndef ISING_ENERGY_H
#define ISING_ENERGY_H

#include <stdlib.h>

typedef struct lattice {
  int x_max;
  int y_max;
  int *spin;
  double J;
} lattice;

lattice *create_lattice(int x_max, int y_max, double J);
void rand_spin(lattice *lat);
double e_tot(lattice *lat);

#endif
