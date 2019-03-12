#ifndef _FILA_H_
#define _FILA_H_

typedef enum boolean {False, True} Boolean;
 
typedef struct RegFila {
	int *dado;
    struct RegFila *prox;
} RegFila;
 
typedef RegFila* Fila;
 
RegFila *AlocaRegFila();

Fila CriaFila();

void InsereFila(Fila *p, int x);
 
void LiberaFila (Fila p);
 
boolean FilaVazia( Fila p);

int RemoveFila( Fila *p);
 
#endif

  
