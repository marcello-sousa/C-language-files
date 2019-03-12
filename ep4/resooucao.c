#include <stdio.h>
#include <stdlib.h>

#define LIN 6
#define COL 9

typedef struct no No;
struct no{
    int linha;
    int coluna;
    No *prox;
};

typedef struct fila Fila;
struct fila{
    No *inicio;
    No *fim;
    int tamanho;
};

typedef struct coordenada Coordenada;
struct coordenada{
    int linha;
    int coluna;
};

Fila *iniciaFila (){
    Fila *f = malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

int filaVazia (Fila *f){
    return (f->inicio == NULL);
}

void insereFila (int linha, int coluna, Fila *f){
    No *nova;

    nova = malloc (sizeof(No));
    nova->linha = linha;
    nova->coluna = coluna;
    
    if (f->inicio == NULL){
        f->fim = nova;
        f->inicio = f->fim;
        f->tamanho++;
        return;
    }
    
    (f->fim)->prox = nova;
    f->fim = (f->fim)->prox;
    f->tamanho++;
}


No *removeFila (Fila *f){
    No *aux; 
    aux = f->inicio;
    
    f->inicio = aux->prox;
    f->tamanho--;
    
    if (f->inicio == NULL)  f->fim = NULL;

    return aux;
}


void imprimeFila (Fila *f){
    int i;
    No *aux;
    
    i = 0; 
    aux = f->inicio;
    
    if (f->tamanho == 0){
        printf ("Fila vazia.");
    }else{
        while (i < f->tamanho){
            printf("(%d, %d) ", aux->linha, aux->coluna);
            aux = aux->prox;
            i++;
        }
    
        printf("\n");
    }
}


/* retorna 0 se estiver fora da borda e 1 cc. */
int checagem_borda (int lin, int col, int m, int n){

    if((lin < 0) || (lin >= m) || (col < 0) || (col >= n)){
        return 0;
    }else{
        return 1;
    }
}



/* A funcao imprimeCaminho utiliza:
 *      - uma matriz pais, recebida como argumento, que armazena na posicao [i][j] a casa que foi anteriormente visitada no labirinto 
 *      - um vetor caminho, que armazena o caminho percorrido no labirinto.
 *
 * A funcao, insere na ultima posicao do vetor caminho a ultima casa do labirinto (m - 1, n -1)e 
 * verifica na matriz de pais, qual foi a ultima casa visitada antes da posicao (m - 1, n - 1).  A funcao insere a ultima essa ultima
 * casa visitada na posicao caminho[tam_v -1] e assim sucessivamente. Dessa maneira, obtemos um vetor no qual cada posicao a partir
 * 0, armazena qual a proxima casa acessada na matriz labirinto, que é o caminho percorrido na matriz libirinto.
 */
void imprimeCaminho (No pais[LIN][COL], int m, int n, int tamanho){
    int i, j, auxi, auxj, auxT;
    Coordenada caminho[tamanho];
    
    i = m - 1;
    j = n - 1;
    
    auxT = tamanho;

    caminho[tamanho].linha = i; 
    caminho[tamanho].coluna = j;
    tamanho--;
    
    while (i != -1 && j != -1){
        auxi = pais[i][j].linha;
        auxj = pais[i][j].coluna;

        caminho[tamanho].linha = auxi;
        caminho[tamanho].coluna = auxj;
        i = auxi;
        j = auxj;
        tamanho--;
    }
    
    printf ("Caminho percorrido: \n");
    
    for (i = 0; i < auxT; i++){
        if (caminho[i].linha != -1 && caminho[i].coluna != -1)
            printf ("(%d, %d)", caminho[i].linha, caminho[i].coluna);
        if (i != 0) 
            printf (" -> ");
    }
    printf ("(%d, %d)", m - 1, n - 1);
    printf ("\n");
}


/* A funcao resolveLabirinto trabalha com 
 *      - uma fila, f na qual cada casa visitada insere na proxima posicao dessa fila as suas casas adacentes que são livres.
 *      - uma matriz pais, que armazena na posicao [i][j] um no, em que no.linha e no.coluna armazenam a posicao do no anteriormente 
 *              visitada no labirinto
 *      - uma matriz distancia, que armazena a distancia entre a casa (0, 0) e todas as outras casas que são atingiveis a partir de
 *             (0, 0), dessa maneira, a casa (m - 1, n -1) armazena a distancia percorrida no caminho.
 * */
int resolveLabirinto (int labirinto[LIN][COL], int m, int n){
    int i, j, distancia[LIN][COL];
    Fila *f;      
    No pais[LIN][COL];
    No *atual;


    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            distancia[i][j] = -1;
            pais[i][j].linha = -1;
            pais[i][j].coluna = -1;
        }
    }
        
    for (i = 0; i < m; i++){
        for ( j = 0; j < n; j++){
            printf("(%d) ", labirinto[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    
    f = iniciaFila ();
    insereFila (0, 0, f);
    distancia[0][0] = 0;

    while (!filaVazia (f)){
        
        atual = removeFila (f);
        
        i = atual->linha;
        j = atual->coluna;

        if (labirinto[i][j] == 0){

            if (checagem_borda (i - 1, j, m, n) == 1){
                if ((labirinto[i - 1][j] == 0) && (distancia[i - 1][j] < 0)){
                    insereFila(i - 1, j, f);
                    pais[i - 1][j].linha = i;
                    pais[i - 1][j].coluna = j;
                    distancia[i - 1][j] = distancia[i][j] + 1;
                }
            }

            if (checagem_borda (i, j + 1, m, n) == 1){
                if ((labirinto[i][j + 1] == 0) && (distancia[i][j + 1] < 0)){
                    insereFila(i, j + 1, f);
                    pais[i][j + 1].linha = i;
                    pais[i][j + 1].coluna = j;
                    distancia[i][j + 1] = distancia[i][j] + 1;
                }
            }
            
            if (checagem_borda (i + 1, j, m, n) == 1){
                if ((labirinto[i + 1][j] == 0) && (distancia[i + 1][j] < 0)){
                    insereFila(i + 1, j, f);
                    pais[i + 1][j].linha = i;
                    pais[i + 1][j].coluna = j;
                    distancia[i + 1][j] = distancia[i][j] + 1;
                }
            }
            
            if ((checagem_borda (i, j - 1, m, n) == 1) ){
                if ((labirinto[i][j - 1] == 0) && distancia[i][j - 1] < 0){
                    insereFila(i, j - 1, f);
                    pais[i][j - 1].linha = i;
                    pais[i][j - 1].coluna = j;
                    distancia[i][j - 1] = distancia[i][j] + 1;
                }
            }
        }

        labirinto[i][j] = -1;

    }

    printf ("A distancia da casa inicial a final: %d\n", distancia[m-1][n-1]);

    imprimeCaminho (pais, m, n, distancia[m - 1][n - 1] + 1);

    if (distancia[m - 1][n - 1] != -1) {
	return 1;
    }else{
	return 0;
    }

}

int main (){
   
    /* Declaração dos labirintos */
    /* Lembrem-se de alterar as constantes LIN e COL para rodar as funcoes */
    /*
    int labirinto1[3][3] = { {0,1,1}, {0,0,0}, {1,0,0}};
   
    int labirinto2[4][4] = { {0,0,1,1}, {1,0,0,0}, {1,0,1,0}, {1,0,0,0}};
    int labirinto3[5][6] = { {0,0,1,0,1,1}, {1,0,0,0,1,0}, {1,1,0,1,0,0}, {1,0,0,0,0,1}, {1,1,1,1,0,0}};
    int labirinto4[6][9] = { {0,1,1,0,0,1,1,0,1}, {0,0,1,1,0,1,0,0,1}, {1,0,0,0,0,1,0,1,1}, {0,1,0,0,1,0,0,0,1}, {0,0,1,0,0,0,1,0,1}, {1,0,0,1,1,0,0,0,0}};
    */

    int labirinto4[6][9] = { {0,1,1,0,0,1,1,0,1}, {0,0,1,1,0,1,0,0,1}, {1,0,0,0,0,1,0,1,1}, {0,1,0,0,1,0,0,0,1}, {0,0,1,0,0,0,1,0,1}, {1,0,0,1,1,0,0,0,0}};
    resolveLabirinto (labirinto4, 6, 9);
    /*
    resolveLabirinto (labirinto1, 3, 3);
    resolveLabirinto (labirinto2, 4, 4);
    resolveLabirinto (labirinto3, 5, 6);
    resolveLabirinto (labirinto4, 6, 9);

    */
    return 0;
}

