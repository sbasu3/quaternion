/////////////////////////////////////////////////////
// Filename: filter.h
// Author: Subhojit Basu [ subhojit.basu@gmail.com ]
// License : MIT License
// Creation Date : 27 feb 2023
/////////////////////////////////////////////////////
#ifndef __FILTER__
#define __FILTER__
#include "vector.cpp"


class Zfilter{
    private:
        vector<double> num_coeff;
        vector<double> den_coeff;
        vector<double> num;
        vector<double> den;
        double alpha;
        unsigned int M;
        unsigned int N;
    public:
        Zfilter(unsigned M, vector<double> numerator, unsigned N ,vector<double> denominator);
        ~Zfilter();
        double calcOut( double num);
};
#endif