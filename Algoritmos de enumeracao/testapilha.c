#include<stdio.h>
#include "pilha.c"
#include "pilha.h"


int main() {
	inicia_pilha();
	empilha(2);
	empilha(3);
	empilha(4);
	imprime_pilha();
	int x = desempilha();
	imprime_pilha();
	printf("%d \n", x);
	printf("%d ", pilha_topo());
	x = desempilha();
	printf("%d ", pilha_topo());
	return 0;
	
}
