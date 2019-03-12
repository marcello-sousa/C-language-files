#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define M 30

char** ordenacaoCrescente (char palavras[N][M]);
char** ordenacaoDecrescente (char palavras[N][M]);

int main () {
	
    char str[10][M] = {"lovelace", "snyder", "jennings", "meltzer", "wescoff", "bilas", "mcnulthy", "lichterman", "hopper", "hamilton"};

    char str1 [6][M] = {"heinlein", "gibson", "clarke", "asimov", "wallace", "kindred"};

return 0;
}

void intercala(int p, int q, int r, char m[N][M]) {
	int i, j, k, aux; char **w;
	
	w = (char **)malloc(N*sizeof(char *));
	for (i = 0; i < N; i++) {
		w[i] = (char *)malloc(M*sizeof(char));
		for (j = 0; j < M; j++)
		    w[i][j] = 0;
		
	for (i = 0, k = p; k < q; i++, k++)
		for (j = 0; m[i][j] != '\0'; j++) 
			w[i][j] = m[k][j];
		
	for (i = r-p-1; k < r; i--, k++)
		for (j = 0; m[i][j] != '\0'; j++) 
			w[i][j] = m[k][j];
		
	i = 0; j = r-p-1; aux = 0;
		
	for (k = p; k < r; k++) {
		while (w[k][i] != '\0') {
			if (w[k][i] != w[k][j])
	           for (aux = 0; w[k][aux] != '0'; aux++)
			
	}
		
}
    
	

char** ordenacaoCrescente (char palavra[N][M]) {
}
	
