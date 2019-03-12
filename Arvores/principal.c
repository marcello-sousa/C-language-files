#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include "Fila.c"
#define N 100
//int parent[100], nivel[100];
#define troca(A, B) { int t = A; A = B; B = t; }

typedef struct reg {
	int conteudo; 
	int chave;
    struct reg *esq;
    struct reg *dir;
} noh; 

typedef noh arvore;

noh *AlocaNoh(){
	noh* q;
	q = (noh*)calloc(1, sizeof(noh));
    if(q==NULL) exit(-1); 
    return q;
}

void erd (arvore *r) {
	if (r != NULL) {
		erd(r->esq);
		printf("%d ", r->conteudo);
		erd(r->dir);		
	}
}

void imprime_nivel (arvore *r) {
	arvore *fila[N], *x;
	int inicio, fim;
	x = r;
	inicio = fim = 0;
	fila[fim++] = x;
	while( inicio < fim) {
		x = fila[inicio++];
		printf("%d ", x->conteudo);
		if(x->esq != NULL) fila[fim++] = x->esq;	    if(x->dir != NULL) fila[fim++] = x->dir;
	}
}

void insere(arvore **r, int x) {
    if(*r == NULL) {
        *r = AlocaNoh();
        (*r)->esq = NULL;
        (*r)->dir = NULL;
        (*r)->conteudo = x;
    }
    else {
    	if(x < (*r)->conteudo)
            insere(&(*r)->esq, x);
        if(x > (*r)->conteudo)
            insere(&(*r)->dir, x);
    }
}

noh *novo_no( int k) {
    noh *novo;
    novo = malloc(sizeof(noh));
    novo->chave = k;
    novo->esq = novo->dir = NULL;
    return novo;
}

void red (arvore *r) {
	if (r != NULL) {
		printf("%d ", r->conteudo);
		red(r->esq);
		red(r->dir);		
	}
}

void edr (arvore *r) {
	if (r != NULL) {	
		red(r->esq);
		red(r->dir);
		printf("%d ", r->conteudo);		
	}
}

/*arvore *insere2 (arvore r, noh *novo) {  
    if (r == NULL) return novo;
    if (r->chave > novo->chave) 
       r->esq = insere (r->esq, novo);
    else 
       r->dir = insere (r->dir, novo);
    return r;
} */

int conta_nos (arvore *r) {	
	if (r == NULL) return 0;
	else {			
		int conte = conta_nos(r->esq); 		
		int contd = conta_nos(r->dir);	
	    return conte + contd + 1;	
	}
} 

int conta_noh (arvore *r) {	
	if (r == NULL) return 0;
	else {			
		 return 1 + conta_nos(r->esq) + conta_nos(r->dir); 		
	}
} 

void imprime (arvore *r) {
	if (r != NULL) {
		imprime (r->esq);
		printf ("%d ", r->conteudo);
		imprime (r->dir);
	}	
} 

int altura (arvore *r) {
	if (r == NULL) return -1;
	else {
		int he = altura(r->esq);
		int hd = altura(r->dir);
		if (he < hd) return hd + 1;
	    else return he + 1;
	}
}

int altura_i ( arvore *r) {
	arvore *fila[N], *x;
	int *parent, *nivel;
	int inicio, fim, i, j, cont;
	parent = malloc( conta_noh(r)*sizeof(int));
	nivel  = malloc( conta_noh(r)*sizeof(int));
	x = r;
	inicio = fim = i = 0;
	fila[fim++] = x;
	parent[i] = x->conteudo;
	while( inicio < fim) {
		x = fila[inicio++];
		nivel[j++] = x->conteudo;
		if( x->esq != NULL) {
			parent[++i] = x->conteudo;
			fila[fim++] = x->esq;
		}
		if( x->dir != NULL) {
			parent[++i] = x->conteudo;
			fila[fim++] = x->dir;
		}
	}
	cont = 0;
	i = nivel[conta_noh(r) - 1];
	while( i != nivel[0]) {	
		j = 0; 
		while( nivel[j] != i) j++;
		i = parent[j];
		cont++;	
	} 
	free(nivel); free(parent);
	return cont; 
}

int depht_tree( arvore *r, int x) {
	if( r == NULL) return 0;	
	else {
		if( r->conteudo == x) return 0;
		else if( x < r->conteudo) return 1 + depht_tree( r->esq, x);
        else return 1 + depht_tree( r->dir, x);
    }
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
          printf ("%d ", x->conteudo);
          x = x->dir;
       }
    }
}

int busca_noh (arvore *r, int val) {
	if (r == NULL) return 0;
	else {
		if (r->conteudo == val) 
		    return 1;
		else if (r->conteudo > val) 
			return busca_noh(r->esq, val);
		else 
			return busca_noh(r->dir,val);	
	}
} 

arvore* ConstroiHeap( int *v, int n) {
	int f, k;
	arvore *r;
	for( k = 1; k < n; ++k) {
		f = k + 1;
		while( f > 1 && v[f/2] < v[f]) {
			troca(v[f/2], v[f]);
			f /= 2;
		}
	}
	for( int i = 1; i < n; i++) 
		insere(&r, v[i]);
	return r;
}

