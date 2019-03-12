#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int vertex;
typedef enum {FALSE, TRUE} boolean;
static int visit[1000];
int pre[1000];
static int cnt;
#define UGraph Graph

/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */

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

void GRAPHremove (Graph G, vertex v, vertex w) {
	link a = G->adj[v];
	while (a->next != NULL && a->w != w) 
		a = a->next;
	printf ("%d \n\n", a->w);
	if (a != NULL && a->w == w) {
		link aux = a->next;
		free(a);
		a = aux;
		G->A--;
	}
}

int GRAPHoutdeg (Graph G, vertex v) {
	link a; int g_out = 0;
	for (a = G->adj[v]; a != NULL; a = a->next) 
		g_out++;
	return g_out;	
}

int GRAPHindeg (Graph G, vertex w) {
	vertex v; link a; int g_in = 0;
	for (v = 0; v < G->V; v++) {
		for (a = G->adj[v]; a != NULL; a = a->next) 
			if (a->w == w) g_in++;	
	}
	return g_in;
}

Graph GRAPHcopy (Graph G) {
	Graph c_G; link a; vertex v, w;
	c_G = GRAPHinit(G->V);
	for (v = 0; v < G->V; v++) 
		for (a = G->adj[v]; a != NULL; a = a->next) 
	        GRAPHinsertA(c_G, v, a->w);
	return c_G;
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

/*Grafos topologicos / floresta e arvores radicadas */

boolean isTopoNumering (Graph G, int topo[]) {
	vertex v;
	for (v = 0; v < G->V; v++) 
		for (link a = G->adj[v]; a != NULL; a = a->next) 
			if (topo[v] >= topo[a->w]) 
				return FALSE;
	return TRUE;
} 

boolean isRootedForest( Graph G, int topo[]) {
    if (!isTopoNumering( G, topo)) 
    	return FALSE;
    for (vertex v = 0; v < G->V; ++v)
        if (GRAPHindeg(G, v) > 1)
        	return FALSE;
   // ineficiente...
    return TRUE;
}

boolean isRootedTree( Graph G, int topo[]) {
    if (!isRootedForest( G, topo))
    	return FALSE;
    int roots = 0;
    for (vertex v = 0; v < G->V; ++v) {
        if (GRAPHindeg(G, v) == 0) {
        	roots++;
            if (roots > 1) return FALSE;
        }
    }
   // ineficiente...
    return TRUE;
}

Graph GRAPHinsertForest( int p[], int n) {
	Graph G = GRAPHinit( n);
	for( int i = 0; i < n; i++) 
		 if (p[i] != i)
			GRAPHinsertA( G, p[i], i);
	return G;
}

void GRAPHpathForest( int p[], int n, vertex w) {
	int path[10], j = 0, i;
	for( i = 0; i < n; i++) { 
		if( w == i) 
			while( p[i] != i) {
				path[j] = p[i];
				i = p[i]; j++;
	        }
	}	
    for(i = j - 1; i >= 0; i--)
		printf(" %d ->", path[i]); 
}

int GRAPHdepthForest( int p[], int n, vertex w) {
	int count = 0;
	for( int i = 0; i < n; i++) 
		if( w == i) 
			while( p[i] != i) {
				i = p[i]; 
				count++;
	        }
	return count;	
}

int GRAPHheightForest( Graph G, int p[], int n) {
	int height_max = 0, aux_max;
	for( vertex v = 0; v < G->V; v++)
		for( link a = G->adj[v]; a != NULL; a = a->next) 
			if( GRAPHoutdeg( G, a->w) == 0 && GRAPHindeg( G, a->w) > 0) {
				aux_max = GRAPHdepthForest( p, n, a->w); 
				if( aux_max > height_max) 
					height_max = aux_max;	
			}		
	return height_max;
} 

vertex randV( Graph G) {
	double r;
	r = rand() / (RAND_MAX + 1.0);
	return r*G->V;
}

Graph GRAPHbuildRandRootedTree ();

static void reachR( Graph G, vertex v) {
	visit[v] = 1;
	for( link a = G->adj[v]; a != NULL; a = a->next) 
		if( visit[a->w] == 0) 
			reachR(G, a->w);
}

static void reachR( Graph G, vertex v, vertex t) {	
	visit[v] = 1;
	if (visit[t] == 1) return;
	for( link a = G->adj[v]; a != NULL; a = a->next) 
		if( visit[a->w] == 0) 
			reachR(G, a->w, t);
} 

boolean GRAPHreach (Graph G, vertex s, vertex t) {
	for ( vertex v = 0; v < G->V; ++v)
      visit[v] = 0;
    reachR( G, s, t);
    if (visit[t] == 0) return FALSE;
    else return TRUE;
} 

static void dfsR( Graph G, vertex v) {
	vertex w;
	pre[v] = cnt++;
	for( link a = G->adj[v]; a != NULL; a = a->next) 
		if (pre[a->w] == -1) {
			dfsR( G, a->w);
		}
}

void GRAPHdfs( Graph G) {
	vertex v;
	cnt = 0;
	for( v = 0; v < G->V; ++v) 
		pre[v] = -1;
	for( v = 0; v < G->V; ++v) 
		if (pre[v] == -1) 
			dfsR(G, v);
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


int main () {
/*	Graph g, c_g; int v = 6;
	g = GRAPHinit(6);
	GRAPHinsertA(g, 2, 4);
	GRAPHinsertA(g, 5, 3);
	GRAPHinsertA(g, 1, 5);
	GRAPHinsertA(g, 4, 2);
	GRAPHinsertA(g, 3, 5);
	printf("\n");
	GRAPHshow(g);	
	printf("\n");
	printf ("outdeg = %d\n", GRAPHoutdeg(g, 1));
	printf ("indeg = %d\n", GRAPHindeg(g, 5));
	c_g = GRAPHcopy(g);
	printf("\n");
    GRAPHshow(c_g); */
    printf("\n");
/*    int p[20] = {5, 5, 0, 0, 4, 4, 11, 11, 7, 7, 7, 11};
    Graph F = GRAPHinsertForest( p, 12); */
    Graph F = GRAPHinit( 6);
    GRAPHinsertA(F, 0, 1);
	GRAPHinsertA(F, 0, 4);
	GRAPHinsertA(F, 2, 0);
	GRAPHinsertA(F, 2, 3);
	GRAPHinsertA(F, 3, 4);
	GRAPHinsertA(F, 3, 5);
	GRAPHinsertA(F, 4, 1);
	GRAPHinsertA(F, 4, 5);
	GRAPHinsertA(F, 5, 1); 
   /* GRAPHinsertA(F, 0, 1);
	GRAPHinsertA(F, 0, 4);
	GRAPHinsertA(F, 1, 2);
	GRAPHinsertA(F, 1, 5);
	GRAPHinsertA(F, 2, 3);
	GRAPHinsertA(F, 3, 7);
	GRAPHinsertA(F, 4, 8);
	GRAPHinsertA(F, 5, 4);
	GRAPHinsertA(F, 6, 5);
	GRAPHinsertA(F, 6, 10);
	GRAPHinsertA(F, 6, 2);
	GRAPHinsertA(F, 7, 11);
	GRAPHinsertA(F, 7, 6);
	GRAPHinsertA(F, 8, 9);
	GRAPHinsertA(F, 9, 5);
	GRAPHinsertA(F, 9, 8);
	GRAPHinsertA(F, 10, 9);
	GRAPHinsertA(F, 11, 10);
    GRAPHshow(F);
    printf("\n");
    printf("Depth = %d ", GRAPHdepthForest(F, 12, 9));
    printf("\nHeight = %d ", GRAPHheightForest(F, p, 12)); 
    printf("\n\nReach = %s", GRAPHreach(F, 0, 9)? "True":"False");
    printf("\n"); */
    vertex v;
    GRAPHreach(F, 0, 1); 
    printf("\nDFS:  ");
    for (v = 0; v < F->V; ++v) 
    	printf("%2d ", v);  
    printf("\nPre:  ");
    for (v = 0; v < F->V; ++v) 
    	printf("%2d ", visit[v]);  
 /*   vertex v;
    GRAPHdfs(F);
    GRAPHshow(F);
    printf("\nDFS:  ");
    for (v = 0; v < F->V; ++v) 
    	printf("%2d ", v);  
    printf("\nPre:  ");
    for (v = 0; v < F->V; ++v) 
    	printf("%2d ", pre[v]);  */

	return 0;	
}
