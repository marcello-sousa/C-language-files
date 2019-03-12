#include <stdio.h>
#include <math.h>
#define MAX 50

int main () {
	int n = 15, i;
	double cor, var, varx, vary, var_aux, xm = 6.07, ym = 11.6, x[MAX], y[MAX];
		 
    for (i = 0; i < n; i++)    	
    	scanf("%lf", &x[i]);
    for (i = 0; i < n; i++)    	
    	scanf("%lf", &y[i]);
	for (i = 0; i < n; i++) 
		var = var + x[i]*y[i] - n*xm*ym;
	for (i = 0; i < n; i++) {
		varx = var + x[i]*x[i] - n*xm*xm;
	for (i = 0; i < n; i++) 
		vary = vary + y[i]*y[i] - n*ym*ym;
	var_aux = sqrt(varx*vary);
	cor = var/var_aux;
	printf ("%lf", cor);
	
    return 0;
}
