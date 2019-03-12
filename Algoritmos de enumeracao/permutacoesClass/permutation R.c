#include <stdio.h>
#include <stdlib.h>

int candidato( int *perm, int i, int m) {
	for( int k = 1; k <= i; k++) 
		if (perm[k] == m) return 0;
	return 1;	
}

void imprime( int *perm, int n) {
	int i;
	for( i = 1; i <= n; i++) 
		printf("%d ", perm[i]);
	printf("\n");	
}

void permutacaoR( int *perm, int i, int n) {	
	if( i >= n) imprime( perm, n);
	else {
		int m;
		for( m = 1; m <= n; m++) 
			if( candidato(perm, i, m)) {
				perm[i+1] = m;
//				printf("\n%d \n", m);
				permutacaoR( perm, i+1, n);
			}
	}	
}

void permutacao( int n) {
	int *perm = malloc((n+1) * sizeof(int));
	for( int i = 1; i <= n; i++) perm[i] = i;
	permutacaoR( perm, 0, n);
}

int main() {
	permutacao(3);
	return 0;	
}
