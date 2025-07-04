#include <stdio.h>
#include "./include/mtx.h"
#include "./include/util.h"

#define EM_SIZE 3
#define EPOCHS 1500
#define RATE 1e-3

typedef struct{
    Mtx *input;
    Mtx *output;
} Train;

Train* get_input(char **tokens, Vocab vocab, int len, int size){
    Mtx *input = init_mtx(len-size*2, size*2); 
    Mtx *output = init_mtx(1, len-size*2);
    for(int i = size; i < len-size; i++){

        int i_id = get_id_by_token(vocab, tokens[i]);
        int count = 1;
        for(int j = i - size; j <= i + size; j++){
            if (j == i) {
                mtx_set(output, 1, i-size+1, i_id);
                continue;
            }
            int j_id = get_id_by_token(vocab, tokens[j]);
            mtx_set(input, i-size+1, count, j_id);
            count ++;
        }
    }
    Train *train = (Train *)malloc(sizeof(Train));
    train->input = input;
    train->output = output;
    return train;
}

void loss(){

}

void forward(Mtx *em_mtx, Mtx *out_w, Train train){
    double vec[EM_SIZE+1] = {0};

    int input_size = train.input->rows;
    int ctx_size = train.input->cols;
    Mtx *labels = train.output;
    int v_size = out_w->cols;
    double t_loss = 0.f;
    for(int r = 1; r <= input_size; r++){
        double target = mtx_at(*labels, 1, r);
        for(int i = 1; i <= ctx_size; i++){
            int idx = mtx_at(*train.input, r, i);
            for(int j = 1; j <= EM_SIZE; j++){
                vec[j] += mtx_at(*em_mtx, idx, j); 
            }
        }

        for(int i = 1; i <= EM_SIZE; i++){
            vec[i] /= ctx_size;
        }

        double pred[v_size+1];
        for(int i = 1; i <= v_size; i++){
            pred[i] = 0;
            for(int j = 1; j <= EM_SIZE; j++){
                pred[i] = mtx_at(*out_w, j, i) * vec[j];
            }
        }


        double ans[v_size+1];
        softmax(out_w->els, v_size, ans);
        // print_arr(ans, v_size+1);

        t_loss += -log(ans[(int)target] + 1e-3); 

        // loss
        double err[v_size+1];
        for (int i = 1; i <= v_size; ++i){
            err[i] = pred[i] - (i == target ? 1.0 : 0.0);
        }

        for (int i = 1; i <= EM_SIZE; ++i){
            for (int j = 1; j <= v_size; ++j){
                 mtx_up(out_w, i, j, -RATE * err[j] * vec[i]);
            }
        }

        double dvec[EM_SIZE] = {0};
        for (int i = 1; i <= EM_SIZE; ++i){
            for (int j = 1; j <= v_size; ++j){
                double w = mtx_at(*out_w, i, j);
                dvec[i] += w * err[j];
            }
        }
           
        for (int i = i; i <= ctx_size; ++i) {
            int idx = mtx_at(*train.input, r, i);
            for (int j = 1; j <= EM_SIZE; ++j)
                mtx_up(em_mtx, idx, j, -RATE * dvec[j] / ctx_size);
        }
    }
    printf("Loss = %.4f\n", t_loss / input_size);
    
}

void training(Train train, Mtx *em_mtx, Mtx *out_w){
    for(int i = 0; i < EPOCHS; i++){
        forward(em_mtx, out_w, train);
    }
}



int main(){
    char *tokens[10] = {"i", "like", "deep", "learning", "i", "like", "nlp", "i", "enjoy", "flying"};

#define TOKEN_SIZE sizeof(tokens)/sizeof(tokens[0])

    Vocab *vocab = build_vocab(tokens, TOKEN_SIZE);
    print_vocab(*vocab);

    // in
    Mtx *em_mtx = init_mtx(vocab->count, EM_SIZE);
    rand_mtx(em_mtx);
    print_mtx(*em_mtx, "embedding matrix");

    // out
    Mtx *out_w = init_mtx(EM_SIZE, vocab->count);
    rand_mtx(out_w);
    print_mtx(*out_w, "output_weight matrix");


    Train *train = get_input(tokens, *vocab, TOKEN_SIZE, 2);
    print_mtx(*train->input, "input");
    print_mtx(*train->output, "output");

    training(*train, em_mtx, out_w);



    
    free(vocab);
    free(em_mtx);
    return 0;
}
