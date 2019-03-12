#include <stdio.h>
#include <stdlib.h>

#define RECS_PATIO 2

struct Rec_Emp {
    char nome_rec[10];
    int uso_rec;
    int taxa_rec;
    struct Rec_Emp *prox;
};

typedef struct Rec_Emp recuperadora;

struct Patio {
    char iden_patio;
    int capacidade;
    struct Patio *prox;
    struct Rec_Emp *lista[RECS_PATIO];
}; 

typedef struct Patio patio;
