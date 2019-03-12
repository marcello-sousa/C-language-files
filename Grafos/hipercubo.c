#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef int vertex;

typedef struct node *link;
struct node { 
	vertex w; 
	link next; 
};

struct graph {
   int V; 
   int A; 
   link *adj; 
};

typedef struct graph *Graph;

static link NEWnode( vertex w, link next) { 
   link a = malloc( sizeof (link));
   a->w = w; 
   a->next = next;     
   return a;                         
}

Graph GRAPHinit( int V) {
	vertex v;
	Graph G = malloc(sizeof*G);
	G->V = V;
	G->A = 0;
	G->adj = malloc(V*sizeof(link));
	for (v = 0; v < V; v++) 
		G->adj[v] = NULL;
	return G;
}

void GRAPHinsertA( Graph G, vertex v, vertex w) {
	link a;
	for (a = G->adj[v]; a != NULL; a = a->next) 
		if (a->w == w) return;
	G->adj[v] = NEWnode(w, G->adj[v]);
	G->A++;	
}

void UGRAPHinsertE( Graph E, vertex v, vertex w)
 {
	GRAPHinsertA (E, v, w);
	GRAPHinsertA (E, w, v);
}

int hamming_distance(unsigned x, unsigned y) {
    int dist = 0;
    unsigned val = x ^ y; 
    while (val != 0) {
        dist++;
        val &= val - 1;
    }
    return dist;
}

Graph UGRAPHbuildCube( int n) {
	Graph G;
	G = GRAPHinit(pow(2, n));
	for( int i = 0; i < G->V - 1; i++) 
		for( int j = i + 1; j < G->V; j++) 
			if( hamming_distance(i, j) == 1) 
				UGRAPHinsertE( G, i, j);	
	return G;
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

int main() {
	Graph E;
	E = UGRAPHbuildCube(3);
	GRAPHshow(E);
	return 0;
}
