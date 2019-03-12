#include <stdio.h>
#include<stdlib.h>

struct pessoa {
	int posicao;
	struct pessoa *prox;
};

typedef struct pessoa Pessoa;

Pessoa *p = NULL;

void insere (int x, Pessoa *inicio) {
	Pessoa *nova;
	/*p = inicio->prox;
	ap = inicio;
	*/
	nova = (int *)malloc(sizeof(int));
	nova->posicao = x;
	
   /* while (p->prox != inicio && p->posicao < x) {
       ap = p;
       */

	nova->prox = inicio->prox;
    inicio->prox = nova;
	
}

void imprime (Pessoa *inicio) {
	Pessoa *q;
	
	for (q = inicio->prox; q!= inicio->prox->prox; q = q->prox) 
	    printf ("%d ", q->posicao);
	printf("\n");
} 

int main () {
	
	int n, i;
	p = (int *)malloc(sizeof(int)); 
	p->prox = p;
	
	scanf ("%d", &n);
	
	
	for (i = 1; i <= n; i++)
	    insere (i, p);
	
	imprime(p);
	
	
	
	return 0;
}




