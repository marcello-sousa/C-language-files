#include <stdio.h>

void subseq( int subs[], int n) {
	int k; 
	subs[k = 0] = 0;
	while(1) {
		if( subs[k] < n) {
			subs[k+1] = subs[k] + 1;
			++k;
		} else {
			subs[k-1] += 1;
			--k;
		}
		if( k == 0) break;
		for(int i = 1; i <= k; ++i) 
			printf("%d ", subs[i]);
		printf("\n");
	}
}

int main() {
	int subs[100];
	subseq(subs, 2);
	return 0;
}
