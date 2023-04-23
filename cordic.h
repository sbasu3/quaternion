/////////////////////////////////////////////////////
// Filename: cordic.h
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 22 Apr 2023
/////////////////////////////////////////////////////

#ifndef __CORDIC
#define __CORDIC
/* All angles in radians*/
#include <stdint.h>
#include <stdio.h>
#include <math.h>


#define ERROR_THRESHOLD 1e-6
#define PI 3.14159
#define SCALE 16384

typedef struct {
    int value;
    double angle;
}angle_value_tuple;

unsigned int lookup(double angle);
void cordic_theta(uint16_t *X, uint16_t *Y, double theta);
double cordic_sin(double theta);
double cordic_cos(double theta);

#endif