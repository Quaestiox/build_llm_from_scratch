#include <time.h>
#include <stdio.h>
#include "./include/mtx.h"
#include "./include/util.h"

#define EM_SIZE 3
#define EPOCHS 1000
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

double* em_forward(Mtx em_mtx, Mtx input, int ctx_size, int r){
    double *vec = (double*)calloc((EM_SIZE+1), sizeof(double));
    for(int i = 1; i <= ctx_size; i++){
        int idx = mtx_at(input, r, i);
        for(int j = 1; j <= EM_SIZE; j++){
            vec[j] += mtx_at(em_mtx, idx, j); 
        }
    }

    for(int i = 1; i <= EM_SIZE; i++){
        vec[i] /= ctx_size;
    }

    return vec;
}

double *out_forward(Mtx out_w, int v_size, double* vec){
    double *pred = (double*)calloc((v_size+1), sizeof(double));
    for(int i = 1; i <= v_size; i++){
        pred[i] = 0;
        for(int j = 1; j <= EM_SIZE; j++){
            pred[i] += mtx_at(out_w, j, i) * vec[j];
        }
    }
    return pred;
}

double loss(double *sm, int target){
    return -log(sm[target] + 1e-10); 
}

void forward(Mtx *em_mtx, Mtx *out_w, Train train){
    int input_size = train.input->rows;
    int ctx_size = train.input->cols;
    Mtx *labels = train.output;
    int v_size = out_w->cols;
    double t_loss = 0.f;
    for(int r = 1; r <= input_size; r++){
        double target = mtx_at(*labels, 1, r);
   
        double *vec = em_forward(*em_mtx, *train.input, ctx_size, r);
///        print_arr(vec+1, EM_SIZE);

        double *pred = out_forward(*out_w, v_size, vec+1);
//        print_arr(pred+1, v_size);
        double *sm = malloc(sizeof(double) * v_size);;
        softmax(pred+1, v_size, sm);
//        print_arr(sm, v_size);
//        printf("loss = %.5f\n",  loss(sm, (int)target));
        t_loss += loss(sm, (int)target);
//
//        // loss
        double err[v_size+1];
        for (int i = 1; i <= v_size; ++i){
            err[i] = sm[i] - (i == target ? 1.0 : 0.0);
        }
//        print_arr(err+1, v_size);
//
        for (int i = 1; i <= EM_SIZE; ++i){
            for (int j = 1; j <= v_size; ++j){
                 mtx_up(out_w, i, j, -RATE * err[j] * vec[i]);
            }
        }
//
        double dvec[EM_SIZE+1] = {0};
        for (int i = 1; i <= EM_SIZE; ++i){
            for (int j = 1; j <= v_size; ++j){
                double w = mtx_at(*out_w, i, j);
                dvec[i] += w * err[j];
            }
        }
//           
        for (int i = 1; i <= ctx_size; ++i) {
            int idx = mtx_at(*train.input, r, i);
            for (int j = 1; j <= EM_SIZE; ++j)
                mtx_up(em_mtx, idx, j, -RATE * dvec[j] / ctx_size);
        }

        free(vec);
        free(pred);
    }
    printf("Loss = %.4f\n", t_loss / input_size);
    
}

void training(Train train, Mtx *em_mtx, Mtx *out_w){
    for(int i = 0; i < EPOCHS; i++){

        forward(em_mtx, out_w, train);
    }
}

void predict(char **context_tokens, int ctx_size, Vocab vocab, Mtx *em_mtx, Mtx *out_w) {
    Mtx *input = init_mtx(1, ctx_size * 2);
    for (int i = 0; i < ctx_size * 2; i++) {
        int id = get_id_by_token(vocab, context_tokens[i]);
        if (id == -1) {
            printf("Unknown token: %s\n", context_tokens[i]);
            return;
        }
        mtx_set(input, 1, i+1, id);
    }
    print_mtx(*input, "input");

    double *vec = em_forward(*em_mtx, *input, ctx_size * 2, 1);
    print_arr(vec+1,ctx_size*2);
    double *pred = out_forward(*out_w, vocab.count, vec+1);
    print_arr(pred+1, vocab.count);
    double *sm = (double*)malloc(sizeof(double) * vocab.count);
    softmax(pred+1, vocab.count, sm);
    print_arr(sm, vocab.count);

    int max_id = 0;
    double max_prob = sm[0];
    for (int i = 1; i < vocab.count; i++) {
        if (sm[i] > max_prob) {
            max_prob = sm[i];
            max_id = i;
        }
    }

    Token predicted = get_token_by_id(vocab, max_id);
    printf("Predicted word: %s (prob: %.3f)\n", predicted.token, max_prob);

    free(input);
    free(vec);
    free(pred);
    free(sm);
}

int main(){
    srand(time(0));
    char *tokens[10] = {"i", "like", "deep", "learning", "i", "like", "nlp", "i", "enjoy", "flying"};

#define TOKEN_SIZE sizeof(tokens)/sizeof(tokens[0])

    Vocab *vocab = build_vocab(tokens, TOKEN_SIZE);
//    print_vocab(*vocab);

    // in
    Mtx *em_mtx = init_mtx(vocab->count, EM_SIZE);
    rand_mtx(em_mtx);
//    print_mtx(*em_mtx, "embedding matrix");

    // out
    Mtx *out_w = init_mtx(EM_SIZE, vocab->count);
    rand_mtx(out_w);
//    print_mtx(*out_w, "output_weight matrix");


    Train *train = get_input(tokens, *vocab, TOKEN_SIZE, 2);
//    print_mtx(*train->input, "input");
//    print_mtx(*train->output, "output");

    training(*train, em_mtx, out_w);

    printf("===== after train =====\n");
    print_mtx(*em_mtx, "embedding matrix");


    char *test_ctx[] = {"i", "like", "i", "enjoy"};  
    predict(test_ctx, 2, *vocab, em_mtx, out_w);

    
    free(vocab);
    free(em_mtx);
    return 0;
}
