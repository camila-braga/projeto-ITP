#include <stdio.h>
#include <stdlib.h>

#include "menuOP1.h"

//! Função que cria e atualiza um arquivo contendo a quantidade de tabelas
//! existentes e seus nomes.

#ifndef LISTA_TABELAS
#define LISTA_TABELAS

void CriaArqNomesTabelas(char *texto) {
  FILE *ArqNomes;
  ArqNomes = fopen("Arquivo com nomes das tabelas.txt", "a+");

  // fprintf(ArqNomes, "%d\n", qtdTabExistentes);
  fprintf(ArqNomes, "%s\n", texto);

  fclose(ArqNomes);
  printf("Arquivo Geral com todos os nomes da tabela foi "
         "criado/atualizado com sucesso.\n");
  /*O arquivo contendo a lista de nomes das tabelas existentes terá o seguinte formato:
  Quantidade de tabelas existentes;
  Nome da tabela 1;
  Nome da tabela 2;
  Nome da tabela 3;
  e assim por diante.
  */

  /*Gostaria que funcionasse assim:
  Sempre que fosse criada uma tabela nova, o dado referente à quantidades de tabelas existentes seria incrementado de 1 e o nome da tabela nova seria adicionado no final da lista*/
}


#endif