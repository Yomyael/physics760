#ifndef ISING_ENERGY_H
#define ISING_ENERGY_H

typedef struct lattice {
  int x_max;
  int y_max;
  int *spin;
} lattice;

lattice *create_lattice(int x_max, int y_max);


#endif
