#include <stdio.h>
#include <stdlib.h>
typedef int vertex;
int idade[100], visit[100];
typedef enum boolean {False, True} boolean;

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

int GRAPHoutdeg( Graph G, vertex v) {
	link a; int g_out = 0;
	for (a = G->adj[v]; a != NULL; a = a->next) 
		g_out++;
	return g_out;	
}

int GRAPHindeg( Graph G, vertex w) {
	vertex v; link a; int g_in = 0;
	for (v = 0; v < G->V; v++) {
		for (a = G->adj[v]; a != NULL; a = a->next) 
			if (a->w == w) g_in++;	
	}
	return g_in;
}

void Swap_Vertex( Graph G, vertex v, vertex w) {
	//link *a, *b, c;
	int troca; 
	/*a = &G->adj[v];
	b = &G->adj[w];
	c = *a;
	*a = *b;
	*b = c; */
	troca = idade[v];
	idade[v] = idade[w];
	idade[w] = troca;
}

static void reachR( Graph G, vertex v) { 
	visit[v] = 1;
    for (link a = G->adj[v]; a != NULL; a = a->next) 
    	if (visit[a->w] == 0)
    		reachR( G, a->w);
}

boolean GRAPHreach( Graph G, vertex s, vertex t) {
	for (vertex v = 0; v < G->V; ++v)
		visit[v] = 0;
    reachR( G, s);
    if (visit[t] == 0) return False;
    else return True;
}

int Procura_Gerente( Graph G, vertex w) {
	int menor = 150;
	if( GRAPHoutdeg( G, w) > 0 && GRAPHindeg( G, w) == 0) 
		return -1;
	else {
		for( vertex v = 1; v < G->V; ++v) 
			if( menor > idade[v] && GRAPHreach( G, v, w) == True) 
				menor = idade[v];				
	}
	return menor;
}

void GRAPHshow (Graph G) {
	vertex v; link a;
	for (v = 1; v < G->V; v++) {
		printf ("%2d: ", v); 
		for (a = G->adj[v]; a != NULL; a = a->next) 
			printf(" %2d", a->w);	
	    printf("\n");			
	 }
}

int main() {
	Graph G;
	int a, v, r; //arestas, vertices, relacoes
	vertex x, y, id;
	char acao;
	scanf("%d %d %d", &v, &r, &a);
	G = GRAPHinit(v + 1);
	for( int w = 1; w < G->V; w++) {
		printf("\nIdades: ");
	    scanf("%d", &id);
	    idade[w] = id;
	}
	for( int i = 0; i < r; ++i) {
		printf("\nArco %d: ", i);
		scanf("%d %d", &x, &y);
		GRAPHinsertA(G, x, y);
	}
	GRAPHshow( G);
	while( a > 0) {
		printf ("\nAcao: ");
		scanf("%c", &acao);
		switch(acao) {
			case 't': 
			    scanf("%d %d", &x, &y);
			    Swap_Vertex( G, x, y);
			    GRAPHshow( G);
			    break;			
			case 'p':
			    scanf("%d", &id);
			    int aux = Procura_Gerente( G, id);
			    if( aux == -1) printf("*\n");
			    else printf("%d\n", aux);
			    break;			
			default: continue;
		}
		a -= 1;
	}	
}
