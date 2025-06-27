#include "./include/util.h"
#include <stdio.h>
#include <math.h>



void test_numerical_diff(){
    double test_x = 5;
    double res = numerical_diff(fn_1, test_x);
    printf("when x is: %.5f, numerical_diff's ans is: %.5f\n", test_x, res);
}

void test_sigmoid(){
    for (int i = -10; i < 10; i++){
        printf("when x = %d, the result of sigmoid is %.5f\n", i, sigmoid(i));
    }
}

int main(){

    // test_numerical_diff();
    test_sigmoid();
}
