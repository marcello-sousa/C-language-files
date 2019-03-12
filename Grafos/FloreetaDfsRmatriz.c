#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//typedef enum {FALSE, TRUE} boolean;
static int visit[1000], cnt, cnt1;
int pre[1000], parent[1000], post[1000], inSource[1000];
#include "pilha.h"
#include "pilha.c"
#define UGraph Graph

typedef int vertex;
#define MAX 20

struct graph {
	int V;
	int A;
	int **adj;
};

typedef struct graph *Graph;

static int **MATRIXint (int r, int c, int val) {
	vertex i, j; 
	int **m = malloc(r*sizeof(int *));
	for (i = 0; i < r; i++) 
		m[i] = malloc(c*sizeof(int));
	for (i = 0; i < r; i++) 
		for(j = 0; j < c; j++) 
			m[i][j] = val;	     
	return m;	
}

Graph GRAPHinit (int V) {
	Graph G = malloc(sizeof*G);
	G->V = V;
	G->A = 0;
	G->adj = MATRIXint(V, V, 0); 
	return G;
}
	
void GRAPHinsertA (Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}

void UGRAPHinsertE (Graph E, vertex v, vertex w) {
	GRAPHinsertA (E, v, w);
	GRAPHinsertA (E, w, v);
} 

void GRAPHremoveA (Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

void UGRAPHremoveE (Graph E, vertex v, vertex w) {
	GRAPHremoveA (E, v, w);
	GRAPHremoveA (E, w, v);
}

void GRAPHshow (Graph G) { 
   vertex v, w; 
   for (v = 0; v < G->V; v++) {
      printf( "%2d:", v);
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1) 
            printf( " %2d", w);
      printf( "\n");
   }
}

Graph GRAPHreverse (Graph G) {
	vertex v, w; Graph R_G;
	R_G = GRAPHinit(G->V);
	for (v = 0; v < G->V; v++) 
		for (w = 0; w < G->V; w++) 
			R_G->adj[w][v] = G->adj[v][w];
	return R_G;
}

int GRAPHindeg( Graph G, vertex w) {
	vertex v; int indeg = 0;
	for( v = 0; v < G->V; v++) 
		if( G->adj[v][w] == 1) 
			indeg++;
	return indeg;
}

int GRAPHoutdeg (Graph G, vertex v) {
	vertex w; int outdeg = 0;
	for (w = 0; w < G->V; w++) 
		if (G->adj[v][w] == 1) 
			outdeg++;
	return outdeg;
}

int GRAPHisSource( Graph G) {
	vertex w; int inSink[MAX], i = 0;
	for (w = 0; w < G->V; w++) 
		if( GRAPHindeg(G, w) == 0 && GRAPHoutdeg(G, w) > 0)
			inSource[i++] = w;
	return i;
}

static void dfsR (Graph G, vertex v, vertex t) {
	vertex w;
	pre[v] = cnt++;
	if (pre[t] != -1) return;
	for( w = 0; w < G->V; ++w)    
		if (G->adj[v][w] == 1 && pre[w] == -1) {
			if (pre[t] != -1) break;
			printf("%d-> ", w);
	   //     parent[w] = v;
			dfsR(G, w, t);			
	    }  
}

static void dfsRA(Graph G, vertex v) {
	vertex w;
	pre[v] = cnt++;
	for( w = 0; w < G->V; ++w)    
		if (G->adj[v][w] == 1 && pre[w] == -1) {
	        parent[w] = v;
			dfsRA(G, w);
	    }
	post[v] = cnt++;  
}

void GRAPHdfsA( Graph G) {
	vertex v;
	cnt = 0, cnt1 = 0;
	for (v = 0; v < G->V; ++v) 
		pre[v] = -1;
	for (v = 0; v < G->V; ++v) 
		 if (pre[v] == -1) {
		 	parent[v] = v;
	        dfsRA( G, v);
	     }
}

void GRAPHPathdfs( Graph G, vertex s, vertex t) {
	vertex v;
	cnt = 0;
	for (v = 0; v < G->V; ++v) 
		pre[v] = -1;
	printf("\nPath : %d-> ", s);
	for (v = 0; v < G->V; ++v) 
		 if (pre[v] == -1 && v == s) {
		//	parent[v] = v;
	        dfsR( G, v, t);
	     }
}

void PathDfs( Graph G, vertex s, vertex t) {
	Pilha p;
	p = CriaPilha();
	vertex v, w;
	GRAPHdfsA( G);
	for( v = 0; v < G->V; v++) 
		if( v == t) {			
			w = v;
			Empilha(p, t);
			while( parent[w] != s && parent[w] != w) {
				Empilha(p, parent[w]);		
			    w = parent[w];  
		    }
		    Empilha(p, s);
		}
    printf("\nPathS: ");
	while (!PilhaVazia(p)) 
		printf("%d-> ", Desempilha(p));
} 

