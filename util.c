#include "./include/util.h"
#include <stdio.h>
#include <math.h>

double numerical_diff(double(*fn)(double), double x){
    double h = 1e-4;
    // central difference
    return (fn(x + h) - fn(x - h)) / (2 * h);
}

double fn_1(double x){
    return 0.01 * x * x + 0.1 * x;
}

double square(double x){
    return x * x ;
}


double sigmoid(double x){
    return 1.f/(1.f + exp(-x));
}


