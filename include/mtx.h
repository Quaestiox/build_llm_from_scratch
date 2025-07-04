#ifndef MTX_H
#define MTX_H

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

typedef struct{
    int rows;
    int cols; 
    double *els;
} Mtx;


Mtx* init_mtx(int rows, int cols);

void print_mtx(Mtx mtx, char *name);

void rand_mtx(Mtx *mtx);

Token get_token_by_id(Vocab vocab, int id);

int get_id_by_token(Vocab vocab, char *token);

void add_token(Vocab *vocab, char *token);

Vocab* build_vocab(char **tokens, int len);

void print_vocab(Vocab vocab);

#endif
