#include <stdio.h>
#define MAX_W 800
#define MAX_H 600

int main () {
	static int C[MAX_W][MAX_H];
	int i, j, inter;
	float real, imag, re, im, x, y;
	for (i = 0; i < MAX_W; i++) {
		for (j = 0; j < MAX_H; j++) {
			x = -1.5 + (float) i / 400;
			y = 1.0 - (float) j / 300;
			real = 0; imag = 0; re = x; im = y;
			for (inter = 0; inter < 50; inter++) {
				real = re*re - im*im + x;
				imag = 2*re*im + y;		
				if (real*real + imag*imag > 4)
					break;
				else re = real; im = imag;		
			}
			if (real*real + imag*imag > 4)
				C[i][j] = 255;
			else C[i][j] = 0;		
	     }
	}
	FILE *f;
	f = fopen("mandelbrot.txt", "w");
	if (f == NULL)
	    printf("Problemas ao criar o arquivo");
	else {
		for (i = 0; i < MAX_W; i++) 
			for (j = 0; j < MAX_H; j++)
				fprintf(f, "%d ", C[i][j]);
		    fprintf(f, "\n");
	}
	fclose(f);
	
	return 0;
}
