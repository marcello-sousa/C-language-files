#include <stdio.h>
#include <stdlib.h>
#define MAX 180

void ZeraMatriz (int tabuleiro[][MAX], int nlin, int ncol) {
    int i, j;   
    for (i = 0; i < nlin; i++)
        for (j = 0; j < ncol; j++)
            tabuleiro[i][j] = 0;
}

void pre_ativacao (int ativacao[][MAX], int nlin, int ncol) {
	int i, j;	
	for (i = 0; i < nlin; i++)
        for (j = 0; j < ncol; j++)
            ativacao[i][j] = -1;
}

void ImprimaTabuleiro (int tabuleiro[][MAX], int nlin, int ncol) {
    int i, j;
    for (i = 0; i < nlin; i++) {
        for (j = 0; j < ncol; j++) {
            printf ("%4d", tabuleiro[i][j]);
        }
        printf ("\n");
    }
    printf("\n");
}

void LeiaConfiguracaoInicial (int tabuleiro [][MAX], int *nlin, int *ncol) {
    int c, l, nc, nl, num, n = 0;    
    ZeraMatriz(tabuleiro, l, c);
    scanf ("%d %d", &l, &c);
    printf("\n");    
    while (n < 1) {
        scanf ("%d %d %d", &nl, &nc, &num);
        tabuleiro[nl][nc] = num;
    	n++;
    }  	 
    *ncol = c; *nlin = l;
}

void CopieMatriz (int origem[][MAX], int destino[][MAX], int nlin, int ncol) {
    int i, j;   
    for (i = 0; i < nlin; i++)
        for (j = 0; j < ncol; j++)
            destino[i][j] = origem[i][j]; 
}

int ver_espalha (int tab[][MAX], int l, int c, int nlin, int ncol) {
	int aux = 0; 	
	if (l+1 < nlin) aux++; 
	if (l-1 >= 0) aux++;
	if (c+1 < ncol) aux++;
	if (c-1 >= 0) aux++;	
	if (tab[l][c] >= aux) return 1;
	else return 0;
}

void espalhe (int tabuleiro[][MAX], int ativacao[][MAX], int nlin, int ncol, int instante, int *nativados) {
    int ctabuleiro[MAX][MAX], c = 0, l = 0, i, j, espalha = 0;
     ZeraMatriz(ctabuleiro, nlin, ncol);   
     while (instante < 7) {
     CopieMatriz(tabuleiro, ctabuleiro, nlin, ncol);     	
     for (i = 0; i < nlin; i++) {
      	for (j = 0; j < ncol; j++) {
     	    if (ctabuleiro[i][j] >= 0) espalha = ver_espalha(ctabuleiro, i, j, nlin, ncol);   	 
    	    if (espalha == 1) {
     	   	    	
     	    	if (i+1 < nlin) {
     	    		tabuleiro[i+1][j]++;
     	    		tabuleiro[i][j]--;
     	    		nativados++;
     	    		if (ativacao[i][j] == -1) ativacao[i][j] = instante;
     	    	}
     	    	
     	        if (i-1 >= 0) {
     	    		tabuleiro[i-1][j]++;
     	    		tabuleiro[i][j]--;
     	    		nativados++;
     	    		if (ativacao[i][j] == -1) ativacao[i][j] = instante;
     	    	}	
     	    
     	    	if (j+1 < ncol) {
     	    		tabuleiro[i][j+1]++;
     	    		tabuleiro[i][j]--;
     	    		nativados++;
     	    		if (ativacao[i][j] == -1) ativacao[i][j] = instante;
     	    	}
     	    	
     	    	if (j-1 >= 0) {
     	    		tabuleiro[i][j-1]++;
     	    		tabuleiro[i][j]--;
     	    		nativados++;
     	    		if (ativacao[i][j] == -1) ativacao[i][j] = instante;
     	    	}
     	    	
     	    }
     	}
     }   
     ImprimaTabuleiro(tabuleiro, nlin, ncol);
     instante++;
     }
     ImprimaTabuleiro(ativacao, l, c);
}

int main() {
    int tempo = 0, nativ, c, l, nli, nco, i, j;
    int tab[MAX][MAX], ctab[MAX][MAX], mativacao[MAX][MAX];
    
    LeiaConfiguracaoInicial(tab, &nli, &nco);
    c = nco; l = nli;   
    printf ("\n");
    ImprimaTabuleiro(tab, l, c);
    pre_ativacao(mativacao, l, c);
    espalhe(tab, mativacao, l, c, tempo, &nativ); 
    ImprimaTabuleiro(mativacao, l, c);
    
    return 0;
}
