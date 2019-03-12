#include <stdio.h>
#include <stdlib.h>
//#include "Fila.h"
//#include "Fila.c"
#include "pilha.h"
#include "pilha.c"
typedef int vertex;
#define UGraph Graph
static int visit[1000];
int pre[1000], post[1000], topo[1000], parent[1000];
static int cnt, cnt1;

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

void GRAPHindeg( Graph G) {
	vertex v;
	for( v = 0; v < G->V; v++) 
		for( link a = G->adj[v]; a != NULL; a = a->next) 
			topo[a->w] += 1;
} 

void UGRAPHinsertE( Graph E, vertex v, vertex w) {
	GRAPHinsertA (E, v, w);
	GRAPHinsertA (E, w, v);
}

void GRAPHshow (Graph G) {
	vertex v; link a;
	for (v = 0; v < G->V; v++) {
		printf ("%2d: ", v); 
		for (a = G->adj[v]; a != NULL; a = a->next) 
			printf(" %2d", a->w);	
	    printf("\n");			
	 }
}

Graph GRAPHreverse( Graph G) {
	vertex v, w; Graph R_G;
	R_G = GRAPHinit(G->V);
	for (v = 0; v < G->V; v++) 
		for (link a = G->adj[v]; a != NULL; a = a->next) 
			GRAPHinsertA( R_G, a->w, v);
	return R_G;
}

static void dfsRcc( UGraph G, int *cc,
                    vertex v, int id) 
{ 
	link a; 
    cc[v] = id;
    for (a = G->adj[v]; a != NULL; a = a->next)
    	if (cc[a->w] == -1) 
    		dfsRcc( G, cc, a->w, id); 
}

int UGRAPHcc( UGraph G, int *cc) { 
	vertex v; int id = 0;
    for (v = 0; v < G->V; ++v) 
    	cc[v] = -1;
    for (v = 0; v < G->V; ++v)
        if (cc[v] == -1) 
        	dfsRcc( G, cc, v, id++);
    return id;
}

void UGRAPHinsertCC( UGraph G, vertex v, vertex w) {
	int cc[50];
	UGRAPHinsertE( G, v, w);
	printf("\nCC Insert = %d", UGRAPHcc(G, cc));
	printf("\nCC : ");
	for( int i = 0; i < G->V; i++) 
    	printf("%2d ", cc[i]);
}

static void dfsR( Graph G, vertex v) {
	vertex w;
	pre[v] = cnt++;
	for( link a = G->adj[v]; a != NULL; a = a->next) 
		if (pre[a->w] == -1) {
			dfsR( G, a->w);
		}
	post[v] = cnt1++;

}

void GRAPHdfs( Graph G) {
	vertex v;
	cnt = 0, cnt1 = 0;
	for( v = 0; v < G->V; ++v) 
		pre[v] = -1;
	for( v = 0; v < G->V; ++v) 
		if (pre[v] == -1) 
			dfsR(G, v);
}

bool GRAPHhasCycle( Graph G) {
	vertex v, w; link a;
    GRAPHdfs( G);
    for (v = 0; v < G->V; ++v) {
    	for (a = G->adj[v]; a != NULL; a = a->next) {
    		w = a->w;
            if (post[v] < post[w]) return True;
        }
    } 
    return False;
}

static void reachR( Graph G, vertex v) { 
	visit[v] = 1;
    for (link a = G->adj[v]; a != NULL; a = a->next) 
    	if (visit[a->w] == 0)
    		reachR( G, a->w);
}

bool GRAPHreach( Graph G, vertex s, vertex t) {
	for (vertex v = 0; v < G->V; ++v)
		visit[v] = 0;
    reachR( G, s);
    if (visit[t] == 0) return False;
    else return True;
}

bool GRAPHccG( Graph G) {
	vertex w;
	for( vertex v; v < G->V; ++v) 
		for( link a = G->adj[v]; a != NULL; a = a->next) {
			w = a->w;
			if( GRAPHreach( G, v, w) !=GRAPHreach(G, w, v)) return False;
		}
	return True;
}

/*int GRAPHcc( Graph G, int *cc) {
	vertex v, w; int nc = 0;
	Fila f = CriaFila();
	for( v = 0; v < G->V; ++v) 
		for( link a = G->adj[v]; a != NULL; a = a->next) 
			if( GRAPHreach(G, v, w) != GRAPHreach(G, v, w)) {
				
			}
			
	return nc;
} */

bool isTopoNumering (Graph G, int topo[]) {
	vertex v;
	for (v = 0; v < G->V; v++) 
		for (link a = G->adj[v]; a != NULL; a = a->next) 
			if (topo[v] >= topo[a->w]) 
				return False;
	return True;
} 

