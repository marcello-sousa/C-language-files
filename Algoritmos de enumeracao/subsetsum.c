#include <stdio.h>
#include <stdlib.h>

void imprime(int subs[], int k) {
	for( int i = 1; i <= k; ++i) 
		printf("%d ", subs[i]);
	printf("\n");
}

void SetSum(int subs[], int v[], int k, int t) {
	int sum = 0;
	for( int i = 1; i <= k; i++) 
		sum += v[subs[i] - 1];
	if( sum == t) imprime(subs, k);
}

void sublex( int n, int v[], int t) {
	int *subs, k;
	subs = malloc((n+1)*sizeof(int));
	subs[k=0] = 0;
	while(1) {
		if( subs[k] < n) {
			subs[k+1] = subs[k] + 1;
			++k;
		} else {
			subs[k-1] += 1;
			--k;		
		}
		if( k == 0) break;
		SetSum(subs, v, k, t);	
	}
	free(subs);
}

int main() {
	int v[] = {61, 62, 63, 64};
	int t = 125;
	sublex(4, v, t);
}
