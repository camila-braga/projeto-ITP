/***
 * @file
 * @brief Responsável pela execução inicial do programa
 *
 * Gerencia o menu do programa invocando os módulos adequados para cada opção.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Dados.h"
#include "Tabela.h"
#include "TabelaGeral.h"

typedef enum
{
  CRIAR_TABELA = 1,
  LISTAR_TABELA = 2,
  CRIAR_LINHA = 3,
  LISTAR_DADOS = 4,
  PESQUISAR_VALOR = 5,
  APAGAR_TUPLA = 6,
  APAGAR_TABELA = 7,
  SAIR = 8,
  LIMPAR = 9
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
  printf("%d - Limpar os dados.\n", LIMPAR);
  printf("-------------------------------------------------------\n\n");
  printf("Digite a opcao desejada: ");
}

void criarTabela()
{
  printf("Digite o nome da tabela: ");
  Texto nome = texto_lerTerminalEmLoop(256); // nomes são limitados a 256 caracteres
  while (tabelaGeral_contemTabela(nome))
  {
    printf("\t\tNao e possivel realizar essa acao: ja existe uma tabela de nome \"%s\".\n", nome.vetor);
    free(nome.vetor);
    printf("\t\tDigite o nome da tabela: ");
    nome = texto_lerTerminalEmLoop(256);
  }

  printf("\tDigite a quantidade de colunas para tabela \"%s\": ", nome.vetor);
  int quantidadeColunas = texto_lerValorPositivoEmLoop();
  printf("\tDigite o nome da coluna de chave primaria para tabela \"%s\": ", nome.vetor);
  Texto nomeDasColunas[quantidadeColunas];
  char tiposDasColunas[quantidadeColunas];
  nomeDasColunas[0] = texto_lerTerminalEmLoop(256);
  tiposDasColunas[0] = 'i';
  for (int i = 1; i < quantidadeColunas; i++)
  {
    printf("\tDigite o nome da coluna %d: ", i + 1);
    nomeDasColunas[i] = texto_lerTerminalEmLoop(256);
    tiposDasColunas[i] = texto_lerTipoEmLoop();
  }

  Tabela tabela = tabela_criar(nome, quantidadeColunas, nomeDasColunas, tiposDasColunas);
  tabela_gravar(tabela);
  tabelaGeral_adicionarTabela(nome);

  printf("\n\n");
  tabela_exibirCabecalho(tabela);
  printf(">>Tabela criada com sucesso.\n");

  tabela_liberar(tabela);
}

void exibirDados()
{
  printf("Digite o nome da tabela: ");
  Texto nome = texto_lerTerminalEmLoop(256);
  if (tabelaGeral_contemTabela(nome))
  {
    Tabela tabela = tabela_recuperar(nome);
    tabela_exibirCabecalho(tabela);
    tabela_exibirDados(tabela);
    tabela_liberar(tabela); // libera nome também
    printf("\n");
  }
  else
  {
    printf("\t\tNao e possivel realizar essa acao: nao existe uma tabela de nome \"%s\".\n", nome.vetor);
    free(nome.vetor);
  }
}

Texto leituraDaChavePrimaria(ColunaDaTabela coluna){
  int valor = texto_lerValorPositivoEmLoop();
  Texto texto;
  texto.capacidade = 32;
  texto.tamanho = 0;
  texto.vetor = calloc(32, sizeof(char));
  sprintf(texto.vetor, "%d", valor);
  texto.tamanho = strlen(texto.vetor);
  return texto;
}

void leituraDeDados(int n, ColunaDaTabela colunas[], Texto linhaASerInserida[])
{
  printf("\tDigite o valor da chave primaria: ");
  linhaASerInserida[0] = leituraDaChavePrimaria(colunas[0]);
  for (int i = 1; i < n; i++)
  {
    ColunaDaTabela aux = colunas[i];
    printf("\tDeseja inserir um valor para coluna %s (s, n)?: ", aux.nome.vetor);
    char inserir;
    scanf("%c", &inserir);
    getchar(); // limpar buffer
    if (inserir == 's')
    {
      printf("\tDigite o valor do tipo de dado %c para a coluna %s: ", aux.tipo, aux.nome);
      linhaASerInserida[i] = texto_lerValorComTipo(aux.tipo);
    }
    else
    {
      Texto texto;
      texto.capacidade = 5;
      texto.tamanho = 4;
      texto.vetor = calloc(4, sizeof(char));
      sprintf(texto.vetor, "NULL");
      linhaASerInserida[i] = texto;
    }
  }
}

void adicionarDados()
{
  printf("Digite o nome da tabela: ");
  Texto nome = texto_lerTerminalEmLoop(256);
  if (tabelaGeral_contemTabela(nome))
  {
    Tabela tabela = tabela_recuperar(nome);
    Texto linhaASerInserida[tabela.quantidadeDeColunas];
    leituraDeDados(tabela.quantidadeDeColunas, tabela.colunas, linhaASerInserida);
    int posicao = coluna_buscarValor(tabela.colunas[0], linhaASerInserida[0]);
    if (posicao == -1) // valor ausente
    {
      tabela_adicionarLinha(tabela, linhaASerInserida);
      tabela_gravar(tabela);
    }
    else
    {
      printf("\t\tNao e possivel realizar essa acao: ja existe uma linha com a chave \"%s\".\n", linhaASerInserida[0].vetor);
      for (int i = 0; i < tabela.quantidadeDeColunas; i++)
      {
        free(linhaASerInserida[i].vetor);
      }
    }
    tabela_liberar(tabela); // libera nome também
  }
  else
  {
    printf("\t\tNao e possivel realizar essa acao: nao existe uma tabela de nome \"%s\".\n", nome.vetor);
    free(nome.vetor);
  }
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
    getchar(); // limpar buffer

    //! Instruções de acordo com a escolha do usuário.
    switch (opcao)
    {
    case CRIAR_TABELA:
      criarTabela();
      break;
    case LISTAR_TABELA:
      // ListaTabelas();
      break;
    case CRIAR_LINHA:
      // CriarNovaLinha();
      break;
    case LISTAR_DADOS:
      exibirDados();
      break;
    case PESQUISAR_VALOR:
      break;
    case APAGAR_TUPLA:
      break;
    case APAGAR_TABELA:
      // ApagaTabela();
      break;
    case SAIR:
      break;
    case LIMPAR:
      tabelaGeral_limpar();
      break;
    default:
      printf("Opcao invalida\n\n");
    }

  } while (opcao != SAIR);

  return 0;
}
