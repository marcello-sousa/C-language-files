#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

RegFila *AlocaRegFila() {
	RegFila* q;
    q = (RegFila*)calloc(1, sizeof(RegFila));
    if( q == NULL) exit(-1);  
    return q;
}
 
Fila CriaFila() {
	Fila p;
    p = AlocaRegFila();
    p->prox = p;
    return p;
}
 
void LiberaFila (Fila p){
	RegFila *q,*t;
    q = p->prox;
    while( q != p) {
    	t = q;
        q = q->prox;
        free(t);
    }
    free(p);
}
 
boolean FilaVazia( Fila p){
  return( p == p->prox);
}
 
void InsereFila( Fila *p, int x){
	RegFila *q;
    q = AlocaRegFila();
    q->dado = &x;
    q->prox = (*p)->prox;
    (*p)->prox = q;
    *p = q;
}
 
int RemoveFila( Fila *p) {
	RegFila *q,*t;
    int *x;
    q = (*p)->prox;
    if( q ==*p) exit(-1); 
    t = q->prox;
    x = t->dado;
    q->prox = t->prox;
    if( t == *p) *p = q;
    free(t);
    return *x;
}
