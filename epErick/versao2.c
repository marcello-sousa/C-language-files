#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RECS_PATIO 2

struct Cronograma {
    int data_cheg;
    int hora_cheg;
    int min_cheg;
    char nome_navio[50];
    int carga_navio;
    int pier;
    int ciclo;
    struct Cronograma *prox;
};

typedef struct Cronograma cronograma;

struct Rec_Emp {
    char nome_rec[10];
    int uso_rec;
    int taxa_rec;
    struct Rec_Emp *prox;
};

typedef struct Rec_Emp recuperadora;

struct Patio {
    char iden_patio;
    int capacidade;
    struct Patio *prox;
    struct Rec_Emp *lista[RECS_PATIO];
}; 

typedef struct Patio patio;

void insere_crono (cronograma *lista, int data, int hora, int min, const char nome[], int carga, int pr) {
	cronograma *p, *novo;
	p = lista;

	novo = malloc(sizeof(cronograma));
	novo->data_cheg = data;
	novo->hora_cheg = hora;
	novo->min_cheg = min;
	strcpy (novo->nome_navio, nome);
	novo->carga_navio = carga; 
	novo->pier = pr;
	
	while (p->prox != NULL) 
		p = p->prox; 
	novo->prox = p->prox;
	p->prox = novo;
}

void insere_patio (patio *pa, int capa, char ident) {
	patio *novo, *p = pa;
	
	novo = malloc(sizeof(patio));
	novo->iden_patio = ident;
	novo->capacidade = capa;
	
	while (p->prox != NULL) 
		p = p->prox;
	novo->prox = p->prox;
	p->prox = novo;
}

void insere_rec (recuperadora *rec, char nome[], char ident[], int uso, int taxa) {
	recuperadora *novo, *p = rec;
	
	novo = malloc (sizeof(recuperadora));
	strcpy(novo->nome_rec, nome);
	strcpy(novo->ident_rec, ident);
	novo->uso_rec = uso;
	novo->taxa_rec = taxa;
	
	while (p->prox != NULL) 
		p = p->prox;
	novo->prox = p->prox;
	p->prox = novo;
	
}

void carrega_cronograma (cronograma *lista) {
	cronograma *p = lista;  
	
	FILE *f;
	int c, pi, m, h, dc; char nv[50], lixo;

	f = fopen ("crono.txt", "rt");
    
    if (f == NULL) {
    	printf ("Problema na abertura do arquivo");
    	return;
    }
    
    while (!feof(f)) {
    	fscanf(f, "%d %d %c %d \"%[^\"]\" %d %d", &dc, &h, &lixo, &m, nv, &c, &pi);
    	insere_crono (p, dc, h, m, nv, c, pi);
 /*   	printf("%d %d %c", h, m, lixo);
    	printf("\n"); */
    }
    fclose(f);
}

void carrega_patio (patio *pt) {
	patio *p = pt;
	FILE *f;
	char pto; int cp;
	
	f = fopen ("porto.txt", "rt");
	
	if (f == NULL) {
    	printf ("Problema na abertura do arquivo");
    	return;
    }
    
    while (!feof(f)) {
    	fscanf (f, "%d %c", &cp, &pto); 
    	insere_patio(p, cp, pto);
	}
	fclose(f);
}

void carrega_rec_emp (recuperadora *rec) {
	recuperadora *p = rec;
	FILE *f;
	char nome[10], ident[10];
	int taxa, uso;
	
	f = fopen("rec_empi.txt", "rt");
	
	if (f == NULL) {
		printf ("Problema na abertura do arquivo");
    	return;
    }
	
    while (!feof(f)) {
    	fscanf(f, "%s %d %d", nome, &uso, &taxa);
    	insere_rec (p, nome, uso, taxa);
    }
	fclose(f);
}
	

double calcula_tempo (cronograma *P, cronograma *Q) {
	double tempo;
	
	tempo = (Q->hora_cheg + (double)Q->min_cheg/60) - (P->hora_cheg + (double)P->min_cheg/60);
	tempo = (Q->data_cheg - P->data_cheg)*24 + tempo;
	
	return tempo;
}

patio *procura_patio (cronograma *li, patio *pt) {
	patio *p = pt;
	
	while (p != NULL && li->carga_navio > p->capacidade) 
		p = p->prox;
		
	return p;					
	
}

