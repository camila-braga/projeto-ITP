#include "leituraString.h"
#include <stdio.h>

//! Função que Apaga uma tabela.

void ApagaTabela()
{
  FILE *Arquivo;

  // Leitura do nome da tabela desejada.
  printf("Digite o nome da tabela que deseja apagar:\n");
  char *nome;
  int tamVetor;
  int condicao = 0;
  do
  {
    nome = lerString(&tamVetor);
    Arquivo = fopen(nome, "r");
    if (Arquivo == NULL)
    {
      printf("Tabela não existe. Digite o nome novamente.\n");
    }
    else
    {
      condicao = 1;
      fclose(Arquivo);
    }
  } while (condicao == 0);

  if (remove(nome))
  {
    printf("Tabela apagada com sucesso.\n");
  }
  else
  {
    printf("Ocorreu um erro no processo.\n");
  }
}
