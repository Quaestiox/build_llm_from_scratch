#include "./include/mtx.h"

Mtx* init_mtx(int rows, int cols){
    double *els = (double *)malloc(rows * cols * sizeof(double));
    assert(els != NULL);
    Mtx *m = (Mtx*)malloc(sizeof(Mtx));
    assert(m != NULL);
    m->rows = rows;
    m->cols = cols;
    m->els = els;
    return m;
}

double mtx_at(Mtx mtx, int row, int col){
    return *(mtx.els + (mtx.cols * row + col));
}

void mtx_set(Mtx *mtx, int row, int col, double v){
    *(mtx->els + (mtx->cols * row + col)) = v;
}

void print_mtx(Mtx mtx, char *name){
    printf("%s = [\n", name);
    for (int i = 0; i < mtx.rows; i++){
        for(int j = 0; j < mtx.cols; j++){
            printf("%10.5f", mtx_at(mtx, i, j));
        }
        printf("\n");
    }
    printf("]\n");
}

void rand_mtx(Mtx *mtx){
    for (int i = 0; i < mtx->rows; i++){
        for(int j = 0; j < mtx->cols; j++){
            mtx_set(mtx, i, j, (double)rand()/(double)RAND_MAX);
        }
    }

}

Token get_token_by_id(Vocab vocab, int id){
    assert(id < vocab.count && id > 0);
    return vocab.dict[id];
}

int get_id_by_token(Vocab vocab, char *token){
    for(int i = 0; i < vocab.count; i++){
        if (strcmp(vocab.dict[i].token, token) == 0){
            return i;
        }
    }
    return -1;
}

void add_token(Vocab *vocab, char *token){
    int res = get_id_by_token(*vocab, token);
    if (res == -1){
        vocab->dict[vocab->count].token = token;
        vocab->dict[vocab->count].count = 1;
        vocab->count ++;
    }else{
        vocab->dict[res].count ++;
    }
}

Vocab* build_vocab(char **tokens, int len){
    Vocab *v = malloc(sizeof(Vocab));
    v->count = 0;
    for (int i = 0; i < len; i++){
        add_token(v, tokens[i]);
    }
    return v;

}

void print_vocab(Vocab vocab){
    for(int i = 0; i < vocab.count; i++){
        printf("id: %4d token: %10s count: %4d\n", i, vocab.dict[i].token, vocab.dict[i].count);
    }
}


