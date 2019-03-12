#include <stdlib.h>
#include <stdio.h>

static void troca (int *perm, int k, int j) {
	int t = perm[k]; perm[k] = perm[j]; perm[j] = t; 
}

void imprime(int *perm, int n) {
	for( int i = 1; i <= n; i++) 
		printf("%d ", perm[i]);
	printf("\n");
}

static void permsComPrefixo (int *perm, int i, int n) {
	if (i >= n-1)
       imprime (perm, n);
    else {
    	int j;
    	for (j = i + 1; j <= n; j++) {
    		troca (perm, i + 1, j);
    		permsComPrefixo (perm, i + 1, n);
    		troca (perm, i + 1, j); 
    	} 
    }
}

void permutacoes (int n) {
	int i, *perm;    
	perm = malloc ((n+1) * sizeof (int));
	for (i = 1; i <= n; i++) 
		perm[i] = i;
	permsComPrefixo (perm, 0, n);
	free (perm);
}

int main() {
	permutacoes(3);
	return 0;
}
