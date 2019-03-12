#include <stdio.h>
#include <stdlib.h>

#define LIN 3
#define COL 3

typedef struct no No;

struct no {
    int linha;
    int coluna;
    No *prox;
};

typedef struct fila Fila;

struct fila {
    No *inicio;
    No *fim;
    int tamanho;
};

No *no = NULL;
Fila *f = NULL;

void insereFila (int linha, int coluna, Fila *f) {
	No *novo;
	
	novo = malloc(sizeof(Fila));
	novo->linha = linha;
	novo->coluna = coluna;
    novo->prox = NULL; 
	
	if (f->tamanho == 0) f->inicio = novo;
	
	else f->fim->prox = novo;
	
	f->fim = novo;
/*	printf ("\n%d %d", novo->linha, novo->coluna);*/
	f->tamanho++;
/*	printf("\n%d ", f->tamanho); */
}

void imprime (Fila *f) {
	No *p;
	p = f->inicio;
	
	while (p != NULL) {
		printf ("%d %d", p->linha, p->coluna);
		p = p->prox;
     	printf("\n");	
	}
	printf("\n");	
}	

No *removeFila (Fila *f) {
	No *p;
	p = f->inicio;
	f->inicio = p->prox;
	free(p);
	f->tamanho--;
	return p->prox;
}

int * distancias (int labirinto[][COL], int m, int n) {
 
   
}

int main () {
	
	Fila *F = malloc(sizeof(Fila));
    F->inicio = NULL;
    F->fim = NULL;
    F->tamanho = 0;
    insereFila(2, 3, F);
    insereFila(1, 3, F);
    insereFila(8, 2, F);
    removeFila(F);
    imprime(F);

}
