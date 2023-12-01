/***
 * @file
 * @brief Responsável pela execução inicial do programa
 *
 * Gerencia o menu do programa invocando os módulos adequados para cada opção.
 */

#include <stdio.h>
#include <stdlib.h>

#include "criarTabela.h"
#include "menuOP2.h"
#include "menuOP3.h"
#include "menuOP4.h"

#include "menuOP7.h"

typedef enum
{
  CRIAR_TABELA = 1,
  LISTAR_TABELA = 2,
  CRIAR_LINHA = 3,
  LISTAR_DADOS = 4,
  PESQUISAR_VALOR = 5,
  APAGAR_TUPLA = 6,
  APAGAR_TABELA = 7,
  SAIR = 8
} Opcoes;

/**
 * Exibe as opções do menu
 */
void menu()
{
  printf("-------------------------------------------------------\n");
  printf("          Menu Principal. Opcoes disponiveis:\n");
  printf("-------------------------------------------------------\n");
  printf("%d - Criar tabela;\n", CRIAR_TABELA);
  printf("%d - Listar todas as tabelas;\n", LISTAR_TABELA);
  printf("%d - Criar uma nova linha na tabela;\n", CRIAR_LINHA);
  printf("%d - Listar todos os dados de uma tabela;\n", LISTAR_DADOS);
  printf("%d - Pesquisar valor em uma tabela;\n", PESQUISAR_VALOR);
  printf("%d - Apagar uma tupla (registro ou linha) de uma tabela;\n", APAGAR_TUPLA);
  printf("%d - Apagar uma tabela;\n", APAGAR_TABELA);
  printf("%d - SAIR.\n", SAIR);
  printf("-------------------------------------------------------\n\n");
  printf("Digite a opcao desejada:");
}

/**
 * Função principal
 *
 * @return resultado da execução do programa. 0 indica ausência de erros.
 */
int main(void)
{

  Opcoes opcao;
  do
  {
    menu(); // imprime as opções de escolha para o usuário.
    scanf("%d", &opcao);

    //! Instruções de acordo com a escolha do usuário.
    switch (opcao)
    {
    case CRIAR_TABELA:
      criaTabela();
      break;
    case LISTAR_TABELA:
      //ListaTabelas();
      break;
    case CRIAR_LINHA:
      //CriarNovaLinha();
      break;
    case LISTAR_DADOS:
      //ListaDadosTabela();
      break;
    case PESQUISAR_VALOR:
      break;
    case APAGAR_TUPLA:
      break;
    case APAGAR_TABELA:
      //ApagaTabela();
      break;
    case SAIR:
      break;
    default:
      printf("Opcao invalida\n\n");
    }

  } while (opcao != SAIR);

  return 0;
}
