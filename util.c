#include "./include/util.h"
#include <stdio.h>
#include <math.h>

double numerical_diff(double(*fn)(double), double x){
    double h = 1e-4;
    // central difference
    return (fn(x + h) - fn(x - h)) / (2 * h);
}

double sigmoid(double x){
    return 1.f/(1.f + exp(-x));
}


