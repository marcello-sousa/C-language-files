#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#define L 480 
#define C 640

struct Vertice {
	float x;
    float y;
    struct Vertice *prox;
};

typedef struct Vertice *Poligono;

Poligono AlocaCabeca () {
	Poligono cabeca;
	cabeca = malloc(sizeof(cabeca));
	cabeca->x = 1;
	cabeca->prox = cabeca;
	return cabeca;
}

void InserePoligono (Poligono P, float X, float Y) {
	Poligono novo;	
    novo = malloc(sizeof(novo));
    novo->x = X;
    novo->y = Y;
    novo->prox = P->prox;
    P->prox = novo;
}	

int NumeroDeVertices(Poligono p) {
	Poligono q = p->prox; int n = 0;
	while (q != p) {
		n++; q = q->prox; 
	}
	return n;
}

int **AlocaMatriz () {
	int i, j, **M;
	M = (int **)malloc(L*sizeof(int *)); 
	for (i = 0; i < L; i++) {
		M[i] = (int *)malloc(C*sizeof(int));
	  	for (j = 0; j < C; j++) {
	  		M[i][j] = 255;
	  	}
	}
	return M;
}	

Poligono DesenhaKoch(Poligono P) {
	int **m, i, j;
	m = AlocaMatriz();
	
}

void DrawLine(int **M, int m, int n, int x1, int y1, int x2, int y2, int val){
	float x,y,dx,dy;
    int xi,yi;
    dx = (x2-x1);
    dy = (y2-y1);
    if(fabsf(dx) > fabsf(dy)) {
    	dy = dy/(fabsf(dx));
        dx = dx/(fabsf(dx));
    }
    else {
        dx = dx/(fabsf(dy));
        dy = dy/(fabsf(dy));
    }
    x = (float)x1;
    y = (float)y1;
    xi = x1;
    yi = y1;
    while(xi != x2 || yi != y2) {
    	if(yi >= 0 && yi < m && xi >= 0 && xi < n) 
    		M[yi][xi] = val;
    x += dx;
    y += dy;
    xi = (int)(x + 0.5);
    yi = (int)(y + 0.5);
    }
    if(y2 >= 0 && y2 < m && x2 >= 0 && x2 < n)
    	M[y2][x2] = val;
}

int **AlocaMatriz () {
	int i, j, **M;
	M = (int **)malloc(L*sizeof(int *)); 
	for (i = 0; i < L; i++) {
		M[i] = (int *)malloc(C*sizeof(int));
	  	for (j = 0; j < C; j++) {
	  		M[i][j] = 255;
	  	}
	}
	return M;
}	

void GravaImagem (int **M) {
	FILE *f; 
	int i, j;
	f = fopen ("levy.txt", "wt");
	if (f == NULL) { 
		perror ("problema ao abrir o arquivo");
		return;
	}
	for (i = 0; i < L; i++) 
		for (j = 0; j < C; j++) 
			fprintf(f, "%d ", M[i][j]);			
}


int main () {
	Poligono p, aux; 
	int **pol, i, j, n, inter;
	float xn, yn;	
	p = AlocaCabeca();
	
	
	return 0;
}
