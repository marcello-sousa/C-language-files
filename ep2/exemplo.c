#include <stdlib.h>
#include <stdwe we weio.h>
struct no
{
	int info;
	struct no *prox;
};
//funções
void addinicio(struct no *head, int valor);
void addfim(struct no *head, int valor);
void remover(struct no *head, int valor);
void buscar(struct no *head, int valor);
void imprimir(struct no *head);
void calcmedia(struct no *head);
void menu();
//------------------------------------------------------------------------------
//função principal
int main()
{
	struct no *head; //cabeça
	int op, valor;
	//lista circular começa na cabeça e aloca um elemento
	if((head = malloc(sizeof (struct no))) == NULL)
	{
		printf("\nMemory Failure\n");//erro
	}
	else
	{
		head->prox = head; //inicializa no proximo registro
		do
		{
			system("CLS");
			menu();
			scanf("%d",&op);
			switch(op)
			{
				case 0:
					break;
				case 1: //inserir no inicio
					addinicio(head, valor);
					break;
	            case 2://inserir no fim
	                addfim(head, valor);
	                break;
				case 3://busca elemento
					buscar(head, valor);
					break;
				case 4:
					remover(head, valor);
					break;
				case 5://média dos elementos
					calcmedia(head);
					break;
				case 6://imprimir lista
					imprimir(head);
					break;
	
				default://nenhuma das opções é escolhida
					printf("\nEsolha uma Opcao valida!\n");
					break;
			}
		
		}
		while(op!=0);
		return 0;
	}	
}
//------------------------------------------------------------------------------
void addinicio(struct no *head, int valor)//inserir um elemento no inicio
{
	struct no *p;
	printf("\nValor do Elemento: ");
	scanf("%d",&valor);
	if((p = malloc(sizeof(struct no))) == NULL)//erro
	{
		printf("\nMemory Failure\n");
	}
	else
	{
		p->info = valor; //recebendo valor
		p->prox = head->prox; //pprox recebe cabeçaprox
		head->prox = p; //cabeça prox recebe p;
	}
}
//------------------------------------------------------------------------------
void addfim(struct no *head, int valor) //inserir no fim
{
    struct no *pNow, *pNext;
    printf("\nValor do elemento: ");
    scanf("%d",&valor);
    if((pNow = malloc(sizeof(struct no))) == NULL)//erro
    {
        printf("\nMemory Failure\n");
    }
    else
    {
        pNow->info = valor; //p recebe valor
        pNext = head->prox; //pnext aponta para o primeiro elemento da lista
        while(pNext->prox != head) //enquanto o proximo e o proximo não chegar na cabeça
        {
            pNext = pNext->prox; //passa para o proximo elemento
        }
        pNow->prox = pNext->prox; //p, do valor, recebe o ultimo elemento que aponta para o pNow e insere no fim na linha abaixo
        pNext->prox = pNow;
    }
}
//------------------------------------------------------------------------------
void remover(struct no *head, int valor)//remover determinado elemento
{
	struct no *p, *aux;
	printf("\nValor a Remover: ");
	scanf("%d",&valor);
	
	p = head->prox; //p recebe o primeiro elemento
	aux = head; 
	head->info = valor; //concatyena valor  na cabeça
	while(p->info != valor) //enquanto o valor digitado for diferente da lista, vai percorrendo
	{
		aux = p; //guarda o elemento e pula para o proximo
		p = p->prox;
	}	
	if(p == head) //não encontrou
	{
		printf("\nElemento nao encontrado\n");
	}
	else
	{
		aux->prox = p->prox; //aux prox recebe o p prox que aponta pra acabeça e elimina a conexao com o p
		free(p);//elimiona o valor
		printf("\nElemento removido com Sucessoj!\n");
	}
}
//------------------------------------------------------------------------------
void imprimir(struct no *head) //imrpimir elementos
{
	struct no *p;
	int okay = 0;
	p = head->prox;//começa no primeiro elemento, para nao cair na cabeça
	while(p!=head->prox)//ensuqnaod p for diferente de cabeça, para achar o fim
	{
		printf("%d ",p->info);//imprime registro
		p = p->prox;//proximo registro
		okay = 1; //validação para lista não ser vazia
	}
	if(okay == 0)//lista vazia
	{
		printf("\nLista Vazia\n");
	}
}
//------------------------------------------------------------------------------
void buscar(struct no *head, int valor)//buscar um elemento na lista
{
	struct no *p; //auxiliar
	printf("\nBuscar elemento: ");
	scanf("%d",&valor);
	p = head->prox; //auxiliar recebe cabeça->prox
	head->info = valor;//cabeça->info recebe o valor a ser procurado
	while(p->info != valor)//enquanto o valor digitado fori diferente cde nulo
	{
		p = p->prox; //passa para o proximo elemento
	}
    if(p == head) //se chegar no fim o p vai ser igual a c abeça, entao nao encotnrou o elemento digitado
    {
        printf("\nElemento nao encontrado!\n");
    }
    else //if(p!=head) - elemento encontrado
    {
        printf("\nElemento encontrado com sucesso!\n");
    }
}
//------------------------------------------------------------------------------
void calcmedia(struct no *head) //média dos elementos
{
	struct no *p;
	int cont = 0; //contador
	float soma = 0; 
	
	p = head->prox; //primeiro elemento da lista
	while(p!=head) //enquanto  o p percorrendo a lista não for nulo
	{
		soma+=p->info; //soma+= valor do elemento
		cont++; //contador ++
		p = p->prox; //passa para o proximo elemento
	}
	printf("\nMedia %.2f",(soma/cont)); //calculando a soma dividido pelo contador
}
//------------------------------------------------------------------------------
void menu()//menu
{
	printf("\n1) Inserir Inicio");
	printf("\n2) Inserir no Fim");
	printf("\n3) Buscar Elemento");
	printf("\n4) Remover Elemento");
	printf("\n5) Media dos Elementos");
	printf("\n6) Imprimir Lista");
	printf("\n\n0) Sair: ");
}
