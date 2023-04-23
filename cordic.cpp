/////////////////////////////////////////////////////
// Filename: cordic.cpp
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 22 Apr 2023
/////////////////////////////////////////////////////
#include "cordic.h"

/* All angles in radians*/

const angle_value_tuple lut[12] = {
                                    {SCALE,0.7854},
                                    {SCALE>>1,0.4636},
                                    {SCALE>>2,0.2450},
                                    {SCALE>>3,0.1244},
                                    {SCALE>>4,0.0624},
                                    {SCALE>>5,0.03124},
                                    {SCALE>>6,0.015624},
                                    {SCALE>>7,0.0078},
                                    {SCALE>>8,0.0039},
                                    {SCALE>>9,0.0020},
                                    {SCALE>>10,0.0009},
                                    {SCALE>>11,0.0005}
                                    };

unsigned int lookup(double angle){
    unsigned int idx = 0;

    while((lut[idx].angle > angle) && (lut[idx+1].angle > angle)){
        idx++;
        if( idx >= 11)
            break;
    }

    return idx;
}

void cordic_theta(int *X, int *Y, double theta){
    double Z;
    int sigma;
    double angle;
    unsigned int i = 0;
    unsigned int idx = 0;
    Z = fmod(theta,PI);
    if(Z > PI/2)
        Z = -(PI - Z);

    sigma = (Z>0)?1:-1;
    *X = 9949;
    *Y = 0;
    
    //idx = lookup(abs(theta));
    do
    {
        angle = lut[idx].angle;
        *X = (*X) - ((sigma * (*Y))>>i) ;
        *Y = (*Y) + ((sigma * (*X))>>i) ;
        Z = Z - (sigma * angle);
        sigma = ( Z > 0 )? 1:-1;
        i++;
        idx = i;

    } while ((Z > ERROR_THRESHOLD) || ( i < 12));
    
}

double cordic_sin(double theta){
    int X_cos, Y_sin;
    cordic_theta(&X_cos,&Y_sin,theta);
    return (double) ((double)Y_sin/SCALE);
}
double cordic_cos(double theta){
    int X_cos, Y_sin;
    cordic_theta(&X_cos,&Y_sin,theta);
    return (double) ((double)X_cos/SCALE);
}

