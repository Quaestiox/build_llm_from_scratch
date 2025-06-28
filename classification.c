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
#define MODEL_NUM 5

struct Model Models[MODEL_NUM];

double gate_data[N][2] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1},
};

char names[MODEL_NUM][128] = {"OR", "AND", "NAND", "NOR", "XOR"};
double labels[MODEL_NUM][N] = {
    // OR
    {0, 1, 1, 1},
    // AND 
    {0, 0, 0, 1},
    // NAND
    {1, 1, 1, 0},
    // nor
    {1, 0, 0, 0},
    // XOR
    {0, 1, 1, 0}
};

void init_model(){
    srand(time(0));
    double r = (double) rand()/(double) RAND_MAX;
    for (int i = 0; i < MODEL_NUM; i++){
        struct Model m = Models[i];
            m.w1 = r;
            m.w2 = r;
            m.b = r;
    }
}

double forward(struct Model m, double x1, double x2){
    return sigmoid(x1 * m.w1 + x2 * m.w2 + m.b);
}

double loss(struct Model m, double *l){
    double res = 0.f;
    for (int i = 0; i< N;i++){
        double pred = forward(m, gate_data[i][0], gate_data[i][1]);
        double label = l[i];
        // Binary Cross Entropy
        res += -(label * log(pred) + (1 - label) * log(1 - pred));
    }
    return res/N;
}

void show(struct Model m){
    printf("model's w1: %.5f, w2: %.5f, b: %.5f\n", m.w1, m.w2, m.b);
}

void train(struct Model *m, double *label){
    for(int i = 0; i < EPOCHS; i++){
        for(int j = 0; j < N; j++){
            double x1 = gate_data[j][0];
            double x2 = gate_data[j][1];
            double y = label[j];

            double pred = forward(*m, x1, x2);

            double err = pred - y;
            double dw1 = err * x1;
            double dw2 = err * x2;
            double db = err;

            m->w1 -= RATE * dw1;
            m->w2 -= RATE * dw2;
            m->b -= RATE * db;
        }
        printf("loss: %.5f\n", loss(*m, label));
    }
}

void test(struct Model m){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            printf("input: %d  %d, output:%.5f\n", i, j, forward(m, i, j));
        }
    }
   
}

void train_all(){
    for (int i = 0; i < MODEL_NUM-1; i++){
        double *label = labels[i];
        train(&Models[i], label);
    }
}

void show_all(){
    for (int i = 0; i < MODEL_NUM-1; i++){
        struct Model m = Models[i];
        char *name = names[i];
        printf("===== %s =====\n", name);
        show(m);
    }
}

void test_all(){
    for (int i = 0; i < MODEL_NUM-1; i++){
        struct Model m = Models[i];
        char *name = names[i];
        printf("===== %s =====\n", name);
        test(m);
    }
}

int main(){
    init_model();
    
    train_all();
       
    show_all();

    test_all();

    // Multi-layered Perceptron
    
    return 0;
}


