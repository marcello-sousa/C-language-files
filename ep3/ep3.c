#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no No;

struct no {
	char conteudo;
	No *prox;
	
};

No *pilha = NULL;

void empilha (char conteudo, No **pilha) {
	No *novo;
	
	novo = malloc(sizeof(No));
	    if (novo == NULL) return;
	novo->conteudo = conteudo;
	
	if (*pilha == NULL) {
		novo->prox = NULL;
	    *pilha = novo;
	}
	
	else {
        novo->prox = *pilha;
        *pilha = novo;
    }	
}

char desempilha (No **pilha) {
	No *p; char x;
	
	p = *pilha;
	x = p->conteudo;
	if (p != NULL) {
	   *pilha = p->prox;
	   free(p);
	}
	return x;
}

void imprime (No *pilha) {
    No *p;
    
    if (pilha == NULL) {
    	printf("Pilha vazia");
        return;
    }
    
    else {
    	for (p = pilha; p != NULL; p = p->prox)
    	    printf("%c", p->conteudo);
    }
    printf("\n\n");
}

int bemformada (char str[]) {
	
	int i;char c, aux;
	
	for (i = 0; i < strlen(str); i++) {
		aux = str[i];
		switch(str[i]) {
			
		   case ')': if (pilha == NULL) return 0;
			          c = desempilha(&pilha);
		              if (c != '(') return 0;
		              break;
		    
		   case ']': if (pilha == NULL) return 0;
			          c = desempilha(&pilha);
		              if (c != '[') return 0;
		              break;
		   
		   case '}': if (pilha == NULL) return 0;
			          c = desempilha(&pilha);
		              if (c != '{') return 0;
		              break;
		   
		  default:    empilha(aux, &pilha); 
		   
		 }
	}
	return 1;
}

int main () {
	
	char s[20] = {"(([a+b]))"};
	
	if (bemformada(s)) printf ("Bem formada");
	else printf("mal formada");
	return 0;
	
}
