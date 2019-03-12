#include <stdio.h>
#include <stdlib.h>

struct pessoa {
	int posicao;
	struct pessoa *prox;
};

typedef struct pessoa Pessoa;

Pessoa *inicio = NULL;

void insere (int x) {
	Pessoa *nova, *p = inicio;
	nova = (Pessoa *)malloc(sizeof(Pessoa));
	nova->posicao = x;
    while (p->prox != inicio && p->posicao < x)
       p = p->prox;
	nova->prox = p->prox;
    p->prox = nova;	
}

void remove1 (Pessoa *p) {
    Pessoa *q; 
    q = p->prox;
       if (q != inicio) {
       p->prox = q->prox;
       free(q);
    }   
}

void imprime () {
	Pessoa *q;
	for (q = inicio->prox; q != inicio; q = q->prox) 
	    printf ("%d ", q->posicao);
	printf("\n");
} 

int  conta_nos (Pessoa *inicio) {
	Pessoa *q; int cont = 0;	
	for (q = inicio->prox; q != inicio; q = q->prox)
	    cont++;
	return cont;
}

void resolvejesephus (int n, int m) {
	Pessoa *q = inicio->prox; int i = 1;
	while (conta_nos(q) > 1) {		
			i = 1;	 
	 if (q == inicio) 
 	 q = inicio->prox;   	
		while (i < m) {  
	    if (n > m) {
	    	if (q == inicio) {
		    	q = inicio->prox; 
		    	i++;
    	    }
        }	
        if (n < m) {
	    	if (q == inicio) {
		    	q = inicio->prox; 
		    	i= i+2;
    	    }
        }      	
	    q = q->prox;
    	i++;				
	}     
      if (q->prox == inicio) q = inicio;
	    remove1(q);
    	q = q->prox; 
     	imprime();	
	}
}


int main () {
	
	int n, m, i;
    inicio = (Pessoa*)malloc(sizeof(Pessoa));
    inicio->posicao = -1;
	inicio->prox = inicio;
	
	scanf ("%d", &n);
	scanf ("%d", &m);
	
	for (i = 1; i <= n; i++)
	    insere (i);
	
	imprime();
	resolvejesephus(n, m);
	imprime();
	
	return 0;
}

