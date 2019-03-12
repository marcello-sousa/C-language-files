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
			
		ssLexComPrefixo( subs, k, m + 1, n);
		imprime(subs, k + 1);	
		ssLexComPrefixo( subs, k + 1, m, n);
	}
}

void sublex2( int n) {
	int *subs = malloc((n+1)*sizeof(int));
	ssLexComPrefixo( subs, 0, 1, n);
	free(subs);	
}

void OrdemMilitar( int n) {
	int *subs = malloc((n+1)*sizeof(int));
	int k, i;
	subs[k = 1] = 0;
	while( 1) {			
		if( subs[k] < n) 			
			subs[k] += 1;			
		else {
			i = 1;		
	    	while((k - i) > 0) {
				if( subs[k-i] < (n - i)) {
					subs[k-i] += 1;	
					break;	  
				}			  
				i++;				
			}			
			if( k == i) {		
				k++;		
				i = 1;				
				while( i <= k) {			
					subs[i] = i;
					i++;
				}				
			}
		}	
		imprime(subs, k); 
		if (k >= n) break;
	}
} 

int main() {
//	sublex2(3);
	OrdemMilitar(5);
	return 0;
	
}