//int GRAPHTop

void GRAPHtopological( Graph G) {
	Pilha p = CriaPilha();
	GRAPHindeg( G);
	for( int i = 0; i < G->V; ++i) 
		if( topo[i] == 0) {
			Empilha( p, topo[i]);	
			topo[i] = -1;
		}
	for( link a = G->adj[Desempilha(p)]; a != NULL; a = a->next) {
		topo[a->w] -= 1;
		for( int i = 0; i < G->V; ++i) 
			if( topo[i] == 0) 
				Empilha( p, topo[i]);	
		if( PilhaVazia(p)) return;
	}	 
}



int main() {
	
	Graph F = GRAPHinit( 13);
    GRAPHinsertA(F, 0, 1);
	GRAPHinsertA(F, 0, 5);
	GRAPHinsertA(F, 2, 0);
	GRAPHinsertA(F, 2, 3);
	GRAPHinsertA(F, 3, 2);
	GRAPHinsertA(F, 3, 5);
	GRAPHinsertA(F, 4, 2);
	GRAPHinsertA(F, 4, 3);
	GRAPHinsertA(F, 5, 4);
	GRAPHinsertA(F, 6, 0);
	GRAPHinsertA(F, 6, 4); 
	GRAPHinsertA(F, 6, 9); 
	GRAPHinsertA(F, 7, 6); 
	GRAPHinsertA(F, 7, 8); 
	GRAPHinsertA(F, 8, 7); 
	GRAPHinsertA(F, 8, 9); 
	GRAPHinsertA(F, 9, 10); 
	GRAPHinsertA(F, 9, 11); 
	GRAPHinsertA(F, 10, 12); 
	GRAPHinsertA(F, 11, 4); 
	GRAPHinsertA(F, 11, 12);
	GRAPHinsertA(F, 12, 9);  
    GRAPHshow(F);  
    printf("\n");  
	
 /*   Graph F = GRAPHinit( 13);
    UGRAPHinsertE(F, 0, 1);
	UGRAPHinsertE(F, 0, 2);
	UGRAPHinsertE(F, 0, 5);
	UGRAPHinsertE(F, 0, 6);
	UGRAPHinsertE(F, 3, 4);
	UGRAPHinsertE(F, 3, 5);
	UGRAPHinsertE(F, 4, 5);
	UGRAPHinsertE(F, 4, 6);
	UGRAPHinsertE(F, 7, 8);
	UGRAPHinsertE(F, 9, 10);
	UGRAPHinsertE(F, 9, 11);
	UGRAPHinsertE(F, 9, 12);
	UGRAPHinsertE(F, 11, 12);
	GRAPHshow(F);  
	
	Graph F = GRAPHinit( 10);
	GRAPHinsertA(F, 0, 1);
	GRAPHinsertA(F, 0, 6);
	GRAPHinsertA(F, 1, 2);
	GRAPHinsertA(F, 1, 4);
	GRAPHinsertA(F, 1, 5);
	GRAPHinsertA(F, 2, 3);
	GRAPHinsertA(F, 3, 4);
	GRAPHinsertA(F, 4, 1);
	GRAPHinsertA(F, 6, 7);
	GRAPHinsertA(F, 6, 9);
	GRAPHinsertA(F, 7, 8); 
    GRAPHshow(F);  */
    
    int cc[50];
/*    printf("\nConect Componets = %d\n", UGRAPHcc(F, cc));
    
    printf("\nCC : ");
    for( int i = 0; i < F->V; i++) 
    	printf("%2d ", cc[i]); */
//    UGRAPHinsertCC( F, 0, 7);
 //   if( GRAPHhasCycle(F)) printf("\n\nHas Cicly is True\n");
//    else printf("\n\nHas Ciclo is False\n");
    Graph R_F = GRAPHreverse( F);
    GRAPHshow( F);  
    printf("\n");  
    GRAPHreach( R_F, 0, 11);
    GRAPHdfs( F);
    printf("\nV   :");
    for( int i = 0; i < F->V; i++) 
		printf("%2d ", i);
    printf("\nPre :");
    for( int i = 0; i < F->V; i++) 
		printf("%2d ", pre[i]);
    printf("\nPos :");
    for( int i = 0; i < F->V; i++) 
		printf("%2d ", post[i]);
    printf("\nVis :");
    for( int i = 0; i < F->V; i++) 
		printf("%2d ", visit[i]);
    if( GRAPHccG(F)) printf("\n\nHas strongly connect is True\n");
    else printf("\n\nHas strongly connect is False\n\n");

}
