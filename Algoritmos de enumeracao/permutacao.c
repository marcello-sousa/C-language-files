#include <stdio.h>
#include <stdlib.h>

void imprime(int subs[], int k) {
	for( int i = 1; i <= k; ++i) 
		printf("%d ", subs[i]);
	printf("\n");
}

int pode( int *perm, int k, int m) {
	int i;
	for( i = 0; i <= k; ++i) 
		if( perm[i] == m) 
			return 0;
	return 1;
}

void permutacoes( int n) {
	int k, m;
	int *perm = malloc((n+1)*sizeof(int));
	for( k = 1; k <= n; k++) perm[k] = k;
	k = n;
	while(1) {
		if( k >= n) {
			imprime( perm, n);
			m = n + 1;
		}
		while( m <= n && !pode(perm, k, m))
			m++;
		if( m <= n) {
			perm[k+1] = m;
			m = 1;
			++k;
		} else {
			if( k < 1) break;
			m = perm[k] + 1;
			--k;
		}
	//	printf("\n*%d %d\n", m, k);
	}
	free(perm);
}


int main() {
	permutacoes(5);
	return 0;
}
