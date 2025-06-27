#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct Model{
    double w1;
    double b;
};

#define EPOCHS 150
#define N 5
#define RATE 1e-2

double m_data[N] = {1, 2, 3, 4, 5};

//double m_label[N] = {2, 4, 6, 8, 10};
double m_label[N] = {3, 6, 9, 12, 15};

struct Model M = {0, 0};

void init_model() {
    srand(time(0));
    double r = (double) rand() / (double) RAND_MAX;
    M.w1 = r;
    M.b = r;
}

double forward(double x){
    return M.w1 * x + M.b;
}

double loss(){
    double res = 0.f;
    for (int i = 0; i < N; i++){
        double x = m_data[i];
        double y = m_label[i];
        double pred = forward(x);
        // MSE
        double diff = y - pred;
        res += diff * diff;
    }
    
    return res/N;
}

void show(){
    printf("model's w1: %.5f, b: %.5f\n", M.w1, M.b);
}

void test(){
    double test_x = 10;
    double test_pred = forward(test_x);
    printf("===========\n");
    printf("when x is: %.5f, the prediction is: %.5f\n", test_x, test_pred);
}

int main(){
    
    init_model();

//    printf("loss: %.5f\n", loss());

    for (int i = 0; i < EPOCHS; i++){
        for (int j = 0; j < N; j++){
            double x = m_data[j];
            double y = m_label[j];
            double pred = forward(x);
            
            // MSE
            double err = pred - y;

            // Gradient descent
            double dw1 = 2 * err * x;
            double db = 2 * err;

            M.w1 -= RATE * dw1;
            M.b -= RATE * db;

        }
        printf("loss: %.5f\n", loss());
    }

    show();

    test();

    return 0;
}


