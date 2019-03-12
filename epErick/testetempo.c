#include <stdio.h>

int main () {
	int h1, h2, m1, m2, d1, d2;
	h1 = h2 = m1 = m2 = d1 = d2 = 0;
	double tt;
	
	h1 = 23; m1 = 30;
	h2 = 11; m2 = 20;
	d1 = 1; d2 = 3;
	
	tt = (h2 + (double)m2/60) - (h1 + (double)m1/60);
	
	tt = (d2 - d1)*24  + tt;
	
	printf ("%.2lfh", tt);
	
	return 0;
	
	
}