void funcao2 (cronograma *lista, int ciclo, patio *pa, recuperadora *re) {
	cronograma *l = lista;
	patio *p = pa; 
	recuperadora *r = re;
	int i = 0;
	
	while (r != NULL) {
		r->uso_rec = 0;
	    r = r->prox;
    }
	
	while (l->ciclo == ciclo) {
		while (i < 3) {
			p = procura_patio(l, p);
		
		  	if (p != NULL) {
		  		
		  		
		  	}
		  	
		  	else printf ("Patio lotado");
			
				
	        if (i == 3) {
	        	i = 0; ciclo++; r = re;
	        	
	        }
	        l = l->prox;
	        i++;	
	    }
	}
	
}

void funcao1 (cronograma *lista, patio *pa, recuperadora *re) {
	cronograma *p, *q, *r, *aux, *auxc; int ciclo = 1, i = 2; 
	aux = malloc(sizeof(cronograma));
	char auxh[5], auxm[5]; 
	double tca, tcb, ta, tb;
	auxc = lista->prox;
	p = lista->prox;
	q = p->prox;
	
	while (p->prox != NULL) {
		
		while (p->ciclo == q->ciclo && q->prox != NULL) {
		
			if (p->pier == q->pier) {
			    tca = p->carga_navio/6000;
	            tcb = q->carga_navio/6000;
	            
			    r = q;		    
			    
		        while (r->ciclo < ciclo + 1 && r->prox != NULL) 
			        r = r->prox;
			  	    			 
		         ta = calcula_tempo(p, q);
		    	 tb = calcula_tempo(q, r);
			    
			     if (tca + tcb > ta + tb) {	
			         if (r->pier != q->pier) {
			            *aux = *q;
			            *q = *r;
		     	        q->prox = aux->prox;
			            aux->prox = r->prox;
		    	        *r = *aux;
		       	        r->prox = aux->prox;
		    	        q->ciclo = ciclo;
		    	        r->ciclo = ciclo + 1;
		    	     }	
	             }	    
           	}
           	         		    
            q = q->prox;		   	
    	}
	    if (i == 3) { 
	  	    i = 1; ciclo++;	
        }	
        
        funcao2(auxc, ciclo-1, pa, re);
        p = p->prox;
        q = p->prox; 
        i++;
        auxc = p;
	}    
}
	
void imprime (cronograma *lista) {
	cronograma *p; 
	
	for (p = lista->prox; p->prox != NULL; p = p->prox) {
		printf("%d %.2d:%.2d %s %d %d %d", p->data_cheg, p->hora_cheg, p->min_cheg, p->nome_navio, p->carga_navio, p->pier, p->ciclo);
		printf("\n");
    }
}  

void forma_ciclos (cronograma *lista) {
	cronograma *p = lista;
	
	int i, j; 
	for (i = 1; p != NULL; i++) 
		for (j = 0; j < 3; j++) {			
			p->ciclo = i;
			p = p->prox;
		}
}

/*
void imprime_patio (patio *pt) {
	patio *p; 
	
	for (p = pt->prox; p->prox != NULL; p = p->prox) {
		printf("%c %d", p->iden_patio, p->capacidade);
		printf("\n");
    }
} 

void imprime_rec (recuperadora *rec) {
	recuperadora *p; 
	
	for (p = rec->prox; p->prox != NULL; p = p->prox) {
		printf("%s %s %d %d", p->nome_rec, p->ident_rec, p->uso_rec, p->taxa_rec);
		printf("\n");
    }
}  
*/
int main() {
	cronograma *Lista;
	Lista = malloc(sizeof(cronograma));
	Lista->prox = NULL;

    patio *PT;
    PT = malloc(sizeof(patio));
    PT->prox = NULL;
    recuperadora *REC;
    REC = malloc(sizeof(recuperadora));
    REC->prox = NULL;
	
	carrega_cronograma(Lista);
	carrega_patio(PT);
	printf("\n");
/*	imprime_patio(PT); */
	carrega_rec_emp(REC);
	printf("\n");
 /*   imprime_rec(REC); */
    REC = REC->prox; 
    forma_ciclos(Lista);
    printf("\n");    
    imprime(Lista); 
   
	funcao1(Lista, PT, REC); 
    printf("\n\n");
    
/*	funcao2(Lista, PT, REC); */
   
	return 0;
}
