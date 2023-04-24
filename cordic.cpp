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
                                    {SCALE>>10,0.0010},
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
    int tmp= 0;

    int sigma;
    double angle;
    unsigned int i = 0;
    unsigned int idx = 0;
    quads_t q;


    Z = fmod(theta,2*PI);
    if( Z < 0)
        Z = Z + 2*PI;

    if((Z < PI/2) && ( Z > 0 )){
        q = QUAD1;
    } else if ((Z > PI/2) && (Z < PI)){
        q = QUAD2;
        Z = Z - PI/2;
    } else if ((Z > PI) && ( Z < 3*PI/2))
    {
        q = QUAD3;
        Z = Z - PI;
    }else if ((Z > 3*PI/2) && ( Z < 2*PI))
    {
        q = QUAD4;
        Z = Z - 3*PI/2;
    }
    
    
    

    sigma = (Z>0)?1:-1;
    *X = 9949;
    *Y = 0;
    
    //idx = lookup(abs(theta));
    do
    {
        angle = lut[idx].angle;
        *X = (*X) - (sigma * ((*Y)>>idx)) ;
        *Y = (*Y) + (sigma * ((*X)>>idx)) ;
        Z = Z - (sigma * angle);
        sigma = ( Z > 0 )? 1:-1;
        i++;
        idx = i;

    } while ((Z > ERROR_THRESHOLD) && ( i < 12));

    switch (q)
    {
    case QUAD1:
        break;
    case QUAD2:
        tmp = -*X;
        *X = *Y;
        *Y = tmp;
        break;
    case QUAD3:
        *X = -*X;
        *Y = -*Y;
        break;
    case QUAD4:
        tmp = *Y;
        *Y = *X;
        *X = -tmp;
        break;
    default:
        break;
    }    
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

