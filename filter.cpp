/////////////////////////////////////////////////////
// Filename: filter.cpp
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 27 feb 2023
/////////////////////////////////////////////////////
#include "filter.h"
#include<assert.h>

Zfilter::Zfilter(unsigned M_in, vector<double> numerator, unsigned N_in ,vector<double> denominator){

    M = M_in;
    N= N_in;
    num_coeff = numerator;
    den_coeff = denominator;
    //assert(M<= MAX_SZ);
    //assert(N<=MAX_SZ);
    num.reSize(M);
    den.reSize(N);
    num.setAll(0);
    den.setAll(0);
    alpha = den_coeff.shiftLeft(0);
}

Zfilter::~Zfilter(){

}
double Zfilter::calcOut( double n){
    double val;

    num.shiftRight(n);
    val = (num.dotProduct(num_coeff) - den.dotProduct(den_coeff))/alpha;
    den.shiftRight(val);

    return val;
}
