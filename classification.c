#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "include/util.h" 

struct Model{
    double w1;
    double w2;
    double b;
};

#define EPOCHS 10000
#define N 4
#define RATE 1e-2

struct Model M = {0, 0, 0};

double or_data[N][2] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1},
};

double or_label[N] = {0, 1, 1, 1};

void init_model(){
    srand(time(0));
    double r = (double) rand()/(double) RAND_MAX;
    M.w1 = r;
    M.w2 = r;
    M.b = r;
}

double forward(double x1, double x2){
    return sigmoid(x1 * M.w1 + x2 * M.w2 + M.b);
}

double loss(){
    double res = 0.f;
    for (int i = 0; i< N;i++){
        double pred = forward(or_data[i][0], or_data[i][1]);
        double label = or_label[i];
        // Binary Cross Entropy
        res += -(label * log(pred) + (1 - label) * log(1 - pred));
    }
    return res/N;
}

void show(){
    printf("model's w1: %.5f, w2: %.5f, b: %.5f\n", M.w1, M.w2, M.b);
}

void train(){
    for(int i = 0; i < EPOCHS; i++){
        for(int j = 0; j < N; j++){
            double x1 = or_data[j][0];
            double x2 = or_data[j][1];
            double y = or_label[j];

            double pred = forward(x1, x2);

            double err = pred - y;
            double dw1 = err * x1;
            double dw2 = err * x2;
            double db = err;

            M.w1 -= RATE * dw1;
            M.w2 -= RATE * dw2;
            M.b -= RATE * db;
        }
        printf("loss: %.5f\n", loss());
    }
}

int main(){
    init_model();

    train();
    
    show();

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            printf("input: %d  %d, output:%.5f\n", i, j, forward(i, j));
        }
    }
    return 0;
}


