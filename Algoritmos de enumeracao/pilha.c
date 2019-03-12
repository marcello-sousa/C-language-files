#include<stdio.h>
#include <stdbool.h>
#define MAX 50

int pilha[MAX];
int t;

void inicia_pilha() {	
	t = 0;
}

bool pilha_vazia () {	
	if (t == 0) return true;	
	else return false;
}

void empilha( int x) {	
	pilha[t++] = x;	
}

int desempilha () {		 
	return pilha[--t];;
}

void imprime_pilha() {
	for(int i = 0; i < t; i++) 
		printf("%d ", pilha[i]);	
	printf("\n");
} 

int pilha_topo() {	
	return pilha[t];
}	

int altera_topo() {
	pilha[t] = pilha[t] + 1;
}
	
int tamanho_pilha() {
	return t;
}