void troca_conteudo( arvore *i, arvore *j) {
	arvore *t;
	t = malloc(sizeof(arvore));
	*t = *i;
	*i = *j;
	i->esq = t->esq;
	i->dir = t->dir;
	t->esq = j->esq;
	t->dir = j->dir;
	*j = *t;
	j->esq = t->esq;
	j->dir = t->dir;	
}

arvore* hierarquica( arvore *r) {
	arvore *p;	
	return p;
}

arvore* busca_min( arvore *r) {
	arvore *x = r;
	while( x->esq != NULL) 
		x = x->esq;
	return x;
}

arvore* busca_max( arvore *r) {
	arvore *x = r;
	while( x->dir != NULL) 
		x = x->dir;
	return x;
}

arvore* insere_balanceada( int *v, int inicio, int fim, arvore *r) {
	if( inicio > fim) return 0;
	else {
		int meio = (fim + inicio) / 2;		
		insere(&r, v[meio]);
		insere_balanceada(v, inicio, meio-1, r);
		insere_balanceada(v, meio+1, fim, r);
	    return r;
	}
}

int conta_folhas (arvore *r) {
	if( r == NULL) return 0; 
	else {
	    int a = 0;
	    if( r->esq == NULL && r->dir == NULL) a = 1;
	    return a + conta_folhas( r->esq) + conta_folhas( r->dir);
	}
}

int conta_filhos (arvore *r) {
	if( r == NULL) return 0; 
	else {
	    int a = 0;
	    if( r->esq != NULL || r->dir != NULL) a = 1;
	    return a + conta_filhos( r->esq) + conta_filhos( r->dir);
	}
}

int conta_maiores( arvore *r, int x) {
	if( r == NULL) return 0; 
	else {
	    int a = 0;
	    if( r->conteudo >= x) a = 1;
	    return a + conta_maiores( r->esq, x) + conta_maiores( r->dir, x);
	}
}

int maiordosmaiores( arvore *R) {
	arvore *p;
	if (R == NULL || R->esq  == NULL) return -1;
	p = R->esq;
	while (p->dir != NULL) p = p->dir;
	return p->conteudo;	
}

noh *novo_noh( int k) {
    noh *novo;
    novo = malloc(sizeof(noh));
    novo->conteudo = k;
    novo->esq = novo->dir = NULL;
    return novo;
}

arvore *insereI( arvore *r, int x) {
	arvore *novo, *p;
	if( r == NULL) {
		novo = novo_noh(x);
		return novo;
	}
	novo = novo_noh(x);
	p = r;
	while( p->esq != NULL && p->dir != NULL) {
		if( novo->conteudo < p->conteudo) p = p->esq;
		else p = p->dir;
	}
	if( novo->conteudo < p->conteudo) p->esq = novo;
	else p->dir = novo;
	return r;    
}

int main() {
	arvore *noh = NULL;
	int n = 0;
/*	insere (&noh, 5);
	insere (&noh, 3);
	insere (&noh, 8);
	insere (&noh, 1);
	insere (&noh, 4);
	insere (&noh, 6);
	insere (&noh, 9);
	insere (&noh, 0);
	insere (&noh, 2);
	insere (&noh, 7); 
	insere (&noh, 5); 
	insere (&noh, 6);
	insere (&noh, 7);
	insere (&noh, 8);
	insere (&noh, 9); 
	insere (&noh, 10); 
	insere (&noh, 7);
	insere (&noh, 1);
	insere (&noh, 8);
	insere (&noh, 5);
	insere (&noh, 9);
	insere (&noh, 3); */
/*	erd(noh);
	printf("\n");
	red(noh);
	printf("\n");
	edr(noh);
//	printf ("\nNumero de nos = %d ", conta_noh(noh));
//	printf ("\nAltura %d", altura(noh)); 
	printf ("\nProfundidade %d", prof(noh, 6)); 
	printf ("\nAchou %d \n", busca_noh(noh, 9));
	erd_i(noh);
	printf("\n");
	imprime_nivel(noh);
	altura_i(noh);
	printf("Altura_i = %d \n", altura_i(noh));
	printf("\n");
	printf( "Profundidade: %d", depht_tree(noh, 5));
	int v[] = {-1, 4, 12, 1, 5, 6, 9, 10, 3};
	arvore *p = ConstroiHeap( v, 9);
	imprime_nivel(p);
	arvore *q = busca_min(noh);
	printf("\n\nMínimo = %d\n ", q->conteudo);
	q = busca_max( noh);
	printf("\nMáximo = %d\n ", q->conteudo); */
//	arvore *l;  
//	int w[] = {1, 4, 5, 10, 16, 17, 21};
	int w[] = {1, 3, 5, 7, 8, 9, 10};
//  int w[] = {0, 1, 1, 3, 4, 4, 5, 6, 6};
    noh = insere_balanceada(w, 0, 6, noh);
//	erd(l);
	imprime_nivel(noh);
//	printf("\n%d", altura_i(l));
	printf("\nFolhas = %d ", conta_folhas(noh));
	printf("\nFilhos = %d ", conta_filhos(noh));
	printf("\nMaiores = %d ", conta_maiores(noh, 4));
	printf("\nMaiordosMaiores = %d\n", maiordosmaiores(noh));	
	printf("\n");
	noh = insereI(noh, 6);
	erd(noh);
	printf("\n");
	imprime_nivel(noh);
	printf( "Profundidade: %d", depht_tree(noh, 3));
	
	return 0;
}
