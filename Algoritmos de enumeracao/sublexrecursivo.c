#include <stdio.h>
#include <stdlib.h>

void imprime(int subs[], int k) {
	for( int i = 1; i <= k; ++i) 
		printf("%d ", subs[i]);
	printf("\n");
}

void ssLexComPrefixo( int subs[], int k, int m, int n) {
	if( m <= n) {
		subs[k + 1] = m;
		imprime(subs, k + 1);
		ssLexComPrefixo( subs, k + 1, m + 1, n);
//		printf("%d, %d\n ", k, m);
		ssLexComPrefixo( subs, k, m + 1, n);
	}
}

void SubLex2( int n) {
	int *subs;
	subs = malloc((n+1)*sizeof(int));
	ssLexComPrefixo( subs, 0, 1, n);
	free(subs);
}

int main() {
	SubLex2(2);
	return 0;
}