bool GRAPHreachI( Graph G, vertex s, vertex t) {
	vertex v, w;
	int fila[MAX], p = 0, u = 1;
	for( v = 0; v < G->V; ++v) 
		visit[v] = 0;
	fila[0] = s;
	while (p != u) {
		v = fila[p++];
		for( w = 0; w < G->V; ++w) 
			if (G->adj[v][w] == 1 && visit[w] != 1) {
				visit[w] = 1;
				fila[u++] = w;
	         }
	}
	if (visit[t] == 1) return True;
	else return False;
}

void reachR( Graph G, vertex v) {
	vertex w;
	visit[v] = 1;
    for( w = 0; w < G->V; ++w) 
    	if( G->adj[v][w] == 1 && visit[w] == 0)
    		reachR( G, w);	
}

bool GRAPHreach( Graph G, vertex s, vertex t){ 
	for (vertex v = 0; v < G->V; ++v)
		visit[v] = 0;
    reachR( G, s);
    if (visit[t] == 0) return False;
    else return True;
}

bool UGRAPHisConnected( Graph G) {
	vertex v, w;
	for( v = 0; v < G->V; ++v) 
		visit[v] = 0;
	reachR( G, 0);
	for( v = 0; v < G->V; ++v) 
		if( visit[v] == 0) return False;
	return True;
}

Graph GRAPHisCycle1( Graph F) {
	vertex v, w; int nf, i;
	nf = GRAPHisSource( F);
	if( nf != 0) 
		for( i = 0; i < nf; ++i) {
			v = inSource[i];
			for( w = 0; w < F->V; ++w) 
				if( F->adj[v][w] == 1) {
					GRAPHremoveA( F, v, w);
					GRAPHisCycle1( F);
				}
		}
	return F;
}

Graph GRAPHisCycle2( Graph F) {
	vertex v, w; int nf, i;
	nf = GRAPHisSource( F);
	if( nf != 0) 
		for( i = 0; i < nf; ++i) {
			v = inSource[i];
			for( w = 0; w < F->V; ++w) 
				if( F->adj[v][w] == 1) {
					GRAPHremoveA( F, v, w);
					GRAPHisCycle1( F);
				}
		}
	return F;
}

Graph GRAPHisCycle( Graph F, vertex v) {
	while( v < F->V) {
		vertex w = 0;		
		while (w < F->V) {		 	
			if( F->adj[v][w] == 1 && GRAPHoutdeg( F, v) > 0 && GRAPHindeg( F, v) == 0) {	
				GRAPHremoveA( F, v, w);
				GRAPHisCycle( F, v); 
			 }
		++w;
		}
	++v;
	}
	return F;
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
/*    Graph F = GRAPHinit( 7);
	GRAPHinsertA(F, 0, 1);
	GRAPHinsertA(F, 1, 2);
	GRAPHinsertA(F, 2, 3);
	GRAPHinsertA(F, 3, 5);
	GRAPHinsertA(F, 3, 6);
	GRAPHinsertA(F, 3, 4);
	GRAPHinsertA(F, 4, 2);
	GRAPHinsertA(F, 5, 6);
	GRAPHinsertA(F, 6, 1);
	GRAPHshow(F);  */
	
/*	Graph F = GRAPHinit(6);
	GRAPHinsertA(F, 0, 1);
	GRAPHinsertA(F, 1, 2);
	GRAPHinsertA(F, 2, 3);
	GRAPHinsertA(F, 3, 4);
	GRAPHinsertA(F, 4, 5);
	GRAPHinsertA(F, 5, 0);
	GRAPHshow( F); 
	
	Graph F = GRAPHinit( 13);
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
	GRAPHshow(F); */
	
/*    PathDfs(F, 0, 3);  
	printf("\n");
    GRAPHPathdfs(F, 0, 3);
    printf("\n\nDFS Forest\n");
    GRAPHdfsA(F); */
    
/*	printf("\nPre : "); 
	for( int i = 0; i < F->V; i++) 
		printf("%2d ", pre[i]); 
    printf("\nPost: ");
    for( int i = 0; i < F->V; i++) 
		printf("%2d ", post[i]);
    printf("\n\n"); 
    if( UGRAPHisConnected(F)) printf("Is connected");
    else printf("Is Not connected");
    printf("\nVisit: ");
    for( int i = 0; i < F->V; i++) 
		printf("%2d ", visit[i]);
    F = GRAPHisCycle1( F);
    printf("\n\n"); */
    GRAPHdfsA(F);
 /*   printf("\n P: ");
    for( int i = 0; i < F->V; i++) 
		printf("%2d ", post[i]); */
    Graph R_F = GRAPHreverse(F);
    printf("\n");
    GRAPHshow(R_F);
    GRAPHdfsA(F);
    if (GRAPHreach(F, 0, 6)) printf ("\nReach: True\n");
    else printf("\nReach: False\n");
    printf("\n V: ");
	for( int i = 0; i < F->V; i++) 
		printf("%2d ", i); 
    printf("\nPa: ");
	for( int i = 0; i < F->V; i++) 
		printf("%2d ", pre[i]); 
    printf("\nPO: ");
	for( int i = 0; i < F->V; i++) 
		printf("%2d ", post[i]); 
    printf("\n\n"); 
}
