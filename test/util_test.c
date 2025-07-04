#include "./include/util.h"
#include <stdio.h>
#include <math.h>

double fn_1(double x){
    return 0.01 * x * x + 0.1 * x;
}

void test_numerical_diff(){
    double test_x = 5;
    double res = numerical_diff(fn_1, test_x);
    printf("when x is: %.5f, numerical_diff's ans is: %.5f\n", test_x, res);
}

double square(double x){
    return x * x ;
}


void test_sigmoid(){
    for (int i = -10; i < 10; i++){
        printf("when x = %d, the result of sigmoid is %.5f\n", i, sigmoid(i));
    }
}

void test_cosine_similarity(){
#define DIM 2
    double a[DIM] = {1, 2};
    double b[DIM] = {2, 5};
    printf("cosine_similarity: %.5f\n",cosine_similarity(a, b, DIM));

}

int main(){
    // test_numerical_diff();
//    test_sigmoid();
    test_cosine_similarity();
}
