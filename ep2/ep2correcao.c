#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa Pessoa;
struct pessoa{
    int posicao;
    Pessoa *prox;
    
    
    y
    
    
    
    
};


/* Lista inicialmente vazia */
Pessoa *inicio = NULL;


/* Insere no fim da lista*/
void insereLista (int x){
    Pessoa* nova = malloc (sizeof (Pessoa));
    Pessoa* aux = inicio;
    nova->posicao = x;

    if (inicio == NULL){
        inicio = malloc (sizeof (Pessoa));
        inicio = nova;
        inicio->prox = inicio;
        return;
    }

    while (aux->prox != inicio)
        aux = aux->prox;

    aux->prox = nova;
    nova->prox = inicio;
}


/* Remove o elemento imediatamente apĆ³s o elemento p presente na lista*/
void removeLista (Pessoa *p){
    Pessoa *removida;
    
    if(p->prox == inicio){
        removida = inicio;
        inicio = removida->prox;
        p->prox = inicio;
    }else{
        removida = p->prox;
        p->prox = removida->prox;
    }

    free(removida);
}


/* Imprime cada elemento dentro da lista */
void imprimeLista (){
    Pessoa* aux = inicio;

    /* Checa se a lista estĆ� vazia*/
    if (aux == NULL){
        printf("Lista vazia");
    }else{ 
        /* Imprime cada pessoa presente na lista */
        do{        
            printf ("%d ", aux->posicao);
            aux = aux->prox;
        }while(aux != inicio);
    }

    printf("\n");
}


void resolveJosephus (int n, int m){
    Pessoa *aux, *atual;
    int i;
  
    aux = malloc (sizeof (Pessoa));

    /* insere pessoas na lista */
    for (i = 1; i <= n; i++)    insereLista(i);
    
    atual = inicio;
    
    /* O laĆ§o continua enquanto existe mais de uma pessoa na lista*/
    while (inicio->prox != inicio){
        aux = atual;

        /* caminha os m passos */
        for (i = 0; i < m - 1; i++) aux = aux->prox;

        /* impede suicidio */
        if (aux->prox == atual)   aux = atual;
        
        removeLista(aux);
        atual = aux->prox;
    }
    
    printf("A pessoa sobrevivente estĆ� na posicao ");

    /* So existe uma pessoa na lista */
    imprimeLista();
}


int main (){
    resolveJosephus(4, 1);
    return 0;
}

