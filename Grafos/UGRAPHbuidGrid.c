#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef int vertex;

typedef struct node *linki;
struct node { 
	vertex w; 
	linki next; 
};

struct graph {
	int V; 
    int A; 
    linki *adj; 
};

typedef struct graph *Graph;

static linki NEWnode( vertex w, linki next) { 
   linki a = malloc( sizeof (linki));
   a->w = w; 
   a->next = next;     
   return a;                         
}

Graph GRAPHinit( int V) {
	vertex v;
	Graph G = malloc(sizeof*G);
	G->V = V;
	G->A = 0;
	G->adj = malloc(V*sizeof(linki));
	for (v = 0; v < V; v++) 
		G->adj[v] = NULL;
	return G;
}

void GRAPHinsertA( Graph G, vertex v, vertex w) {
	linki a;
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

void GRAPHshow (Graph G) {
	vertex v; linki a;
	for (v = 0; v < G->V; v++) {
		printf ("%2d: ", v); 
		for (a = G->adj[v]; a != NULL; a = a->next) 
			printf(" %2d", a->w);	
	    printf("\n");			
	 }
}

Graph GRAPHbuidGrid(int m, int n) {
	Graph G;
	G = GRAPHinit(m * n);
	for( vertex v = 0; v < G->V - 1; v++) {
		if((v + 1) % m != 0) GRAPHinsertA(G, v, v + 1);
		if( v + m < G->V) GRAPHinsertA(G, v, v + m);
	}	
	return G;
}

Graph UGRAPHbuidGrid(int m, int n) {
	Graph G;
	G = GRAPHinit(m * n);
	for( vertex v = 0; v < G->V - 1; v++) {
		if( (v + 1) % m != 0) UGRAPHinsertE(G, v, v + 1);
		if( v + m < G->V) UGRAPHinsertE(G, v, v + m);
	}	
	return G;
}

int main () {
	Graph G = GRAPHbuidGrid(4, 3);
	GRAPHshow(G);
	printf("\n");
//	Graph E = UGRAPHbuidGrid(4, 3);
//	GRAPHshow(E);
	return 0;
}
