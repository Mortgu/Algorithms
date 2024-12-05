#ifndef ALGORITHMS_PERLIN_H
#define ALGORITHMS_PERLIN_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int p[512];

double noise(double x, double y, double z);

double fade(double t);
double lerp(double t, double a, double b);
double grad(int hash, double x, double y, double z);

void load_permutation(char* fileName);

#endif
