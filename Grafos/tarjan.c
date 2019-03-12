#include <stdio.h>
#include <stdlib.h>
//#include "Fila.h"
//#include "Fila.c"
//#include "pilha.h"
//#include "pilha.c"
typedef int vertex;
static int *pre, *low;
static int cnt, topo[1000];
static int k, N;
static vertex *stack;
static vertex parent[1000];
/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */

typedef struct node *link;
struct node { 
   vertex w; 
   link next; 
};

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura graph representa um grafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */

struct graph {
   int V; 
   int A; 
   link *adj; 
};
/* Um Graph é um ponteiro para um graph. */

typedef struct graph *Graph;

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next. */

static link NEWnode( vertex w, link next) { 
   link a = malloc( sizeof (link));
   a->w = w; 
   a->next = next;     
   return a;                         
}

Graph GRAPHinit (int V) {
	vertex v;
	Graph G = malloc(sizeof*G);
	G->V = V;
	G->A = 0;
	G->adj = malloc(V*sizeof(link));
	for (v = 0; v < V; v++) 
		G->adj[v] = NULL;
	return G;
}

void GRAPHinsertA (Graph G, vertex v, vertex w) {
	link a;
	for (a = G->adj[v]; a != NULL; a = a->next) 
		if (a->w == w) return;
	G->adj[v] = NEWnode(w, G->adj[v]);
	G->A++;	
}

void UGRAPHinsertE( Graph E, vertex v, vertex w) {
	GRAPHinsertA (E, v, w);
	GRAPHinsertA (E, w, v);
}

/* O código de strongR() foi adaptado da figura 5.15 do livro de Aho, Hopcroft e Ullman. */

static void strongR( Graph G, vertex v, int *sc) { 
   vertex w, u; link a; int min;
   pre[v] = cnt++;
   min = pre[v]; 
   stack[N++] = v;
   for (a = G->adj[v]; a != NULL; a = a->next) {
      w = a->w;
      if (pre[w] == -1) {
         strongR( G, w, sc);
         if (low[w] < min) min = low[w]; /*A*/
      }
      else if (pre[w] < pre[v] && sc[w] == -1) {
         if (pre[w] < min) min = pre[w]; /*B*/
      }
   }
   low[v] = min;
   if (low[v] == pre[v]) {               /*C*/
      do {
         u = stack[--N];
         sc[u] = k;
      } while (u != v);
      k++;
   }
}

/* A função GRAPHscT() devolve o número de componentes fortes do grafo G e armazena no vetor sc[], indexado pelo vértices de G, os nomes das componentes fortes de G: para cada vértice u, sc[u] será o nome da componente forte que contém u. Os nomes das componentes fortes são 0, 1, 2, etc. (A função implementa o algoritmo de Tarjan.) */

int GRAPHscT( Graph G, int *sc) {
   vertex v; 
   pre = malloc( G->V * sizeof (int));
   low = malloc( G->V * sizeof (int));
   stack = malloc( G->V * sizeof (vertex));
   for (v = 0; v < G->V; ++v) 
      pre[v] = sc[v] = -1;

   k = N = cnt = 0;
   for (v = 0; v < G->V; ++v) 
      if (pre[v] == -1)
         strongR( G, v, sc);
   free( pre); free( low); free( stack);
   return k;
}

static void bridgesR( Graph G, vertex v) { 
   link a; int min; 
   pre[v] = cnt++; 

   min = pre[v];
   for (a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] == -1) {
         parent[w] = v;
         bridgesR( G, w);
         if (low[w] < min) /*A*/
            min = low[w];
      }
      else {
         if (pre[w] < min && w != parent[v]) /*B*/
            min = pre[w];
      }
   }
   low[v]= min;

   for (v = 0; v < G->V; ++v) 
      if (low[v] == pre[v] && parent[v] != v)
         /* arco parent[v]-v faz parte de ponte */
         printf( "%d-%d\n", parent[v], v);
}


void UGRAPHbridges( Graph G) { 
	vertex v;
	pre = malloc( G->V * sizeof (int));
    low = malloc( G->V * sizeof (int));
    for (v = 0; v < G->V; ++v)
       pre[v] = parent[v] = -1;
    cnt = 0;
    for (v = 0; v < G->V; ++v)
       if (pre[v] == -1) {
          parent[v] = v;
          bridgesR( G, v);
       }
}
/* A função bridgesR() recebe um vértice v e imprime todas as pontes que estão na subárvore da floresta DFS que tem raiz v. */


int main() {
	int sc[100];
	Graph G = GRAPHinit( 10);
	UGRAPHinsertE( G, 3, 7);
	UGRAPHinsertE( G, 1, 4);
	UGRAPHinsertE( G, 7, 8);
	UGRAPHinsertE( G, 0, 5);
	UGRAPHinsertE( G, 5, 2);
	UGRAPHinsertE( G, 3, 8);
	UGRAPHinsertE( G, 2, 9);
	UGRAPHinsertE( G, 0, 6);
	UGRAPHinsertE( G, 4, 9);
	UGRAPHinsertE( G, 2, 6);
	UGRAPHinsertE( G, 6, 4);
	//GRAPHscT( G, sc);
	UGRAPHbridges( G);
	//printf("\nsc : ");
	//for (int i = 0; i < G->V; ++i) 
		//printf("%d ", sc[i]);
}
