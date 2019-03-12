#include<stdio.h>
#include<stdlib.h>

static void troca (char *perm, int k, int j) {
	char t = perm[k]; perm[k] = perm[j]; perm[j] = t; 
}

void imprime(char *perm, int n) {
	for( int i = 1; i <= n; i++) 
		printf("%c ", perm[i]);
	printf("\n");
}

void ComPrefixo( char *perm, int i, int n) {
	if( i == n) imprime( perm, n);
	else {
		for( int j = i; j <= n; j++) {
			troca(perm, i, j);
			ComPrefixo( perm, i + 1, n);
			troca(perm, i, j);
		}
	}
}

void permutacoes(int n, char *perm) {
	ComPrefixo(perm, 1, n);
}

int main() {	
	char perm[10] = {"-ABC"};
	permutacoes(3, perm);
	return 0;
}
