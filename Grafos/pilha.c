#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

RegPilha *AlocaRegPilha(){
	RegPilha* q;
	q = (RegPilha*)calloc(1, sizeof(RegPilha));
	if(q==NULL) exit(-1); 
    return q;
}

Pilha CriaPilha(){
	Pilha p;
	p = AlocaRegPilha();
	p->prox = NULL;
	return p;
}

void LiberaPilha( Pilha p){
	RegPilha *q,*t;
	q = p;
	while(q != NULL) {
		t = q;
		q = q->prox;
		free(t);
	}
}

bool PilhaVazia( Pilha p) {
	return (p->prox == NULL);
}

void Empilha( Pilha p, int x) {
	RegPilha *q;
	q = AlocaRegPilha();
	q->dado = x;
	q->prox = p->prox;
	p->prox = q;
}

int Desempilha( Pilha p) {
	RegPilha *q;
	int x;
	q = p->prox;
	if(q==NULL) exit(-1);
	x = q->dado;
	p->prox = q->prox;
	free(q);
	return x;
}
