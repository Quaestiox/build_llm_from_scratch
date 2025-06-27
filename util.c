#include "./include/util.h"
#include <stdio.h>

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

int main(){
    double test_x = 5;
    double res = numerical_diff(fn_1, test_x);
    printf("when x is: %.5f, numerical_diff's ans is: %.5f\n", test_x, res);
}
