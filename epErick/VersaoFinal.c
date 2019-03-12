#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define RE_NOME_DIM 10
#define PA_LISTA_DIM 2
#define NA_MAX 50

typedef const char * FILESPEC;

typedef struct Cronograma {
    int      na_data;
    int      na_hora;
    int      na_min;
    char     na_nome[NA_MAX];
    int      na_carga;
    int      na_pier;
    int      na_ciclo;
    struct Cronograma *na_prox;
} cronograma;


typedef struct rec_emp {

    int      re_taxa;
    int      re_uso;
    char     re_nome[RE_NOME_DIM];
} REC_EMP;

typedef struct Patio {

    struct Patio *pa_prox;
    int      pa_capacidade;
    char     pa_iden;
    REC_EMP  pa_lista[PA_LISTA_DIM];   

    #define pare(pa,n) ((pa)->pa_lista[(n)])
} patio;

cronograma *cronograma_novo () {
    cronograma *c = calloc(1, sizeof(cronograma));
    return c;
}

patio *patio_novo() {
    patio * p = calloc(1, sizeof (patio));
    return p;
}

void cronograma_insere (head, novo)
	cronograma *head;
	cronograma *novo;
{
    while (head->na_prox != NULL) {
        head = head->na_prox;
    }
    novo->na_prox = head->na_prox;
    head->na_prox = novo;
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


void carrega_cronograma (head, arquivo)
	cronograma *head;
	FILESPEC arquivo;
{
    int i = 1, j = 1;
	char lixo;

	FILE *f = fopen (arquivo, "rt");

    if (f == NULL) {
    	perror ("Problema na abertura do arquivo");
    	return;
    }

    while (!feof(f) && !ferror(f)) {

        cronograma *cr = cronograma_novo();

    	fscanf(f, "%d %d %c %d \"%[^\"]\" %d %d",
            &cr->na_data,
            &cr->na_hora,
            &lixo,
            &cr->na_min,
            cr->na_nome,
            &cr->na_carga,
            &cr->na_pier
        );

            cr->na_ciclo = i;
            if (j == 3) { 
            	i++; j = 0;
            }
            j++;
    	cronograma_insere(head, cr);
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
        return;
    }

    while (!feof(fp) && !ferror(fp)) {

        patio *pa = patio_novo();

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

	tempo = (Q->na_hora + (double)Q->na_min/60) - (P->na_hora + (double)P->na_min/60);
	tempo = (Q->na_data - P->na_data)*24 + tempo;
	return tempo;
}

patio *procura_patio (cronograma *li, patio *pt) {
	patio *p = pt->pa_prox;

	while (p != NULL && li->na_carga > p->pa_capacidade)
		p = p->pa_prox;
	return p;
}

void marca_recuperadoras (patio *pt, char re_nome[]) {
	patio *p = pt;
	while (p != NULL) {
		if (strcmp (re_nome, p->pa_lista[0].re_nome) == 0) p->pa_lista[0].re_uso = 1;
		if (strcmp (re_nome, p->pa_lista[1].re_nome) == 0) p->pa_lista[1].re_uso = 1;
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
		if (aux->pa_lista[1].re_uso != -1) aux->pa_lista[1].re_uso = 0;
		aux = aux->pa_prox;
	}	
	aux = pa;
	while (l->na_ciclo == ciclo) {
		while (i < 3) {

			p = procura_patio(l, aux);
	        aux = p;
		  	if (p != NULL) {
		  		if ((p->pa_lista[0].re_uso != 0 && p->pa_lista[1].re_uso != 0) && (p->pa_capacidade - l->na_carga < 0)) {
		  		p = procura_patio(l, aux);

		  		}
		  		else {
		  			if (p->pa_lista[0].re_uso == 0) {
		  				printf ("%c %d %s %s \n", p->pa_iden, l->na_ciclo, l->na_nome, p->pa_lista[0].re_nome);
		  				strcpy(rec, p->pa_lista[0].re_nome);
		  				marca_recuperadoras(pa, rec);
		  				p->pa_capacidade = p->pa_capacidade - l->na_carga;
		  			}

		  			else if (p->pa_lista[1].re_uso == 0) {
		  				printf ("%c %d %s %s \n", p->pa_iden, l->na_ciclo, l->na_nome, p->pa_lista[1].re_nome);
		  				strcpy(rec, p->pa_lista[1].re_nome);
		  				marca_recuperadoras(pa, rec);
		  				p->pa_capacidade = p->pa_capacidade - l->na_carga;
		  			}
		  		}
		  	}
		  	else {
		  		printf ("\nPatio lotado");
			    aux = pa;
			}
	        l = l->na_prox;
	        i++;
	    }
	}
}

void funcao1 (cronograma *lista, patio *pa) {
	cronograma *p, *q, *r, *aux, *auxc;
	double tca, tcb, ta, tb;
	int ciclo = lista->na_ciclo;
	auxc = lista->na_prox;
	p = lista;
	q = p;
	aux = malloc(sizeof(cronograma));
	while (p->na_prox != NULL) {
		while (p->na_ciclo == q->na_ciclo && q->na_prox != NULL) {
			if (p->na_pier == q->na_pier) {
			    tca = p->na_carga/6000;
	            tcb = q->na_carga/6000;
			    r = q;
		        while (r->na_ciclo < ciclo + 1 && r->na_prox != NULL)
			        r = r->na_prox;
		         ta = calcula_tempo(p, q);
		    	 tb = calcula_tempo(q, r);
			     if (tca + tcb > ta + tb) {
			         if (r->na_pier != q->na_pier) {
			            *aux = *q;
			            *q = *r;
		     	        q->na_prox = aux->na_prox;
			            aux->na_prox = r->na_prox;
		    	        *r = *aux;
		       	        r->na_prox = aux->na_prox;
		    	        q->na_ciclo = ciclo;
		    	        r->na_ciclo = ciclo + 1;
		    	     }
	             }
           	}
             q = q->na_prox;
        }      
        p = p->na_prox;
        q = p->na_prox;
        if (p->na_ciclo != ciclo) {
        	funcao2(auxc, ciclo, pa);
	        ciclo = p->na_ciclo;
	        auxc = p;
	    }
	}
}

void imprime_cronograma (cronograma *lista) {
	cronograma *p;
	for (p = lista->na_prox; p->na_prox != NULL; p = p->na_prox) {
		printf("%d %.2d:%.2d %s %d %d %d", p->na_data, p->na_hora, p->na_min, p->na_nome, p->na_carga, p->na_pier, p->na_ciclo);
		printf("\n");
    }
}


void imprime_patio (patio *pt) {
	patio *p;
	for (p = pt->pa_prox; p->pa_prox != NULL; p = p->pa_prox) {
		printf("%c %d %s", p->pa_iden, p->pa_capacidade, p->pa_lista[0].re_nome);
		printf("\n");
    }
}

int main() {

	cronograma *head = cronograma_novo();
    carrega_cronograma(head, "crono.txt");

    patio *cabeca = patio_novo();
    patio_carrega(cabeca, "portorec.txt");

	funcao1(head, cabeca);
    printf("\n");

	return 0;
}
