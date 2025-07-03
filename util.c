#include "./include/util.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double numerical_diff(double(*fn)(double), double x){
    double h = 1e-4;
    // central difference
    return (fn(x + h) - fn(x - h)) / (2 * h);
}

double sigmoid(double x){
    return 1.f/(1.f + exp(-x));
}

double cosine_similarity(double a[], double b[], int dim){

    double dot = 0.f, nm_a = 0.f, nm_b = 0.f;
    for(int i = 0; i < dim; i++){
        dot += a[i] * b[i];
        nm_a += a[i] * a[i];
        nm_b += b[i] * b[i];
    }

    return dot / (sqrt(nm_a) * sqrt(nm_b));
}
