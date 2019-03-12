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
/*    struct Rec_Emp *prox; */
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

void insere_patio (patio *p, patio *novo) {
 /*   patio *p = cabeca; */
       
    printf("%c ", p->iden_patio);
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
    }
    fclose(f);
}

void carrega_patio (patio *pa, patio p, recuperadora r1, recuperadora r2) {
	patio *pt = pa;
	FILE *f; 
	
	f = fopen ("portorec.txt", "rt");
	
	if (f == NULL) {
    	printf ("Problema na abertura do arquivo");
    	return;
    }
    
    while (!feof(f)) {
    	
    	fscanf (f, "%d %c %s %s %d %d %d %d", &p.capacidade, &p.iden_patio, r1.nome_rec, r2.nome_rec, &r1.uso_rec, &r2.uso_rec, &r1.taxa_rec, &r2.taxa_rec); 	
    	p.lista[0] = &r1;
    	p.lista[1] = &r2;
    	insere_patio(pt, &p);      	
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
	printf("%d ", p->capacidade);
	
	while (p != NULL && li->carga_navio > p->capacidade) 
		p = p->prox;
		
	return p;					
	
}

void funcao2 (cronograma *lista, int ciclo, patio *pa) {
	cronograma *l = lista;
	patio *p, *aux = pa; 
	int i = 0;
	
	while (l->ciclo == ciclo) {
		while (i < 3) {
			
			p = procura_patio(l, aux); 
						
		  	if (p != NULL) {
		  		printf ("Recuperadoras disponiveis: %s %s", p->lista[0]->nome_rec, p->lista[1]->nome_rec);
		  		if (p->lista[0]->uso_rec == 1 && p->lista[1]->uso_rec == 1) {
		  			p = procura_patio(l, aux);
		  			break;
		  		}
		  		else {}
		  		
		  	}
		  	
		  	else {
		  		printf ("\nPatio lotado"); 
			    p = pa;
			}	
	        
	        l = l->prox;
	        i++;	
	    }
	}
	
}

void funcao1 (cronograma *lista, patio *pa) {
	cronograma *p, *q, *r, *aux, *auxc; 
	char auxh[5], auxm[5]; 
	double tca, tcb, ta, tb;
	int ciclo = lista->ciclo; 
	auxc = lista->prox;
	p = lista->prox;
	q = p->prox;
	aux = malloc(sizeof(cronograma));
	
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
	    		
        
        p = p->prox;
        q = p->prox; 
        
        if (p->ciclo != ciclo) { 
        	funcao2(auxc, ciclo, pa);
	        ciclo = p->ciclo;
	    }
           
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


void imprime_patio (patio *pt) {
	patio *p; 
	
	for (p = pt; p->prox != NULL; p = p->prox) {
		printf("%c %d", p->iden_patio, p->capacidade);
		
		printf("\n");
    }    
    printf("teste");
} 

int main() {
	cronograma *Lista;
	Lista = malloc(sizeof(cronograma));
	Lista->prox = NULL; 
    carrega_cronograma(Lista);
	
    patio *PT;
    PT = malloc(sizeof(patio));
    PT->prox = NULL; 
    patio pat;
    pat.prox = NULL;
    recuperadora rec1, rec2;
	
	carrega_patio(PT, pat, rec1, rec2);
	printf("\n");
	
	printf("\n");
    
    cronograma *p = Lista;
	
	int i, j; 
    p->ciclo = -1;
 
	for (i = 1; p != NULL; i++) 
		for (j = 0; j < 3; j++) {			
			p->ciclo = i;
			p = p->prox;
		}
 
    printf("\n");    
    imprime(Lista); 
   
	
	funcao1(Lista, PT); 
    printf("\n\n");
    
	imprime_patio(PT); 

   
	return 0;
}
