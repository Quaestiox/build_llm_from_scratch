#ifndef UTIL_H

#define UTIL_H



double numerical_diff(double(*fn)(double), double);

double sigmoid(double);

double cosine_similarity(double *, double*, int);

void softmax(double *x, int len, double *out);

void print_arr(double *arr, int len);
#endif 



