#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum {FALSE, TRUE} boolean;
static int visit[1000], cnt;
int pre[1000];

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

void GRAPHremoveA (Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
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

int GRAPHindeg (Graph G, vertex w) {
	vertex v; int indeg = 0;
	for (v = 0; v < G->V; v++) 
		if (G->adj[v][w] == 1) 
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

void GRAPHisSink (Graph G) {
	vertex w; int inSink[MAX];
	for (w = 0; w < G->V; w++) {
		if( GRAPHindeg(G, w) > 0 && GRAPHoutdeg(G, w) == 0) inSink[w] = 1;
	    else inSink [w] = 0;
	}
}

Graph GRAPHcopy (Graph G) {
	Graph C_G; vertex v, w;
	C_G = GRAPHinit(G->V);
	for (v = 0; v < G->V; v++) 
		for (w = 0; w < G->V; w++) 
			C_G->adj[v][w] = G->adj[v][w];
	return C_G;
}

int GRAPHisolated (Graph G, vertex v) {
	if (GRAPHindeg(G, v) != 0 || GRAPHoutdeg(G, v != 0)) return 0;
	else return 1;	
}

Graph GRAPHreverse (Graph G) {
	vertex v, w; Graph R_G;
	R_G = GRAPHinit(G->V);
	for (v = 0; v < G->V; v++) 
		for (w = 0; w < G->V; w++) 
			R_G->adj[w][v] = G->adj[v][w];
	return R_G;
}

int GRAPHequal (Graph G, Graph H) {
	vertex v, w; 
	for (v = 0; v < G->V; v++) 
		for (w = 0; w < G->V; w++) 
			if (H->adj[v][w] != G->adj[v][w]) return 0;
	return 1;	
}

int GRAPHcheck (Graph G) {
	vertex v, w;
	for (v = 0, w = 0; v < G->V; v++, w++)
			if (G->adj[v][w] != 0) return 0;
	return 1;			
}

int isTournament (Graph G) {
	vertex v, w;
	for (v = 0; v < G->V; v++) 
		for (w = 0; w < v; w++) 
			if (G->adj[v][w] == 1) 
				if (G->adj[v][w] == G->adj[w][v]) return 0;
	return 1;		
}

/* funcion of graphs undirected */

int GRAPHisUndirected (Graph G) {
	vertex v, w;
	for (v = 0; v < G->V; v++) 
		for (w = 0; w < v; w++) 
			if (G->adj[v][w] == 1) 
				if (G->adj[v][w] != G->adj[w][v]) return 0;
	return 1;		
}

void UGRAPHinsertE (Graph E, vertex v, vertex w) {
	GRAPHinsertA (E, v, w);
	GRAPHinsertA (E, w, v);
} 

void UGRAPHremoveE (Graph E, vertex v, vertex w) {
	GRAPHremoveA (E, v, w);
	GRAPHremoveA (E, w, v);
} 

void UGRAPHdegress (Graph E, int Grau[]) {
	vertex v, w; int i = 0;
	for (v = 0; v < E->V; v++) {
	    Grau[i] = GRAPHoutdeg(E, v); 
	    i++;
	}
}

/*Capitulo 3 - contrutores de grafos ex1 */
	
void GRAPHbuildPath (Graph G) {
	vertex v, w;
	for (v = 0, w = 1; v < G->V; v++, w++) 
		GRAPHinsertA (G, v, w);
}	
	
void GRAPHbuildCycle (Graph G) {
	vertex v, w;
	for (v = 0, w = 1; v < G->V; v++, w++) 
	    if (v == G->V - 1) GRAPHinsertA (G, v, 0);
	    else GRAPHinsertA (G, v, w);
}

void GRAPHtwo_two (Graph G) {
	vertex v, w;
	for (v = 0, w = 2; v < G->V; v++, w++) {
		if (w == G->V) w = 0;
	    GRAPHinsertA (G, v, w);
	}	
}

void UGRAPHknight (int V, vertex v, vertex w) {
	Graph G = GRAPHinit(V);
	
} 

/*Capitulo 3 - contrutores de grafos ex2 */

/*void GRAPHtoundirected (Graph G) {
	vertex v, w;
	for (v = 0; v < G->V; v++) 
		for (w = 0; w < v; w++) 
			
	
} */

/*Capitulo 4 */

vertex randV( Graph G) {
	double r;
	r = rand() / (RAND_MAX + 1.0);
	return r*G->V;
}

Graph GRAPHrand1 (int V, int A) {
	Graph G = GRAPHinit( V);
	while (G->A < A) {
		vertex v = randV( G);
		vertex w = randV( G);
		if (v != w) 
			GRAPHinsertA(G, v, w);
	}
	return G;
}

Graph GRAPHrand2( int V, int A) { 
    double prob = (double) A / V / (V-1);
    Graph G = GRAPHinit( V);
    for (vertex v = 0; v < V; ++v)
       for (vertex w = 0; w < V; ++w)
          if (v != w)
             if (rand( ) < prob*(RAND_MAX + 1.0))    
                GRAPHinsertA( G, v, w); 
   return G;
}

Graph ArvoreRadicada1( int V) {
	vertex v, w; 
	Graph G = GRAPHinit( V);
	for (w = 2; w < G->V; w++) {
		v = 0 + rand() % (w - 1);		
		GRAPHinsertA( G, v, w);
	}
	return G;
}

Graph ArvoreRadicada2( int V, int k) {
	vertex v, w;
	Graph G = GRAPHinit( V);
	for (v = 0; v < G->V; v++) {
		w = (v + 1) + rand() % (v + k);
		printf("%d ", w);
		GRAPHinsertA( G, v, w);           
	}
	return G;	
}

int GRAPHcheckPath( int seq[], int n) {
	vertex v, w, i, j;
	for (v = 0, w = 1; w < n; v += 1, w += 1)
		for (i = w, j = w + 1; j < n; i += 1, j += 1) 
			if (seq[i] == seq[v] && seq[j] == seq[w]) return 0; 
	return 1;	
}

int GRAPHcheckSimplePath( int seq[], int n) {
	vertex v, w;
	for (v = 0; v < n; v++) 
		for (w = v + 1; w < n; w++) {
			if (seq[v] == seq[w]) {
				if (GRAPHcheckPath(seq, n)) return 0;
				else return -1;
			}		
		}
	return 1;
}

static void reachR( Graph G, vertex v, vertex t) { 
    visit[v] = 1;  
    for (vertex w = 0; w < G->V; ++w) 
    	if (G->adj[v][w] == 1 && visit[w] == 0){
            if (visit[t] == 1) return;
    		reachR( G, w, t);
        }
}

boolean GRAPHreach( Graph G, vertex s, vertex t) {
	for (vertex v = 0; v < G->V; ++v)
      visit[v] = 0;
    reachR( G, s, t);
    if (visit[t] == 0) return FALSE;
    else return TRUE;
}

boolean GRAPHreachI( Graph G, vertex s, vertex t) {
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
	if (visit[t] == 1) return TRUE;
	else return FALSE;
}

static void dfsR( Graph G, vertex v) { 
   vertex w;
   pre[v] = cnt++; 
   for (w = 0; w < G->V; ++w)
      if (G->adj[v][w] != 0 && pre[w] == -1)
         dfsR( G, w); 
}

void GRAPHdfs( Graph G) { 
   vertex v;
   cnt = 0;
   for (v = 0; v < G->V; ++v) 
      pre[v] = -1;
   for (v = 0; v < G->V; ++v)
      if (pre[v] == -1) 
         dfsR( G, v); // começa nova etapa
}

int main () {
	/*srand((unsigned) time(NULL));
	time_t to, tf;
	double tempo_total;
	to = time(NULL);
	Graph G_r1 = GRAPHrand1( 200, 400);
	tf = time(NULL);
	tempo_total = difftime(tf, to);
	printf("Rand1 T = %.2lf s", tempo_total);
	to = time(NULL);
	Graph G_r2 = GRAPHrand2( 200, 400);
	tf = time(NULL);
	tempo_total = difftime(tf, to);
	printf("\nRand2 T = %.2lf s", tempo_total); */
/*	int seq[] = {1, 3, 7, 3, 7};
	printf ("%d ", GRAPHcheckSimplePath(seq, 5)); */
	int v;
	Graph F = GRAPHinit( 12);
    GRAPHinsertA(F, 0, 1);
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
    printf("\n\nReach = %s", GRAPHreach(F, 0, 2)? "True" : "False");
    GRAPHdfs(F);
    printf("\nDFS:  ");
    for (v = 0; v < F->V; ++v) 
    	printf("%2d ", v);  
    printf("\nPre:  ");
    for (v = 0; v < F->V; ++v) 
    	printf("%2d ", visit[v]);  
    
    return 0;
}
