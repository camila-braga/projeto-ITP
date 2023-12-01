#include <stdio.h>
#include <stdlib.h>

#include "leituraString.h"

//! Função que exibe todos os dados de uma tabela.

void ListaDadosTabela() {

  // Leitura do nome da tabela.
  FILE *Arquivo;
  char *nome;
  int tamNome;
  int condicao = 0;
  do {
    nome = lerString(&tamNome);
    Arquivo = fopen(nome, "r");
    if (Arquivo == NULL) {
      printf("Tabela não encontrada. Digite o nome novamente.\n");

    } else {
      printf("Tabela encontrada");
      condicao = 1;
    }

  } while (condicao == 0);
  printf("Os dados da tabela %s são\n", nome);
  char *Vetor = NULL;
  int t
  
  // Exibição dos dados da tabela.
}