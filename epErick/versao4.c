#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RE_NOME_DIM 10
#define PA_LISTA_DIM 2
#define NA_MAX 50


typedef struct Cronograma {
    int      data_cheg;
    int      hora_cheg;
    int      min_cheg;
    char     nome_navio[NA_MAX];
    int      carga_navio;
    int      pier;
    int      ciclo;
    struct Cronograma *prox;
} cronograma;


typedef const char * FILESPEC;

typedef struct rec_emp {

    int      re_taxa;
    int      re_uso;
    char     re_nome[RE_NOME_DIM];
} REC_EMP;

typedef struct Patio {

    struct Patio *pa_prox;
    int     pa_capacidade;
    char    pa_iden;
    REC_EMP pa_lista[PA_LISTA_DIM];   /* NOTE: structs, NOT pointers */

    #define pare(pa,n) ((pa)->pa_lista[(n)])
} patio;

patio *patio_novinho() {
    patio * p = calloc(1, sizeof (patio));
    return p;
}

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

void patio_insere(cabeca, novo)
    patio * cabeca;
    patio * novo;
{
    while (cabeca->pa_prox != NULL) {
        cabeca = cabeca->pa_prox;
    }
    novo->pa_prox = cabeca->pa_prox;
    cabeca->pa_prox = novo;
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

void patio_carrega(cabeca, arquivo)
    patio* cabeca;
    FILESPEC arquivo;
{
    FILE *fp = fopen(arquivo, "rt");

    if (fp == NULL) {
        perror("patio_carrega: Problema na abertura do arquivo");
        exit(1);
    }

    while (!feof(fp) && !ferror(fp)) {

        patio *pa = patio_novinho();

        fscanf(fp, "%d %c %s %s %d %d %d %d",
            &pa->pa_capacidade,
            &pa->pa_iden,
            pare(pa,0).re_nome,
            pare(pa,1).re_nome,
            &(pare(pa,0).re_uso),
            &(pare(pa,1).re_uso),
            &(pare(pa,0).re_taxa),
            &(pare(pa,1).re_taxa)
        );

        patio_insere(cabeca, pa);

    }

    fclose(fp);
}
	

double calcula_tempo (cronograma *P, cronograma *Q) {
	double tempo;
	
	tempo = (Q->hora_cheg + (double)Q->min_cheg/60) - (P->hora_cheg + (double)P->min_cheg/60);
	tempo = (Q->data_cheg - P->data_cheg)*24 + tempo;
	
	return tempo;
}

patio *procura_patio (cronograma *li, patio *pt) {
	patio *p = pt->pa_prox;
	
	while (p != NULL && li->carga_navio > p->pa_capacidade) 
		p = p->pa_prox;
		
	return p;					
	
}

void marca_recuperadoras (patio *pt, char re_nome[]) {
	patio *p = pt;
	
	while (p != NULL) {
		
		if (re_nome == p->pa_lista[0].re_nome) p->pa_lista[0].re_uso = 1;
		if (re_nome == p->pa_lista[1].re_nome) p->pa_lista[1].re_uso = 1;
		p = p->pa_prox;
		
    }
	
}	

void funcao2 (cronograma *lista, int ciclo, patio *pa) {
	cronograma *l = lista;
	patio *p, *aux = pa; 
	int i = 0;
	char rec[RE_NOME_DIM];
	
	while (aux->pa_prox != NULL) {
		
		aux->pa_lista[0].re_uso = 0;
		if (aux->pa_lista[1].re_uso != -1) aux->pa_lista[1].re_uso = 0;	aux = aux->pa_prox;
	}
	
	aux = pa;
		
	while (l->ciclo == ciclo) {
		while (i < 3) {
			
			p = procura_patio(l, aux); 
	        aux = p;
		  	if (p != NULL) {
		  		printf ("Recuperadoras disponiveis: %s %s\n", p->pa_lista[0].re_nome, p->pa_lista[1].re_nome);
		  		if ((p->pa_lista[0].re_uso != 0 && p->pa_lista[1].re_uso != 0) && (p->pa_capacidade - l->carga_navio < 0)) {
		  		p = procura_patio(l, aux);
		  			
		  		}
		  		else {
		  			if (p->pa_lista[0].re_uso == 0) {
		  				printf ("\n%c %d %s %s \n", p->pa_iden, l->ciclo, l->nome_navio, p->pa_lista[0].re_nome);
		  				strcpy(rec, p->pa_lista[0].re_nome);
		  				marca_recuperadoras(pa, rec);
		  				p->pa_capacidade = p->pa_capacidade - l->carga_navio;  		       
		  			}
		  			
		  			else if (p->pa_lista[1].re_uso == 0) {
		  				printf ("\n%c %d %s %s *\n", p->pa_iden, l->ciclo, l->nome_navio, p->pa_lista[1].re_nome);
		  				strcpy(rec, p->pa_lista[1].re_nome);
		  				marca_recuperadoras(pa, rec);
		  				p->pa_capacidade = p->pa_capacidade - l->carga_navio;
		  			    	  		         
		  			}
		  			
		  		} 
		  		
		  	}
		  	
		  	else {
		  		printf ("\nPatio lotado"); 
			    aux = pa;
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
	        auxc = p;
	    } 
        
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
	
	for (p = pt; p->pa_prox != NULL; p = p->pa_prox) {
		printf("%c %d %s", p->pa_iden, p->pa_capacidade, p->pa_lista[0].re_nome);
		
		printf("\n");
    }    
} 

int main() {
	cronograma *Lista;
	Lista = malloc(sizeof(cronograma));
	Lista->prox = NULL; 
    carrega_cronograma(Lista);
	
    
    patio *cabeca = patio_novinho();
    patio_carrega(cabeca, "portorec.txt");    
    
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
/*    imprime(Lista); */
   
	
	funcao1(Lista, cabeca); 
    printf("\n\n");
    
	imprime_patio(cabeca); 

   
	return 0;
}
