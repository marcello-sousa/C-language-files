#ifndef _PILHA_H_
#define _PILHA_H_

typedef struct _RegPilha{
	int dado;
    struct _RegPilha *prox;
} RegPilha;

typedef RegPilha* Pilha;

typedef enum boolean {False,True} bool;

RegPilha *AlocaRegPilha();

Pilha CriaPilha();

void LiberaPilha(Pilha p);

bool PilhaVazia(Pilha p);

void Empilha(Pilha p, int x);

int Desempilha(Pilha p);

#endif
