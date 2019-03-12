#include <stdio.h>
#include <stdlib.h>

typedef struct _RegPilha {
	int dado;
    struct _RegPilha *prox;
} RegPilha;
typedef RegPilha* Pilha;
typedef enum boolean {false,true} bool;

typedef struct reg {
      int  conteudo; // conteúdo
      struct reg *esq;
      struct reg *dir;
} noh; // nó

typedef noh arvore;

noh *AlocaNoh(){
	noh* q;
	q = (noh*)calloc(1, sizeof(noh));
    if(q==NULL) exit(-1); 
    return q;
}

void insere(arvore **r, int x){
    if(*r == NULL){
        *r = AlocaNoh();
        (*r)->esq = NULL;
        (*r)->dir = NULL;
        (*r)->conteudo = x;
    }else{
        if(x < (*r)->conteudo)
            insere(&(*r)->esq, x);
        if(x > (*r)->conteudo)
            insere(&(*r)->dir, x);
    }
}

RegPilha *AlocaRegPilha() {
	RegPilha* q;
    q = (RegPilha*)calloc(1, sizeof(RegPilha));
    if(q==NULL) exit(-1); 
    return q;
}

Pilha CriaPilha() {
	Pilha p;
    p = AlocaRegPilha();
    p->prox = NULL;
    return p;
}
 
void LiberaPilha(Pilha p) {
	RegPilha *q,*t;
    q = p;
    while(q!=NULL){
    t = q;
    q = q->prox;
    free(t);
    }
}

bool PilhaVazia(Pilha p) {
	return (p->prox==NULL);
}
 
void Empilha(Pilha p, arvore *r) {
	RegPilha *q;
    q = AlocaRegPilha();
    q->dado = r->conteudo;
    q->prox = p->prox;
    p->prox = q;
}

int Desempilha(Pilha p) {
	RegPilha *q;
    int x;
    q = p->prox;
    if(q==NULL) exit(-1);
    x = q->dado;
    p->prox = q->prox;
    free(q);
    return x; 
}

void erd_i (arvore *r) {
	arvore *x, *p[100];
	int t = 0;
    x = r;
    while (x != NULL || t > 0) {
       if (x != NULL) {
          p[t++] = x;
          x = x->esq;
       }
       else {
          x = p[--t];
          printf ("%d\n", x->conteudo);
          x = x->dir;
       }
    }
}

int main() {
	arvore *noh = NULL;
	int n = 0;
	insere (&noh, 12);
	insere (&noh, 30);
	insere (&noh, 6);
	insere (&noh, 15);
	insere (&noh, 2);
	insere (&noh, 1);
	insere (&noh, 20);
	insere (&noh, 5);
	insere (&noh, 32);
	erd_i(noh);
}	
	
