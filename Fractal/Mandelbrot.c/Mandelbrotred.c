#include <stdio.h>
#include <math.h>
#define MAX_H 800
#define MAX_W 600

void grava_conjunto (int R[][MAX_H], int G[][MAX_H], int B[][MAX_H]) {
    int i, j;
    FILE *f;
	f = fopen("mandelbrot2.ppm", "w");
	if (f == NULL)
	    printf("Problemas ao criar o arquivo");
	else {
        fprintf(f, "P3\n800 600\n255\n");
		for (i = 0; i < MAX_W; i++)
			for (j = 0; j < MAX_H; j++)
				fprintf(f, "%d %d %d ", R[i][j], G[i][j], B[i][j]);
		    fprintf(f, "\n");
	}
	fclose(f);
}

int main () {
	static int R[MAX_W][MAX_H], G[MAX_W][MAX_H], B[MAX_W][MAX_H];
	int C1[3] = {255, 255, 0}, C2[3] = {0, 0, 156}, i, j, inter, inter_max, inter_min;
	double real, imag, re, im, x, y, p, q;
	inter_max = 995;
	inter_min = 1;
	for (i = 0; i < MAX_W; i++) {
		for (j = 0; j < MAX_H; j++) {
			x = -1.5 + (double) j / 400;
			y = 1.0 - (double) i / 300;
			real = 0; imag = 0; re = 0; im = 0;
			for (inter = 0; inter < 1000; inter++) {
				real = re*re - im*im + x;
				imag = 2*re*im + y;
				if (real*real + imag*imag > 4)
					break;
				else {
                    re = real;
                    im = imag;
                }
			}
			if (real*real + imag*imag > 4) {
				p = log10 (inter - inter_min + 1) / log10 (inter_max - inter_min + 1);
				q = 1 - p;
				R[i][j] = p*C1[0] + q*C2[0];
				G[i][j] = p*C1[1] + q*C2[1];
				B[i][j] = p*C1[2] + q*C2[2];
            }
			else {
                R[i][j] = 0;
                G[i][j] = 0;
                B[i][j] = 0;
			}
	     }
	}
	grava_conjunto(R, G, B);

	return 0;
}
