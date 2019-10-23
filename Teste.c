#include <stdio.h>
#include <stdlib.h>
int main(void)
{
  // criando a variável ponteiro para o arquivo
  char palavra[20];
  FILE *pont_arq;

  //abrindo o arquivo
  pont_arq = fopen("Arquivo.pdf", "a");

  //mensagem para o usuário
  printf("O arquivo foi criado com sucesso! \n\n");

  printf("Escreva uma palavra para testar gravacao de arquivo: ");
  scanf("%s", palavra);

  //usando fprintf para armazenar a string no arquivo
  fprintf(pont_arq, "%s", palavra);

  //usando fclose para fechar o arquivo
  fclose(pont_arq);

  printf("Dados gravados com sucesso!");


  system("pause");
  return(0);
}

