#include <stdio.h>
#include "pilha.h"
#include "pilha.c"

void StackSubLex( int n) {
	inicia_pilha();
	int s = 0, x = 0;
	while(1) {
		x = desempilha();		
		if(x < n) {
			empilha(x);
			empilha(x + 1);
			
		}
		else {
			if( pilha_vazia()) break;
			x = desempilha();
			empilha(x + 1);		
		}
		imprime_pilha();
	}
}

int main() {
	StackSubLex(3);
	return 0;
	
}
