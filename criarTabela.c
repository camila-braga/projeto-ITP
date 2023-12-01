
/**
 * @file
 * @brief Implementação responsável por criar tabelas.
 *
 * As tabelas são indexadas por um aquivo principal denominado "Tabela Geral.data"
 * e cada tabela estará associada a um arquivo especificado pelo o nome dela atribuído pelo usuário.
 *
 * A Tabela Geral terá o seguinte formato:
 * Quantidade de tabelas existentes
 * Quantidade de caracteres do nome da primeira tabela (incluindo o \0)
 * Nome da primeira tabela
 * Quantidade de caracteres do nome da segunda tabela  (incluindo o \0)
 * Nome da segunda tabela
 * ...
 * Quantidade de caracteres do nome da última tabela  (incluindo o \0)
 * Nome da última tabela
 *
 *
 *
 *
 * As tabelas específicas serão organizadas da seguinte forma:
 * Nome da tabela
 * Quantidade de colunas
 * Quantidade de linhas
 * Quantidade de caracteres do nome da primeira coluna (incluindo o \0)
 * Nome da primeira coluna
 * Tipo de dado da primeira coluna
 * Quantidade de caracteres do nome da segunda coluna (incluindo o \0)
 * Nome da segunda coluna
 * Tipo de dado da segunda coluna
 * ...
 * Quantidade de caracteres do nome da última coluna (incluindo o \0)
 * Nome da última coluna
 * Tipo de dado da última coluna
 * Dados da primeira coluna
 * Dados da segunda coluna
 * ...
 * Dados da última coluna
 *
 * Observação: a primeira coluna será a chave primária da tabela e seu tipo será inteiro sem sinal.
 *
 * Observação: os nomes das tabelas possuem restrições quanto aos caracteres. Os nomes podem ser compostos
 * por letras, dígitos e os símbolos '-', '_', '.' e espaço.
 */

#include <string.h>

#include "criarTabela.h"

#include <stdio.h>
#include <stdlib.h>
#include "TabelaGeral.h"
#include "leituraString.h"

// Funções auxiliares para verificação de nomes válidos para as tabelas

/**
 * Verifica se o caractere é uma letra minúscula
 *
 * @param c Caractere sendo verificado
 * @return 1 se o caractere for uma letra minúscula e 0 em caso contrário
 */
int ehMinuscula(char c) { return c >= 'a' && c <= 'z'; }

/**
 * Verifica se o caractere é uma letra maiúscula
 *
 * @param c Caractere sendo verificado
 * @return 1 se o caractere for uma letra maiúscula e 0 em caso contrário
 */
int ehMaiscula(char c) { return c >= 'A' && c <= 'Z'; }

// TODO comentar
int ehDigito(char c) { return c >= '0' && c <= '9'; }

// TODO comentar
int ehSimbolo(char c) { return c == '.' || c == '_' || c == ' ' || c == '-'; }

/**
 * Verifica se um nome é válido
 *
 * Os nomes das tabelas possuem restrições quanto aos caracteres. Os nomes podem ser compostos
 * por letras, dígitos e os símbolos '-', '_', '.' e espaço.
 * @param nome Ponteiro para nome a ser verificado.
 * @param tamanho Quantidade de caracteres do nome.
 * @return 1 caso o nome seja válido e 0 em caso contrário.
 */
int verificaNomeDaTabelaValido(char *nome, int tamanho)
{
  int condicao = (tamanho > 0) && !ehSimbolo(nome[0]);
  for (int i = 0; i < tamanho; i++)
  {
    char c = nome[i];
    int min = ehMinuscula(c);
    int mai = ehMaiscula(c);
    int dig = ehDigito(c);
    int sim = ehSimbolo(c);
    if (min + mai + dig + sim == 0)
    {
      condicao = 0;
    }
  }
  return condicao;
}

/**
 * Verificar se existe um nome de tabela na tabela geral.
 *
 * @param nomeDaTabela Nome a ser pesquisado.
 * @param tamanho Tamanho do vetor de caracteres do nome.
 * @return 1 se o nome estiver presente e 0 em caso contrário.
 */
int verificarExistencia(char *nomeDaTabela, int tamanhoNomeDaTabela)
{
  FILE *tabelaGeral = fopen("tabela geral.data", "r");
  if (tabelaGeral == NULL)
  {
    return 0;
  }
  else
  {
    int n;
    fscanf(tabelaGeral, "%d ", &n);
    for (int i = 0; i < n; i++)
    {
      int tamanho;
      fscanf(tabelaGeral, "%d ", tamanho);
      char nomeLido[tamanho];
      fgets(nomeLido, tamanho, tabelaGeral);
      if (strcmp(nomeLido, nomeDaTabela) == 0)
      {
        return 1;
      }
    }
  }
  return 0;
}

// TODO comentar
char *lerNomeDaTabela(int *tamanho)
{
  printf("Digite o nome da tabela\n");
  int criterio = 0;
  char *nomeDaTabela;
  while (criterio == 0)
  {
    nomeDaTabela = lerString(tamanho);
    int nomeValido = verificaNomeDaTabelaValido(nomeDaTabela, *tamanho - 1);
    int existeNome = verificarExistencia(nomeDaTabela, tamanho - 1);
    if (!nomeValido || existeNome)
    {
      printf("Nome inválido. Digite novamente.\n");
      free(nomeDaTabela);
    } else {
      criterio = 1;
    }
  }
  return nomeDaTabela;
}

