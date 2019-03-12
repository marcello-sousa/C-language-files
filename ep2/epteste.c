#include <stdio.h>

int main()
{
  int n,x,i,m;
  printf("\n\n   SOLUCAO DO PROBLEMA DE JOSEPHUS \n\n");
  printf("Entre com o numero de pessoas (n): ");
  scanf("%d",&n);
  printf("Entre com o valor do \"passo\" (m): ");
  scanf("%d",&m);
  printf("\n A sequencia de pessoas a serem mortas é:\n");
  for (i=1;i<=n;i++)
  {
    x=m*i; // se n fosse infinito seria a i-esima pessoa a ser morta
    while (x>n)  // ajusta x enquanto x > n
      x=(m*(x-n)-1)/(m-1); // arredonda para baixo!
    printf("%d, ",x);
  }
  printf("\b\b.\n\n");
  return(0);
}
