#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#define L 480 
#define C 640

typedef const char *FILESPEC;

struct Vertice {
	float x;
    float y;
    struct Vertice *prox;
};

typedef struct Vertice Poligono;
/*
Poligono AlocaCabeca () {
	Poligono cabeca;
	cabeca = malloc(sizeof(cabeca));
	cabeca->prox = cabeca;
	return cabeca;
} */

void InserePoligono (Poligono **P, float X, float Y) {
	Poligono *novo, *q;
	q = *P;	
    novo = malloc(sizeof(novo));
    novo->x = X;
    novo->y = Y;
    if (q == NULL) {
    	novo->prox = novo;
    	*P = novo;
    } 
    else {
    novo->prox = q->prox;
    q->prox = novo;
    }
 /*  printf ("%f %f\n", novo->x, novo->y);  */
}	

int NumeroDeVertices(Poligono *p) {
	Poligono *q = p; int n = 0;
	while (q != p) {
		q = q->prox; n++;
	}
	return n;
}

Poligono *PoligonoPorPontoMedio(Poligono *p) {
	Poligono *q = NULL, *media = NULL; float xi, yi;
	q = p;
/*	media = AlocaCabeca(); */
	while (q != p) {
		xi = (q->x + q->prox->x)/2;
		yi = (q->y + q->prox->y)/2;
		InserePoligono(&media, xi, yi);
		q = q->prox;
		printf("%f \n", xi);
	}
	printf("\n");
	if (NumeroDeVertices(media) < 4)
		return NULL;
	else 
		return media;
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
	f = fopen ("imagem.txt", "wt");
	if (f == NULL) { 
		perror ("problema ao abrir o arquivo");
		return;
	}
	for (i = 0; i < L; i++) 
		for (j = 0; j < C; j++) 
			fprintf(f, "%d ", M[i][j]);			
}

void DesenhaLevy (Poligono *p, int **m) {
	Poligono *q; 
	int xm, ym;
	for (q = p->prox; q != p; q = q->prox) {
		xm = q->prox->x - q->x;
	}
}

int main () {
	Poligono *p = NULL, *aux = NULL; 
	int **pol, i, j, n, inter;
	float xn, yn;
	
/*	p = AlocaCabeca(); */
	printf ("Digite n: ");
	scanf ("%d %d", &n, &inter);	
	for (i = 0; i < n; i++) {
		printf ("\nDigite x e y: ");
		scanf ("%f %f", &xn, &yn);
		InserePoligono(&p, xn, yn);
	}    
	pol = AlocaMatriz();
	for (i = 0; i < inter; i++) {
		for (aux = p; aux != p; aux = aux->prox) 
			DrawLine (pol, L, C, aux->x, aux->y, aux->prox->x, aux->prox->y, 0);
		p = PoligonoPorPontoMedio(aux);
		GravaImagem(pol);
    }	    
    
	return 0;
}
