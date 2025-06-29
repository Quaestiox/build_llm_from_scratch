#include <stdio.h>
#include <string.h>
#include <assert.h> 
#include <math.h>
#include <stdlib.h>

#define MAX_TOKEN 1000
#define MAX_EL 100

typedef struct{
    char *token;
    int count;
} Token;

typedef struct{
    Token dict[MAX_TOKEN];
    int count;
} Vocab;

typedef double Mat[MAX_EL][MAX_EL];

Vocab vocab;

Mat co_mat = {0};
Mat ppmi_mat = {0};

Token get_token_by_id(int id){
    assert(id < vocab.count && id > 0);
    return vocab.dict[id];
}

int get_id_by_token(char *token){
    for(int i = 0; i < vocab.count; i++){
        if (strcmp(vocab.dict[i].token, token) == 0){
            return i;
        }
    }
    return -1;

}

void add_token(char *token){
    int res = get_id_by_token(token);
    if (res == -1){
        vocab.dict[vocab.count].token = token;
        vocab.dict[vocab.count].count = 1;
        vocab.count ++;
    }else{
        vocab.dict[res].count ++;
    }
}

void build_vocab(char **tokens, int len){
    for (int i = 0; i < len; i++){
        add_token(tokens[i]);
    }
}

void print_vocab(){
    for(int i = 0; i < vocab.count; i++){
        printf("id: %4d token: %10s count: %4d\n", i, vocab.dict[i].token, vocab.dict[i].count);
    }
}

void build_co_mat(char **tokens, int len, int window_size){
    for(int i = 0; i < len; i++) {
        int id = get_id_by_token(tokens[i]);
        for(int j = i - window_size; j < i + window_size; j++){
            if (j < 0 || j >= len || j == i) continue;
            int ct_id = get_id_by_token(tokens[j]);
            co_mat[id][ct_id] ++;
        }
    }
}

void build_ppmi_max(){
    double eps = 1e-2;
    int total = 0;
    int counts[MAX_EL] = {0};
    for(int i = 0; i < vocab.count; i++){
        for(int j = 0; j < vocab.count; j++){
            total += co_mat[i][j];
            counts[j] += co_mat[i][j];
        }
    }

    for(int i = 0; i < vocab.count; i++){
        for(int j = 0; j < vocab.count; j++){
            double pmi  = log2((co_mat[i][j] * total)/(counts[i] * counts[j] + eps));
            if (pmi < 0){
                pmi = 0;
            }
            ppmi_mat[i][j] = pmi;
        }
    }
}

void print_mat(Mat mat, char *name){
    printf("%s = [\n", name);
    for(int i = 0; i < vocab.count; i ++){
        for(int j = 0; j < vocab.count; j ++){
            printf("%6.2f", mat[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

int main(){
    char *tokens[10] = {"i", "like", "deep", "learning", "i", "like", "nlp", "i", "enjoy", "flying"};

#define TOKEN_SIZE sizeof(tokens)/sizeof(tokens[0])

    build_vocab(tokens, TOKEN_SIZE);
    print_vocab();
    build_co_mat(tokens, TOKEN_SIZE, 1);
    print_mat(co_mat, "co_occurence matrix") ;
    build_ppmi_max();
    print_mat(ppmi_mat, "PPMI matrix");
}





