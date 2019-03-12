#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inocente( unsigned char a[], int m, unsigned char b[], int n) {
	int ocorr = 0;
	for( int k = m; k <= n; ++k) {
		int i = m, j = k;
		while( i >= 1 && a[i] == b[j]) {
			i--, j--;
		}
		if( i < 1) ++ocorr;
	}
	return ocorr;
}

int boyermoore( unsigned char a[], int m, unsigned char b[], int n) {
	int ult[128];
	for(int f = 0; f < 128; ++f) ult[f] = 0;
	for(int i = 1; i <=  m; ++i) ult[a[i]] = i;
	int ocorr;
	int k = m;
	while( k <= n) {
		int i = m, j = k;
		while( i >= 1 && a[i] == b[j]) 
			--i, --j;
		if( i < 1) ++ocorr;
		if( k == n) break;
		k += m - ult[b[k + 1]] + 1;	
	}
	return ocorr;
}

int boyermoore1( unsigned char a[], int m, unsigned char b[], int n) {
	int ult[128];
	for (int i = 0; i < 128; ++i) ult[i] = 0;
	for (int i = 1; i <   m; ++i) ult[a[i]] = i;
	int ocorrs = 0, k = m;
	while (k <= n) {
		int i = m, j = k;
		while (i >= 1 && a[i] == b[j]) 
		    --i, --j;   
		if (i < 1) ++ocorrs;
		k += m - ult[b[k]];
	}
	return ocorrs;
}

int boyermoore2( unsigned char a[], int m, unsigned char b[], int n) {
	int *alcance = malloc((m+1)*sizeof(int));
	int h = m, k = m - 1;
	while( h >= 1 && k >= 1) {
		int i = m, j = k;
		while( i >= h && j >= 1) {
			if (a[i] == a[j]) --i, --j;
		    else i = m, j = --k;	
	    }
		alcance[h--] = k;
	}
	while( h >= 1) alcance[h--] = k;
	for( int i = 1; i <= m; i++) 
		printf("%d ", alcance[i]); 
	int ocorrs = 0;
	k = m;
    while (k <= n) {
    	int i = m, j = k;
    	while (i >= 1 && a[i] == b[j]) 
    		--i, --j;  
    	if (i < 1) ++ocorrs;
    	if (i == m) k += 1;
    	else k += m - alcance[i+1];
    }
    return ocorrs;
}  



int main() {
    unsigned char a[] = {"-abcbccabc"};
	unsigned char b[] = {"-abbaabbba abba bab"};
//	printf ("\n%d ", boyermoore(a, strlen(a)-1, b, strlen(b)-1));
//	printf ("\n%d ", boyermoore1(a, strlen(a)-1, b, strlen(b)-1));
    printf("\nOcorrencias = %d ", boyermoore2(a, strlen(a)-1, b, strlen(b)-1));
	return 0;
}
