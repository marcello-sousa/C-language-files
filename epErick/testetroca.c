#include<stdio.h>
#include<stdlib.h>
 
struct cel {
     int cont;
     struct cel *prox;
};
 
typedef struct cel celula;
 
celula* insere (int x, celula *p) {
 
        celula *nova = (celula *)malloc (sizeof (celula));
        nova->cont = x;
        nova->prox = p;
        // necessário retorna o novo endereço do nova cabeça da lista ou da celula nova para a variável 'l'
        return nova;
 }
 
void selectsort(celula *p) {
     celula *i, *j, *aux;
     aux = (celula *)malloc (sizeof (celula));
     i = p;
     while( i != NULL) {
            j = i->prox;
            while (j != NULL) {
                   if (i->cont > j->cont){
                         //  swap dos ponteiros
                         *aux = *i ; // copia valor de i em aux.
                         *i =  *j; // copia valor de j em i.
                         i->prox = aux->prox; // altera ponterio do próximo de i para que ele continue sendo o mesmo que era antes da copia
                         aux->prox = j->prox; // copia o valor do ponteiro do proximo j
                         *j = *aux; // copia valor de aux em j.
                          j->prox = aux->prox; // altera ponterio do próximo de i para que ele continue sendo o mesmo que era antes da copia
                   }
                   j = j->prox;
            }
      i = i->prox;
    }
}
 
void imprima (celula *p) {
     celula *v;
     for (v = p; v != NULL; v = v->prox)
         printf ("%d ", v->cont);
         printf("\n");
}      
 
int main () {
    // lista vazia aponta para um endereço NULO !
    celula *l = NULL;
 
    // É necessário atualizar o ponteiro 'l' para a nova celula  ou  a cabeça da sua lista !  por isso do 'l = insere( numero, lista);'
    l = insere(7, l);
    l = insere(11, l);
    l = insere(8, l);
    l = insere(4, l);
    l = insere(12, l);
    l = insere(9, l);
    l = insere(1, l);
    imprima(l);
    selectsort(l);
    printf("\n");
    imprima(l);
 
   return 0;
 }
