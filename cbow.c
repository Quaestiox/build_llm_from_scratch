#include <stdio.h>
#include "./include/mtx.h"

#define EM_SIZE 3


int main(){
    char *tokens[10] = {"i", "like", "deep", "learning", "i", "like", "nlp", "i", "enjoy", "flying"};

#define TOKEN_SIZE sizeof(tokens)/sizeof(tokens[0])

    Vocab *vocab = build_vocab(tokens, TOKEN_SIZE);
    print_vocab(*vocab);

    Mtx *em_mtx = init_mtx(vocab->count, EM_SIZE);
    rand_mtx(em_mtx);
    print_mtx(*em_mtx, "embedding matrix");


    free(vocab);
    free(em_mtx);
    return 0;
}
