#include <stdio.h>
#include <stdlib.h>

#include "leituraString.h"

void CriarNovaLinha() {
  /*Gostaria que funcionasse assim:
  Ler do usuário o nome da tabela desejada
  Ler o arquivo de listas de tabelas criadas e verificar se a tabela pedida
  existe Caso não exista, exibir mensagem de erro Caso exista, fechar esse
  arquivo e abrir o arquivo da tabela desejada Pedir o valor da chave primária
  Verificar se o valor já existe.
  Caso exista, solicitar outro
  Caso não exista, gravar como o valor da primeira coluna
  Solicitar os valores das outras colunas
  Atualizar valor da quantidade de linhas dessa tabela
  Fechar a tabela*/

  // Leitura do nome da tabela desejada:
  printf("Digite o nome da tabela na qual deseja inserir uma linha.\n");
  char *nomeTabela;
  int tamVetor;
  int condicao = 0;
  FILE *arqTabelas;

  do {
    nomeTabela = lerString(&tamVetor);
    arqTabelas = fopen(nomeTabela, "r");
    if (arqTabelas == NULL) {
      printf(
          "A tabela requerida não foi encontrada. Digite novamente o nome.\n");

    } else {
      condicao = 1;
      printf("Tabela encontrada.\n");
      fclose(arqTabelas);
    }
  } while (condicao == 0);

  // Leitura do valor da chave primária:
  arqTabelas = fopen(nomeTabela, "a+");
  condicao = 0;
  printf("Digite o valor da chave primária.\n");
  int chave;
  do {
    scanf("%d", &chave);
    if (chave > 0) {
      printf("Valor inválido. Digite novamente.\n");
    } else {

      fseek(arqTabelas, 0,
            SEEK_SET); // para o ponteiro ir para o início do arquivo
      if (chave == fscanf(arqTabelas, "%d", &chave)) {

        condicao = 1;
      }
    }
  } while (condicao == 0);
      
}

