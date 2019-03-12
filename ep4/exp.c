//insere inicio retira fim
#include <stdio.h>
#include <stdlib.h>
#define SUCESSO 1
#define FALHA  -1

 typedef struct ElementoLifo   ElementoLifo;
struct ElementoLifo {
   int            dado;       // dado deste elemento
   ElementoLifo *proximo;    // elemento seguinte a este
   ElementoLifo *anterior;
};
typedef struct Lifo   Lifo;
struct Lifo {
   int          nelemen;     // nro elementos desta fila
   ElementoLifo * inicio;      // primeiro elemento desta fila
   ElementoLifo * fim;         // ultimo elemento desta fila
};

int  destroiLifo (Lifo *fila);
 int insereLifo (Lifo *fila, int dado);
 int retiraLifo (Lifo *fila, int *dado);
 Lifo *criafila();    // cria uma nova fila
int nelementos    (Lifo *fila);  // retorna nro elementos

Lifo  *criafila() {    // cria uma nova fila
   Lifo *nova = malloc( sizeof(Lifo) );
   nova->nelemen = 0;
   nova->inicio  = NULL;
   nova->fim     = NULL;
   return nova;   // retorne a nova fila criada
}
 int nelementos    (Lifo *fila) {  // retorna nro elementos
    return fila->nelemen;
}
int insereLifo (Lifo *fila,int dado ) {

    ElementoLifo *novo = malloc( sizeof(ElementoLifo));
    novo->dado = dado;
    novo->proximo = fila->inicio;

    if(fila->nelemen==0)      // 1a insercao (fila vazia) ?
        fila->fim = novo;     // se fila vazia, então novo elemento é também o fila->fim

    fila->inicio = novo;      // inserção no inicio: novo elemento é o fila->inicio

    fila->nelemen++;
    return SUCESSO;
}
int retiraLifo (Lifo *fila, int *dado) {

ElementoLifo *fim = fila->fim;
   if(fim!=NULL)  // // existe o ultimo elemento (fila não-vazia)?
   {
     *dado = fim->dado;
      fila->nelemen--;

      if((fila->nelemen)==0) { // a fila esvaziou?
            fila->inicio=NULL;
            fila->fim=NULL;
      }
      else
      if((fila->nelemen)==1) { // fila ficou com apenas 1 elemento?
            fila->fim = fila->inicio;
            fila->fim->proximo = NULL;
      }
      else  // fila ficou com mais que 1 elemento
      {
           ElementoLifo *ultimo = fila->inicio;  // procure qual será agora o ultimo elemento da fila
            while(ultimo->proximo != fim) ultimo = ultimo->proximo;
            fila->fim = ultimo;          // encontrou - ajuste os ponteiros de ligação
            fila->fim->proximo = NULL;
      }

      free(fim);   // devolva a memoria ao SO
      return SUCESSO;
   }
   else
      return FALHA;

}


int main(int argc, char const *argv[])
{ 

    Lifo *fila1 = criafila();
    printf("fila criada, nro elem=%d \n", nelementos(fila1));
    insereLifo (fila1,1 );
    printf("INSERCAO NO INICIO, nro elem=%d \n", nelementos(fila1));
    insereLifo (fila1,2 );
    printf("INSERCAO NO INICIO, nro elem=%d \n", nelementos(fila1));
    insereLifo (fila1,3 );
    printf("INSERCAO NO INICIO, nro elem=%d \n", nelementos(fila1));

    retiraLifo (fila1,3);
    printf("RETIRADA NO FIM, nro elem=%d \n", nelementos(fila1));
    retiraLifo (fila1,2);
    printf("RETIRADA NO FIM, nro elem=%d \n", nelementos(fila1));
    retiraLifo (fila1,1);
    printf("RETIRADA NO FIM, nro elem=%d \n", nelementos(fila1));




  return 0;
}