void criarTabela()
{
  int tamanhoNomeDaTabela;
  char *nomeDaTabela = lerNomeDaTabela(&tamanhoNomeDaTabela);
  // TODO
}

//! Função que cria uma tabela.
void criaTabela()
{
  /*Gostaria que funcionasse assim:
  Ler nome da tabela, fazendo o tratamento necessário
  Criar arquivo da tabela
  Criar arquivo auxiliar contendo o nome da tabela, a quantidade de colunas e os nomes dessa colunas
  Criar/Atualizar arquivo contendo lista de tabelas criadas
  Ler quantidade de colunas
  Quantidade de linhas inicial = 0
  Ler nome da primeira coluna que é a chave primária
  Gravar seu tipo de dados que é inteiro não negativo
  Ler os nomes e tipos de dados das outras colunas*/

  FILE *arquivoTabela;
  FILE *arquivoNomesColunasDaTabela;

  // Leitura do nome da tabela:
  printf("Digite o nome da tabela\n");
  int tamanhoVetor;
  int criterio = 0;
  char *nomeDaTabela;
  while (criterio == 0)
  {
    nomeDaTabela = lerString(&tamanhoVetor);
    criterio = verificaNomeDaTabelaValido(nomeDaTabela, tamanhoVetor);
    if (criterio == 0)
    {
      printf("Nome inválido. Digite novamente.\n");
    }
  }
  arquivoTabela = fopen(nomeDaTabela, "w");
  fprintf(arquivoTabela, "%s\n", nomeDaTabela);

  // Chama função para atualizar lista de tabelas existentes:
  CriaArqNomesTabelas(nomeDaTabela);

  // Nome do arquivo auxiliar da tabela criada que conterá os nomes de suas colunas:
  char AUXTABELA[tamanhoVetor + 3];
  for (int i = 0; i < tamanhoVetor; i++)
  {
    AUXTABELA[i] = nomeDaTabela[i];
  }
  AUXTABELA[tamanhoVetor] = 'A';
  AUXTABELA[tamanhoVetor + 1] = 'U';
  AUXTABELA[tamanhoVetor + 2] = 'X';
  AUXTABELA[tamanhoVetor + 3] = '\0';
  arquivoNomesColunasDaTabela = fopen(AUXTABELA, "w");
  fprintf(arquivoNomesColunasDaTabela, "%s\n", AUXTABELA);

  // Leitura da quantidade de colunas.
  printf("Digite a quantidade de colunas da tabela %s\n", nomeDaTabela);
  int qtdColunas;
  scanf("%d", &qtdColunas);
  fprintf(arquivoTabela, "%d\n", qtdColunas);
  fprintf(arquivoNomesColunasDaTabela, "%d\n", qtdColunas);

  // Quantidade de linhas.
  int qtdLinhas = 0;
  fprintf(arquivoTabela, "%d\n", qtdLinhas);

  // Leitura do nome e tipo de dados de cada coluna.
  printf("Digite o nome da primeira coluna que será a chave primária.\n");
  char *nomeChave;
  int tamChave;
  nomeChave = lerString(&tamChave);
  fprintf(arquivoTabela, "%s\n", nomeChave);
  fprintf(arquivoTabela, "%c\n", 'i');

  for (int i = 1; i < qtdColunas; i++)
  {
    printf("Digite o nome da coluna %d.\n", i + 1);
    char *nome;
    int tamanho;
    nome = lerString(&tamanho);
    fprintf(arquivoTabela, "%s\n", nome);
    fprintf(arquivoNomesColunasDaTabela, "%s\n", nome);
    printf("Digite o tipo de dados da coluna %s.\n", nome);
    printf("Opções: 'i' para inteiro, 'f' para float, 'd' para double, 'c' "
           "para char, 's' para string.\n");
    char tipo;
    scanf("%c", &tipo);
    fprintf(arquivoTabela, "%c\n", tipo);
  }

  fclose(arquivoTabela);
  fclose(arquivoNomesColunasDaTabela);
  printf("Tabela %s criada com sucesso\n", nomeDaTabela);
  printf("Tabela auxiliar %s criada com sucesso\n", AUXTABELA);

  /*A tabela criada terá o seguinte formato:
  Nome da tabela
  Quantidade de colunas
  Quantidade de linhas
  Nome da primeira coluna que é a chave primária
  Tipo de dados da chave que é inteiro não negativo
  Nome da segunda coluna, se tiver
  Tipo de dados da segunda coluna, se tiver
  Nome da terceira coluna, se tiver
  Tipo de dados da terceira coluna, se tiver
  e assim por diante.
  */

  /*A tabela auxiliar terá o seguinte formato:
  Nome da tabela
  Quantidade de colunas
  Nome da primeira coluna
  Nome da segunda coluna, se tiver
  Nome da terceira coluna, se tiver
  e assim por diante.
  */

  printf("\n\n<fim>");
}